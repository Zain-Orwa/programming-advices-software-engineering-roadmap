# System Bank v17 — Tenant Identity

This version completes authenticated tenant selection for the client API.

## What changes

- No organization UUID is hardcoded in Rust or JavaScript.
- The first authenticated account claims the existing unclaimed workspace that already contains client records.
- Every later new account receives a separate empty organization.
- Returning users keep their existing organization membership.
- Every client CRUD request verifies the Neon Auth JWT and checks a database permission.
- The browser refreshes expiring access tokens without storing them in local storage.
- The old database default organization is removed so an unscoped insert cannot silently enter a shared workspace.

## Replace

- `frontend/app.js`
- `api/clients.rs`
- `api/onboarding.rs`
- `src/auth.rs`
- `Cargo.toml`

Keep your other project files unchanged. The included `frontend/index.html` and `frontend/style.css` are unchanged from v16.

## Run the migration

In the Neon SQL Editor, run:

```text
migrations/002_finalize_tenant_isolation.sql
```

The final verification should show:

- `organization_id` is not nullable
- `column_default` is null
- `clients_without_organization` is `0`

## Check locally

```bash
node --check frontend/app.js
cargo check --bin clients --bin onboarding
```

## Deploy

```bash
vercel --prod
```

## First-account behaviour

Create or sign in with the account that should own the existing System Bank client list first. That account claims the only unclaimed organization containing existing client records. New accounts created afterward start with empty client lists.
