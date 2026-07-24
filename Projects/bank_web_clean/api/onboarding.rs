#[path = "../src/auth.rs"]
mod auth;

use auth::verify_request;
use http_body_util::BodyExt;
use serde::Deserialize;
use serde_json::{json, Value};
use sqlx::{postgres::PgPoolOptions, Row};
use std::env;
use vercel_runtime::{run, service_fn, Error, Request};

#[derive(Deserialize, Default)]
struct OnboardingInput {
    #[serde(rename = "organizationName")]
    organization_name: Option<String>,
    #[serde(rename = "displayName")]
    display_name: Option<String>,
}

#[tokio::main]
async fn main() -> Result<(), Error> {
    run(service_fn(handler)).await
}

async fn handler(req: Request) -> Result<Value, Error> {
    if req.method().as_str() != "POST" {
        return Ok(json!({ "error": "Method not allowed" }));
    }

    let claims = verify_request(&req).await?;
    let body = req.into_body().collect().await?.to_bytes();
    let input: OnboardingInput = if body.is_empty() {
        OnboardingInput::default()
    } else {
        serde_json::from_slice(&body)?
    };

    // Identity metadata must come from the verified JWT, never from the
    // request body.
    let email = clean_required(
        claims.email,
        "Authenticated email is unavailable",
        320,
    )?;

    let display_name = clean_optional(claims.name.or(input.display_name), 120)
        .unwrap_or_else(|| email.split('@').next().unwrap_or("User").to_string());

    let organization_name = clean_optional(input.organization_name, 120)
        .unwrap_or_else(|| format!("{} Organization", display_name));

    let database_url = env::var("DATABASE_URL")?;
    let pool = PgPoolOptions::new()
        .max_connections(1)
        .connect(&database_url)
        .await?;
    let mut tx = pool.begin().await?;

    // Prevent two simultaneous onboarding requests for the same Neon user
    // from creating duplicate workspaces.
    sqlx::query("SELECT pg_advisory_xact_lock(hashtext($1)::bigint)")
        .bind(&claims.sub)
        .execute(&mut *tx)
        .await?;

    let existing_by_subject = sqlx::query(
        r#"
        SELECT id::text AS id
        FROM app_users
        WHERE auth_provider = 'neon'
          AND auth_subject = $1
        LIMIT 1
        "#,
    )
    .bind(&claims.sub)
    .fetch_optional(&mut *tx)
    .await?;

    // Email matching is only used for a pre-created invited record and only
    // when Neon says that email has been verified.
    let invited_by_email = if existing_by_subject.is_none()
        && claims.email_verified.unwrap_or(false)
    {
        sqlx::query(
            r#"
            SELECT id::text AS id
            FROM app_users
            WHERE LOWER(email) = LOWER($1)
              AND (auth_subject IS NULL OR auth_provider IS NULL)
            LIMIT 1
            "#,
        )
        .bind(&email)
        .fetch_optional(&mut *tx)
        .await?
    } else {
        None
    };

    let existing_user = existing_by_subject.or(invited_by_email);

    let user_id = if let Some(row) = existing_user {
        let id: String = row.get("id");
        sqlx::query(
            r#"
            UPDATE app_users
            SET email = $2,
                display_name = $3,
                auth_provider = 'neon',
                auth_subject = $1,
                status = 'active',
                updated_at = NOW()
            WHERE id = $4::uuid
            "#,
        )
        .bind(&claims.sub)
        .bind(&email)
        .bind(&display_name)
        .bind(&id)
        .execute(&mut *tx)
        .await?;
        id
    } else {
        sqlx::query(
            r#"
            INSERT INTO app_users (email, display_name, auth_provider, auth_subject)
            VALUES ($1, $2, 'neon', $3)
            RETURNING id::text AS id
            "#,
        )
        .bind(&email)
        .bind(&display_name)
        .bind(&claims.sub)
        .fetch_one(&mut *tx)
        .await?
        .get("id")
    };

    if let Some(row) = sqlx::query(
        r#"
        SELECT o.id::text AS id,
               o.name,
               o.slug,
               r.name AS role
        FROM organization_members om
        JOIN organizations o ON o.id = om.organization_id
        JOIN roles r ON r.id = om.role_id
        WHERE om.user_id = $1::uuid
          AND om.status = 'active'
        ORDER BY om.joined_at
        LIMIT 1
        "#,
    )
    .bind(&user_id)
    .fetch_optional(&mut *tx)
    .await?
    {
        tx.commit().await?;
        return Ok(json!({
            "organization": {
                "id": row.get::<String, _>("id"),
                "name": row.get::<String, _>("name"),
                "slug": row.get::<String, _>("slug"),
                "role": row.get::<String, _>("role")
            },
            "created": false
        }));
    }

    // Claim the one pre-auth workspace containing existing client data, if it
    // has not already been claimed. The row lock prevents two users from
    // claiming it at the same time. No organization UUID is hardcoded.
    let legacy_workspace = sqlx::query(
        r#"
        SELECT o.id::text AS id
        FROM organizations o
        WHERE EXISTS (
            SELECT 1
            FROM clients c
            WHERE c.organization_id = o.id
        )
          AND NOT EXISTS (
            SELECT 1
            FROM organization_members om
            WHERE om.organization_id = o.id
          )
        ORDER BY o.created_at
        LIMIT 1
        FOR UPDATE OF o SKIP LOCKED
        "#,
    )
    .fetch_optional(&mut *tx)
    .await?;

    let (organization_id, claimed_existing_workspace) = if let Some(row) = legacy_workspace {
        (row.get::<String, _>("id"), true)
    } else {
        let slug = unique_slug(&organization_name, &user_id);
        let row = sqlx::query(
            r#"
            INSERT INTO organizations (name, slug)
            VALUES ($1, $2)
            RETURNING id::text AS id
            "#,
        )
        .bind(&organization_name)
        .bind(slug)
        .fetch_one(&mut *tx)
        .await?;
        (row.get::<String, _>("id"), false)
    };

    create_default_roles(&mut tx, &organization_id).await?;

    let owner_role: String = sqlx::query_scalar(
        r#"
        SELECT id::text
        FROM roles
        WHERE organization_id = $1::uuid
          AND name = 'Owner'
        "#,
    )
    .bind(&organization_id)
    .fetch_one(&mut *tx)
    .await?;

    sqlx::query(
        r#"
        INSERT INTO organization_members (
            organization_id,
            user_id,
            role_id,
            status
        )
        VALUES ($1::uuid, $2::uuid, $3::uuid, 'active')
        ON CONFLICT (organization_id, user_id)
        DO UPDATE SET role_id = EXCLUDED.role_id, status = 'active'
        "#,
    )
    .bind(&organization_id)
    .bind(&user_id)
    .bind(&owner_role)
    .execute(&mut *tx)
    .await?;

    let organization = sqlx::query(
        r#"
        SELECT id::text AS id, name, slug
        FROM organizations
        WHERE id = $1::uuid
        "#,
    )
    .bind(&organization_id)
    .fetch_one(&mut *tx)
    .await?;

    tx.commit().await?;

    Ok(json!({
        "organization": {
            "id": organization.get::<String, _>("id"),
            "name": organization.get::<String, _>("name"),
            "slug": organization.get::<String, _>("slug"),
            "role": "Owner"
        },
        "created": true,
        "claimedExistingWorkspace": claimed_existing_workspace
    }))
}

