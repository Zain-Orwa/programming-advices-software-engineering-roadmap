# Bank Web Learning Project

This version avoids external C++ dependencies. There is no `nlohmann/json.hpp` and no `httplib.h`.

Folder structure:

```txt
bank_web/
  .vscode/
    c_cpp_properties.json
    settings.json
  backend/
    CMakeLists.txt
    include/
      BankService.h
      Client.h
      HttpServer.h
      Json.h
      Routes.h
      Storage.h
    src/
      BankService.cpp
      Client.cpp
      HttpServer.cpp
      Json.cpp
      Routes.cpp
      Storage.cpp
      main.cpp
    data/
      Clients.txt
  frontend/
    index.html
    app.js
    style.css
```

## Run backend

Open a terminal from the project root:

```bash
cd backend
cmake -S . -B build
cmake --build build
./build/bank_api
```

The API runs at:

```txt
http://localhost:8080
```

Test it:

```bash
curl http://localhost:8080/api/health
curl http://localhost:8080/api/clients
```

## Run frontend

Open `frontend/index.html` in the browser, or use the VS Code Live Server extension.

## API routes

```txt
GET    /api/health
GET    /api/clients
GET    /api/clients/{accountNumber}
POST   /api/clients
PUT    /api/clients/{accountNumber}
DELETE /api/clients/{accountNumber}
POST   /api/clients/{accountNumber}/deposit
POST   /api/clients/{accountNumber}/withdraw
GET    /api/balances/total
```

Example add client:

```bash
curl -X POST http://localhost:8080/api/clients \
  -H "Content-Type: application/json" \
  -d '{"accountNumber":"1003","pinCode":"1111","name":"Test Client","phone":"0600000003","accountBalance":500}'
```

This project is for learning only. Do not use real banking or private data.
