# System Bank v18 — Complete Authentication

This version fixes the authentication entry flow and keeps all v17 tenant isolation.

## Replace / add

Replace:
- `frontend/index.html`
- `frontend/style.css`
- `frontend/app.js`

Add:
- `api/auth.js`

No database migration is required. No Cargo file changes are required.

## What changed

- Same-origin Neon Auth proxy to prevent privacy browsers from blocking session cookies
- Working sign-up and session restoration flow
- Show / hide password controls
- Repeat-password validation
- Forgot-password email flow
- Reset-password screen from emailed token
- Clear authentication error messages

## Checks

```bash
node --check frontend/app.js
node --check api/auth.js
cargo check --bin clients --bin onboarding
```

Then deploy with:

```bash
vercel --prod
```