fn clean_optional(value: Option<String>, max_length: usize) -> Option<String> {
    let cleaned = value?
        .trim()
        .chars()
        .take(max_length)
        .collect::<String>();

    if cleaned.is_empty() {
        None
    } else {
        Some(cleaned)
    }
}

fn clean_required(
    value: Option<String>,
    missing_message: &'static str,
    max_length: usize,
) -> Result<String, Error> {
    clean_optional(value, max_length).ok_or_else(|| missing_message.into())
}

fn unique_slug(organization_name: &str, user_id: &str) -> String {
    let base = slugify(organization_name);
    let suffix: String = user_id
        .chars()
        .filter(|character| character.is_ascii_alphanumeric())
        .take(12)
        .collect();

    format!(
        "{}-{}",
        if base.is_empty() { "organization" } else { &base },
        suffix.to_lowercase()
    )
}

fn slugify(value: &str) -> String {
    let mut output = String::new();
    let mut previous_was_dash = false;

    for character in value.to_lowercase().chars() {
        if character.is_ascii_alphanumeric() {
            output.push(character);
            previous_was_dash = false;
        } else if !previous_was_dash && !output.is_empty() {
            output.push('-');
            previous_was_dash = true;
        }
    }

    output.trim_matches('-').to_string()
}

async fn create_default_roles(
    tx: &mut sqlx::Transaction<'_, sqlx::Postgres>,
    organization_id: &str,
) -> Result<(), Error> {
    for role in ["Owner", "Admin", "Manager", "Teller", "Viewer"] {
        sqlx::query(
            r#"
            INSERT INTO roles (organization_id, name, is_system)
            VALUES ($1::uuid, $2, TRUE)
            ON CONFLICT (organization_id, name) DO NOTHING
            "#,
        )
        .bind(organization_id)
        .bind(role)
        .execute(&mut **tx)
        .await?;
    }

    sqlx::query(
        r#"
        INSERT INTO role_permissions (role_id, permission_code)
        SELECT r.id, p.code
        FROM roles r
        CROSS JOIN permissions p
        WHERE r.organization_id = $1::uuid
          AND r.name IN ('Owner', 'Admin')
        ON CONFLICT DO NOTHING
        "#,
    )
    .bind(organization_id)
    .execute(&mut **tx)
    .await?;

    sqlx::query(
        r#"
        INSERT INTO role_permissions (role_id, permission_code)
        SELECT r.id, p.code
        FROM roles r
        JOIN permissions p ON p.code IN (
            'clients.view',
            'clients.create',
            'clients.update',
            'clients.delete',
            'transactions.view'
        )
        WHERE r.organization_id = $1::uuid
          AND r.name = 'Manager'
        ON CONFLICT DO NOTHING
        "#,
    )
    .bind(organization_id)
    .execute(&mut **tx)
    .await?;

    sqlx::query(
        r#"
        INSERT INTO role_permissions (role_id, permission_code)
        SELECT r.id, p.code
        FROM roles r
        JOIN permissions p ON p.code IN (
            'clients.view',
            'transactions.view',
            'transactions.deposit',
            'transactions.withdraw'
        )
        WHERE r.organization_id = $1::uuid
          AND r.name = 'Teller'
        ON CONFLICT DO NOTHING
        "#,
    )
    .bind(organization_id)
    .execute(&mut **tx)
    .await?;

    sqlx::query(
        r#"
        INSERT INTO role_permissions (role_id, permission_code)
        SELECT r.id, p.code
        FROM roles r
        JOIN permissions p ON p.code IN ('clients.view', 'transactions.view')
        WHERE r.organization_id = $1::uuid
          AND r.name = 'Viewer'
        ON CONFLICT DO NOTHING
        "#,
    )
    .bind(organization_id)
    .execute(&mut **tx)
    .await?;

    Ok(())
}
