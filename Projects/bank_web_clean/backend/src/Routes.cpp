#include "Routes.h"
#include "Json.h"

#include <sstream>

static bool startsWith(const std::string& value, const std::string& prefix)
{
    return value.rfind(prefix, 0) == 0;
}

static std::string pathAfter(const std::string& path, const std::string& prefix)
{
    if (!startsWith(path, prefix))
        return "";

    return path.substr(prefix.size());
}

static Client clientFromJsonBody(const std::string& body, bool requireAccountNumber)
{
    Client client;

    if (auto value = jsonStringValue(body, "accountNumber"))
        client.accountNumber = *value;

    if (auto value = jsonStringValue(body, "pinCode"))
        client.pinCode = *value;

    if (auto value = jsonStringValue(body, "name"))
        client.name = *value;

    if (auto value = jsonStringValue(body, "phone"))
        client.phone = *value;

    if (auto value = jsonNumberValue(body, "accountBalance"))
        client.accountBalance = *value;

    if (requireAccountNumber && client.accountNumber.empty())
        client.accountNumber = "";

    return client;
}

HttpResponse handleApiRequest(const HttpRequest& request, BankService& bankService)
{
    HttpResponse response;

    if (request.method == "OPTIONS")
    {
        response.status = 204;
        response.body = "";
        return response;
    }

    if (request.method == "GET" && request.path == "/api/health")
    {
        response.body = "{\"ok\":true}";
        return response;
    }

    if (request.method == "GET" && request.path == "/api/clients")
    {
        response.body = "{\"clients\":" + clientsToPublicJson(bankService.getAllClients()) + "}";
        return response;
    }

    if (request.method == "GET" && request.path == "/api/balances/total")
    {
        std::ostringstream output;
        output << "{\"totalBalances\":" << bankService.getTotalBalances() << "}";
        response.body = output.str();
        return response;
    }

    if (request.method == "POST" && request.path == "/api/clients")
    {
        Client client = clientFromJsonBody(request.body, true);
        std::string errorMessage;

        if (!bankService.addClient(client, errorMessage))
        {
            response.status = 400;
            response.body = jsonError(errorMessage);
            return response;
        }

        response.status = 201;
        response.body = jsonMessage("Client added successfully.");
        return response;
    }

    const std::string clientsPrefix = "/api/clients/";

    if (startsWith(request.path, clientsPrefix))
    {
        std::string rest = pathAfter(request.path, clientsPrefix);
        std::string accountNumber = rest;
        std::string action;

        size_t slash = rest.find('/');
        if (slash != std::string::npos)
        {
            accountNumber = rest.substr(0, slash);
            action = rest.substr(slash + 1);
        }

        if (accountNumber.empty())
        {
            response.status = 400;
            response.body = jsonError("Account number is required.");
            return response;
        }

        if (request.method == "GET" && action.empty())
        {
            auto client = bankService.getClientByAccountNumber(accountNumber);
            if (!client)
            {
                response.status = 404;
                response.body = jsonError("Client not found.");
                return response;
            }

            response.body = "{\"client\":" + clientToPublicJson(*client) + "}";
            return response;
        }

        if (request.method == "PUT" && action.empty())
        {
            Client client = clientFromJsonBody(request.body, false);
            std::string errorMessage;

            if (!bankService.updateClient(accountNumber, client, errorMessage))
            {
                response.status = 400;
                response.body = jsonError(errorMessage);
                return response;
            }

            response.body = jsonMessage("Client updated successfully.");
            return response;
        }

        if (request.method == "DELETE" && action.empty())
        {
            std::string errorMessage;

            if (!bankService.deleteClient(accountNumber, errorMessage))
            {
                response.status = 404;
                response.body = jsonError(errorMessage);
                return response;
            }

            response.body = jsonMessage("Client deleted successfully.");
            return response;
        }

        if (request.method == "POST" && (action == "deposit" || action == "withdraw"))
        {
            auto amount = jsonNumberValue(request.body, "amount");
            if (!amount)
            {
                response.status = 400;
                response.body = jsonError("Amount is required.");
                return response;
            }

            std::string errorMessage;
            bool ok = false;

            if (action == "deposit")
                ok = bankService.deposit(accountNumber, *amount, errorMessage);
            else
                ok = bankService.withdraw(accountNumber, *amount, errorMessage);

            if (!ok)
            {
                response.status = 400;
                response.body = jsonError(errorMessage);
                return response;
            }

            response.body = jsonMessage("Transaction completed successfully.");
            return response;
        }
    }

    response.status = 404;
    response.body = jsonError("Route not found.");
    return response;
}
