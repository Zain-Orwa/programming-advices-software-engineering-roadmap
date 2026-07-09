# Bankana Frontend v3

Replace your current `frontend` folder with this `frontend` folder.

Keep your C++ backend running at:

```bash
cd backend
./build/bank_api
```

Run the frontend from the project root:

```bash
cd frontend
python3 -m http.server 5500
```

Open:

```txt
http://localhost:5500
```

This version updates the Transactions Menu to show only three premium action cards:

1. Deposit
2. Withdraw
3. Total Balance

Deposit and Withdraw open their own action screens and still use confirmation popups.
