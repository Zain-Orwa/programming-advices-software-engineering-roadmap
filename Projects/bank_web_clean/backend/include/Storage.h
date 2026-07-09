#pragma once

#include "Client.h"

#include <string>
#include <vector>

class ClientStorage
{
public:
    explicit ClientStorage(std::string filePath);

    std::vector<Client> load() const;
    bool save(const std::vector<Client>& clients) const;

    const std::string& filePath() const;

private:
    std::string m_filePath;
};
