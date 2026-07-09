#include "BankService.h"

#include <algorithm>

BankService::BankService(ClientStorage storage)
    : m_storage(std::move(storage))
{
}

std::vector<Client> BankService::getAllClients() const
{
    return m_storage.load();
}

std::optional<Client> BankService::getClientByAccountNumber(const std::string& accountNumber) const
{
    std::vector<Client> clients = m_storage.load();

    for (const Client& client : clients)
    {
        if (client.accountNumber == accountNumber)
            return client;
    }

    return std::nullopt;
}

bool BankService::addClient(const Client& client, std::string& errorMessage)
{
    if (!isValidClientForCreate(client, errorMessage))
        return false;

    std::vector<Client> clients = m_storage.load();

    auto exists = std::any_of(clients.begin(), clients.end(), [&](const Client& current) {
        return current.accountNumber == client.accountNumber;
    });

    if (exists)
    {
        errorMessage = "Client account number already exists.";
        return false;
    }

    clients.push_back(client);

    if (!m_storage.save(clients))
    {
        errorMessage = "Could not save Clients.txt.";
        return false;
    }

    return true;
}

bool BankService::updateClient(const std::string& accountNumber, const Client& updatedClient, std::string& errorMessage)
{
    std::vector<Client> clients = m_storage.load();

    for (Client& client : clients)
    {
        if (client.accountNumber == accountNumber)
        {
            client.pinCode = updatedClient.pinCode;
            client.name = updatedClient.name;
            client.phone = updatedClient.phone;
            client.accountBalance = updatedClient.accountBalance;

            if (!m_storage.save(clients))
            {
                errorMessage = "Could not save Clients.txt.";
                return false;
            }

            return true;
        }
    }

    errorMessage = "Client not found.";
    return false;
}

bool BankService::deleteClient(const std::string& accountNumber, std::string& errorMessage)
{
    std::vector<Client> clients = m_storage.load();

    const size_t oldSize = clients.size();
    clients.erase(
        std::remove_if(clients.begin(), clients.end(), [&](const Client& client) {
            return client.accountNumber == accountNumber;
        }),
        clients.end());

    if (clients.size() == oldSize)
    {
        errorMessage = "Client not found.";
        return false;
    }

    if (!m_storage.save(clients))
    {
        errorMessage = "Could not save Clients.txt.";
        return false;
    }

    return true;
}

bool BankService::deposit(const std::string& accountNumber, double amount, std::string& errorMessage)
{
    if (amount <= 0)
    {
        errorMessage = "Deposit amount must be greater than zero.";
        return false;
    }

    std::vector<Client> clients = m_storage.load();

    for (Client& client : clients)
    {
        if (client.accountNumber == accountNumber)
        {
            client.accountBalance += amount;

            if (!m_storage.save(clients))
            {
                errorMessage = "Could not save Clients.txt.";
                return false;
            }

            return true;
        }
    }

    errorMessage = "Client not found.";
    return false;
}

bool BankService::withdraw(const std::string& accountNumber, double amount, std::string& errorMessage)
{
    if (amount <= 0)
    {
        errorMessage = "Withdraw amount must be greater than zero.";
        return false;
    }

    std::vector<Client> clients = m_storage.load();

    for (Client& client : clients)
    {
        if (client.accountNumber == accountNumber)
        {
            if (amount > client.accountBalance)
            {
                errorMessage = "Amount exceeds the client balance.";
                return false;
            }

            client.accountBalance -= amount;

            if (!m_storage.save(clients))
            {
                errorMessage = "Could not save Clients.txt.";
                return false;
            }

            return true;
        }
    }

    errorMessage = "Client not found.";
    return false;
}

double BankService::getTotalBalances() const
{
    double total = 0.0;
    std::vector<Client> clients = m_storage.load();

    for (const Client& client : clients)
        total += client.accountBalance;

    return total;
}

bool BankService::isValidClientForCreate(const Client& client, std::string& errorMessage)
{
    if (client.accountNumber.empty())
    {
        errorMessage = "Account number is required.";
        return false;
    }

    if (client.pinCode.empty())
    {
        errorMessage = "Pin code is required.";
        return false;
    }

    if (client.name.empty())
    {
        errorMessage = "Name is required.";
        return false;
    }

    if (client.accountBalance < 0)
    {
        errorMessage = "Balance cannot be negative.";
        return false;
    }

    return true;
}
