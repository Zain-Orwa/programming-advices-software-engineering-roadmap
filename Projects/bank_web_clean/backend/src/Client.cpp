#include "Client.h"
#include "Json.h"

#include <sstream>
#include <stdexcept>

std::vector<std::string> splitString(const std::string& text, const std::string& delimiter)
{
    std::vector<std::string> result;
    size_t start = 0;
    size_t position = text.find(delimiter);

    while (position != std::string::npos)
    {
        result.push_back(text.substr(start, position - start));
        start = position + delimiter.length();
        position = text.find(delimiter, start);
    }

    result.push_back(text.substr(start));
    return result;
}

Client clientFromLine(const std::string& line, const std::string& separator)
{
    std::vector<std::string> data = splitString(line, separator);

    if (data.size() < 5)
        throw std::runtime_error("Bad client line in Clients.txt");

    Client client;
    client.accountNumber = data[0];
    client.pinCode = data[1];
    client.name = data[2];
    client.phone = data[3];
    client.accountBalance = std::stod(data[4]);

    return client;
}

std::string clientToLine(const Client& client, const std::string& separator)
{
    std::ostringstream output;

    output << client.accountNumber << separator
           << client.pinCode << separator
           << client.name << separator
           << client.phone << separator
           << client.accountBalance;

    return output.str();
}

std::string clientToPublicJson(const Client& client)
{
    std::ostringstream output;

    output << "{"
           << "\"accountNumber\":\"" << jsonEscape(client.accountNumber) << "\","
           << "\"name\":\"" << jsonEscape(client.name) << "\","
           << "\"phone\":\"" << jsonEscape(client.phone) << "\","
           << "\"accountBalance\":" << client.accountBalance
           << "}";

    return output.str();
}

std::string clientsToPublicJson(const std::vector<Client>& clients)
{
    std::ostringstream output;

    output << "[";
    for (size_t index = 0; index < clients.size(); ++index)
    {
        if (index > 0)
            output << ",";
        output << clientToPublicJson(clients[index]);
    }
    output << "]";

    return output.str();
}
