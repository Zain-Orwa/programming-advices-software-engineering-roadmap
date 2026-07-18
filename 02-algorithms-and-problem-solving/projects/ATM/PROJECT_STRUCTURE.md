# ATM project structure

All project files are intentionally kept directly in the `ATM` root directory to match a simple 42-style project layout.

```text
ATM/
├── Makefile
├── atm.h
├── main.cpp
├── atm.cpp
├── user_inputs.cpp
├── find_lookup.cpp
├── file_io.cpp
├── utils.cpp
├── show_screen.cpp
├── deposit.cpp
├── withdraw.cpp
├── balance.cpp
├── Clients.txt
└── PROJECT_STRUCTURE.md
```

## Responsibility of each file

- `main.cpp`: program entry point only.
- `atm.cpp`: login flow and high-level ATM control.
- `user_inputs.cpp`: functions that read values from the user.
- `find_lookup.cpp`: client search and client-loading logic.
- `file_io.cpp`: converting client records and reading client data from files.
- `utils.cpp`: reusable general helper functions, such as string splitting.
- `show_screen.cpp`: clearing the terminal and printing screens or menus.
- `deposit.cpp`: deposit operations.
- `withdraw.cpp`: withdrawal operations.
- `balance.cpp`: balance-related operations.
- `atm.h`: structures, constants, includes, and function declarations shared by the `.cpp` files.
- `Clients.txt`: persistent client data.
- `Makefile`: original uploaded 42-style Makefile, preserved unchanged.

## Important note

The Makefile was preserved exactly as uploaded. At present, its `SRCS` list does not contain `file_io.cpp` or `find_lookup.cpp`. Add them later when you want those files compiled and linked. No source code was modified in this package.
