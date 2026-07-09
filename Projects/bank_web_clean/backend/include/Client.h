#pragma once

#include <string>
#include <vector>

struct Client
{
    std::string accountNumber;
    std::string pinCode;
    std::string name;
    std::string phone;
    double accountBalance = 0.0;
    bool markForDelete = false;
};

std::vector<std::string> splitString(const std::string& text, const std::string& delimiter);
Client clientFromLine(const std::string& line, const std::string& separator = "#//#");
std::string clientToLine(const Client& client, const std::string& separator = "#//#");

// Public JSON does not expose pinCode.
std::string clientToPublicJson(const Client& client);
std::string clientsToPublicJson(const std::vector<Client>& clients);
