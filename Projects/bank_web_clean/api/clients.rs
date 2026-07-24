#[path = "../src/auth.rs"]
mod auth;

use http_body_util::BodyExt;
use serde::{Deserialize, Serialize};
use serde_json::{json, Value};
use sqlx::{postgres::PgPoolOptions, Row};
use std::env;
use vercel_runtime::{run, service_fn, Error, Request};

#[derive(Serialize)]
struct Client {
    #[serde(rename = "accountNumber")]
    account_number: String,
    name: String,
    phone: String,
    #[serde(rename = "accountBalance")]
    account_balance: f64,
}

#[derive(Deserialize)]
struct ClientInput {
    #[serde(rename = "accountNumber")]
    account_number: String,
    #[serde(rename = "pinCode")]
    pin_code: String,
    name: String,
    phone: String,
    #[serde(rename = "accountBalance")]
    account_balance: f64,
}

#[derive(Deserialize)]
struct ClientUpdateInput {
    #[serde(rename = "pinCode")]
    pin_code: Option<String>,
    name: String,
    phone: String,
    #[serde(rename = "accountBalance")]
    account_balance: f64,
}

#[tokio::main]
async fn main() -> Result<(), Error> {
    run(service_fn(handler)).await
}

async fn handler(req: Request) -> Result<Value, Error> {
    match req.method().as_str() {
        "GET" => get_clients(req).await,
        "POST" => add_client(req).await,
        "DELETE" => delete_client(req).await,
        "PUT" => update_client(req).await,
        _ => Ok(json!({ "error": "Method not allowed" })),
    }
}

async fn connect_db() -> Result<sqlx::PgPool, Error> {
    let database_url = env::var("DATABASE_URL")?;

    let pool = PgPoolOptions::new()
        .max_connections(1)
        .connect(&database_url)
        .await?;

    Ok(pool)
}

fn query_param(req: &Request, key: &str) -> Option<String> {
    let query = req.uri().query()?;

    for pair in query.split('&') {
        let mut parts = pair.splitn(2, '=');
        let current_key = parts.next()?;
        let value = parts.next().unwrap_or("");

        if current_key == key {
            return Some(value.to_string());
        }
    }

    None
}

fn row_to_client(row: sqlx::postgres::PgRow) -> Client {
    let phone: Option<String> = row.get("phone");

    Client {
        account_number: row.get("account_number"),
        name: row.get("name"),
        phone: phone.unwrap_or_default(),
        account_balance: row.get("account_balance"),
    }
}

async fn get_clients(req: Request) -> Result<Value, Error> {
    let claims = auth::verify_request(&req).await?;
    let pool = connect_db().await?;
    let organization_id = auth::organization_for_permission(&pool, &claims.sub, "clients.view").await?;

    let rows = sqlx::query(
        r#"
        SELECT account_number, name, phone, account_balance
        FROM clients
        WHERE organization_id = $1::uuid
        ORDER BY account_number
        "#,
    )
    .bind(&organization_id)
    .fetch_all(&pool)
    .await?;

    let clients: Vec<Client> = rows.into_iter().map(row_to_client).collect();

    Ok(json!({ "clients": clients }))
}

async fn add_client(req: Request) -> Result<Value, Error> {
    let claims = auth::verify_request(&req).await?;
    let pool = connect_db().await?;
    let organization_id = auth::organization_for_permission(&pool, &claims.sub, "clients.create").await?;
    let body = req.into_body().collect().await?.to_bytes();
    let client: ClientInput = serde_json::from_slice(&body)?;


    sqlx::query(
        r#"
        INSERT INTO clients (
            organization_id,
            account_number,
            pin_code,
            name,
            phone,
            account_balance
        )
        VALUES ($1::uuid, $2, $3, $4, $5, $6)
        "#,
    )
    .bind(&organization_id)
    .bind(client.account_number.trim())
    .bind(client.pin_code)
    .bind(client.name.trim())
    .bind(client.phone.trim())
    .bind(client.account_balance)
    .execute(&pool)
    .await?;

    Ok(json!({ "message": "Client Added Successfully." }))
}

async fn delete_client(req: Request) -> Result<Value, Error> {
    let claims = auth::verify_request(&req).await?;
    let pool = connect_db().await?;
    let organization_id = auth::organization_for_permission(&pool, &claims.sub, "clients.delete").await?;
    let account_number = query_param(&req, "accountNumber").ok_or("Missing accountNumber")?;


    let row = sqlx::query(
        r#"
        DELETE FROM clients
        WHERE organization_id = $1::uuid
          AND account_number = $2
        RETURNING account_number, name, phone, account_balance
        "#,
    )
    .bind(&organization_id)
    .bind(account_number.trim())
    .fetch_optional(&pool)
    .await?;

    match row {
        Some(row) => Ok(json!({
            "message": "Client Deleted Successfully.",
            "client": row_to_client(row)
        })),
        None => Err("Client not found.".into()),
    }
}

async fn update_client(req: Request) -> Result<Value, Error> {
    let claims = auth::verify_request(&req).await?;
    let pool = connect_db().await?;
    let organization_id = auth::organization_for_permission(&pool, &claims.sub, "clients.update").await?;
    let account_number = query_param(&req, "accountNumber").ok_or("Missing accountNumber")?;
    let body = req.into_body().collect().await?.to_bytes();
    let client: ClientUpdateInput = serde_json::from_slice(&body)?;
    let pin_code = client.pin_code.unwrap_or_default();


    let row = sqlx::query(
        r#"
        UPDATE clients
        SET
            pin_code = CASE WHEN $3 = '' THEN pin_code ELSE $3 END,
            name = $4,
            phone = $5,
            account_balance = $6
        WHERE organization_id = $1::uuid
          AND account_number = $2
        RETURNING account_number, name, phone, account_balance
        "#,
    )
    .bind(&organization_id)
    .bind(account_number.trim())
    .bind(pin_code.trim())
    .bind(client.name.trim())
    .bind(client.phone.trim())
    .bind(client.account_balance)
    .fetch_optional(&pool)
    .await?;

    match row {
        Some(row) => Ok(json!({
            "message": "Client Updated Successfully.",
            "client": row_to_client(row)
        })),
        None => Err("Client not found.".into()),
    }
}
