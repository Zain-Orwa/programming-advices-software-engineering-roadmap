#pragma once

#include "Client.h"
#include "Storage.h"

#include <optional>
#include <string>
#include <vector>

class BankService
{
public:
    explicit BankService(ClientStorage storage);

    std::vector<Client> getAllClients() const;
    std::optional<Client> getClientByAccountNumber(const std::string& accountNumber) const;

    bool addClient(const Client& client, std::string& errorMessage);
    bool updateClient(const std::string& accountNumber, const Client& updatedClient, std::string& errorMessage);
    bool deleteClient(const std::string& accountNumber, std::string& errorMessage);

    bool deposit(const std::string& accountNumber, double amount, std::string& errorMessage);
    bool withdraw(const std::string& accountNumber, double amount, std::string& errorMessage);

    double getTotalBalances() const;

private:
    ClientStorage m_storage;

    static bool isValidClientForCreate(const Client& client, std::string& errorMessage);
};
