use serde_json::{json, Value};
use vercel_runtime::{run, service_fn, Error, Request};

#[tokio::main]
async fn main() -> Result<(), Error> {
    run(service_fn(handler)).await
}

async fn handler(_request: Request) -> Result<Value, Error> {
    Ok(json!({
        "app": "System Bank",
        "message": "Rust API is working",
        "status": "ok"
    }))
}
