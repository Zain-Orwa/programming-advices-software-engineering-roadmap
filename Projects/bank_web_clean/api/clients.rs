use serde_json::{json, Value};
use vercel_runtime::{run, service_fn, Error, Request};

#[tokio::main]
async fn main() -> Result<(), Error> {
    run(service_fn(handler)).await
}

async fn handler(_req: Request) -> Result<Value, Error> {
    Ok(json!({
        "clients": [
            {
                "accountNumber": "1001",
                "name": "Ali Example",
                "phone": "0600000001",
                "accountBalance": 1500.0
            },
            {
                "accountNumber": "1002",
                "name": "Sara Example",
                "phone": "0600000002",
                "accountBalance": 2750.0
            }
        ]
    }))
}