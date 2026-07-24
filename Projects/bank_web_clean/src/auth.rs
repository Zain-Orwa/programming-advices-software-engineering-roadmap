use jsonwebtoken::{decode, decode_header, jwk::JwkSet, DecodingKey, Validation};
use serde::Deserialize;
use sqlx::{PgPool, Row};
use std::env;
use vercel_runtime::{Error, Request};

#[derive(Debug, Clone, Deserialize)]
pub struct AuthClaims {
    pub sub: String,
    #[serde(default)]
    pub email: Option<String>,
    #[serde(default)]
    pub name: Option<String>,
    #[serde(default, alias = "emailVerified")]
    pub email_verified: Option<bool>,
    #[serde(rename = "exp")]
    pub _expires_at: usize,
}

pub fn bearer_token(req: &Request) -> Result<&str, Error> {
    let value = req
        .headers()
        .get("authorization")
        .and_then(|header| header.to_str().ok())
        .ok_or("Missing Authorization header")?;

    value
        .strip_prefix("Bearer ")
        .or_else(|| value.strip_prefix("bearer "))
        .ok_or_else(|| "Invalid Authorization header".into())
}

pub async fn verify_request(req: &Request) -> Result<AuthClaims, Error> {
    let token = bearer_token(req)?;
    let header = decode_header(token)?;
    let kid = header.kid.as_deref().ok_or("JWT is missing kid")?;
    let jwks_url = env::var("NEON_AUTH_JWKS_URL")?;

    let jwks: JwkSet = reqwest::Client::new()
        .get(jwks_url)
        .send()
        .await?
        .error_for_status()?
        .json()
        .await?;

    let jwk = jwks.find(kid).ok_or("JWT signing key was not found")?;
    let key = DecodingKey::from_jwk(jwk)?;

    // Neon Auth signs the token and publishes the matching public key through
    // its JWKS endpoint. Expiration is validated by jsonwebtoken by default.
    let mut validation = Validation::new(header.alg);
    validation.validate_aud = false;

    Ok(decode::<AuthClaims>(token, &key, &validation)?.claims)
}

#[allow(dead_code)]
pub async fn organization_for_permission(
    pool: &PgPool,
    auth_subject: &str,
    permission: &str,
) -> Result<String, Error> {
    let row = sqlx::query(
        r#"
        SELECT om.organization_id::text AS organization_id
        FROM app_users u
        JOIN organization_members om
          ON om.user_id = u.id
         AND om.status = 'active'
        JOIN role_permissions rp ON rp.role_id = om.role_id
        WHERE u.auth_provider = 'neon'
          AND u.auth_subject = $1
          AND u.status = 'active'
          AND rp.permission_code = $2
        ORDER BY om.joined_at
        LIMIT 1
        "#,
    )
    .bind(auth_subject)
    .bind(permission)
    .fetch_optional(pool)
    .await?;

    row.map(|record| record.get::<String, _>("organization_id"))
        .ok_or_else(|| "Access denied or onboarding is incomplete".into())
}
