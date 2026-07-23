# Bankana Frontend v11 — Operation Back Navigation

This version keeps the complete v10 Client List workspace unchanged and adds clear navigation to every operation screen.

- The private centered main menu remains the first screen.
- The Client List HTML, tools, table, actions, and layout are unchanged from v10.
- Add, Delete, Update, Find, Transactions, Deposit, Withdraw, Total Balance, and Exit now include a glowing back widget.
- Most operation back widgets return directly to the Main Menu.
- **Add New Client is context-aware:**
  - Opened from the Main Menu → back returns to the Main Menu.
  - Opened from the Client List → back returns to the Client List.
- Existing transaction Back buttons still return to the Transactions menu.
- Backend API code is unchanged.

## Replace

Replace your project `frontend/` folder with this package's `frontend/` folder.

The included `api/clients.rs` is unchanged and is included only so the zip remains a complete Bankana update package.

## Check and deploy

```bash
node --check frontend/app.js
cargo check --bin clients
vercel --prod
```
