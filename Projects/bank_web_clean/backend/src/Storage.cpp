#include "Storage.h"

#include <filesystem>
#include <fstream>
#include <iostream>

ClientStorage::ClientStorage(std::string filePath)
    : m_filePath(std::move(filePath))
{
}

std::vector<Client> ClientStorage::load() const
{
    std::vector<Client> clients;
    std::ifstream file(m_filePath);

    if (!file.is_open())
        return clients;

    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty())
            continue;

        try
        {
            clients.push_back(clientFromLine(line));
        }
        catch (const std::exception& error)
        {
            std::cerr << "Skipping bad line: " << error.what() << "\n";
        }
    }

    return clients;
}

bool ClientStorage::save(const std::vector<Client>& clients) const
{
    std::filesystem::path path(m_filePath);

    if (path.has_parent_path())
        std::filesystem::create_directories(path.parent_path());

    std::ofstream file(m_filePath, std::ios::trunc);
    if (!file.is_open())
        return false;

    for (const Client& client : clients)
        file << clientToLine(client) << '\n';

    return true;
}

const std::string& ClientStorage::filePath() const
{
    return m_filePath;
}
