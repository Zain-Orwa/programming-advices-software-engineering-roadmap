#pragma once

#include <optional>
#include <string>

std::string jsonEscape(const std::string& value);
std::optional<std::string> jsonStringValue(const std::string& body, const std::string& key);
std::optional<double> jsonNumberValue(const std::string& body, const std::string& key);
std::string jsonError(const std::string& message);
std::string jsonMessage(const std::string& message);
