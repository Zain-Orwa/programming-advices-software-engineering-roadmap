use serde_json::{json, Value};
use sqlx::{postgres::PgPoolOptions, Row};
use std::env;
use vercel_runtime::{run, service_fn, Error, Request};

#[tokio::main]
async fn main() -> Result<(), Error> {
    run(service_fn(handler)).await
}

async fn handler(_req: Request) -> Result<Value, Error> {
    let database_url = env::var("DATABASE_URL")?;

    let pool = PgPoolOptions::new()
        .max_connections(1)
        .connect(&database_url)
        .await?;

    let row = sqlx::query(
        r#"
        SELECT COALESCE(SUM(account_balance), 0) AS total_balances
        FROM clients
        "#,
    )
    .fetch_one(&pool)
    .await?;

    let total_balances: f64 = row.get("total_balances");

    Ok(json!({
        "totalBalances": total_balances
    }))
}