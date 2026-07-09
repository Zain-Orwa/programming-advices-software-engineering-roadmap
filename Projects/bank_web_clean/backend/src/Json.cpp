#include "Json.h"

#include <cctype>
#include <sstream>

std::string jsonEscape(const std::string& value)
{
    std::ostringstream output;

    for (char ch : value)
    {
        switch (ch)
        {
        case '"':
            output << "\\\"";
            break;
        case '\\':
            output << "\\\\";
            break;
        case '\n':
            output << "\\n";
            break;
        case '\r':
            output << "\\r";
            break;
        case '\t':
            output << "\\t";
            break;
        default:
            output << ch;
            break;
        }
    }

    return output.str();
}

static size_t findKey(const std::string& body, const std::string& key)
{
    return body.find("\"" + key + "\"");
}

static size_t skipSpaces(const std::string& body, size_t index)
{
    while (index < body.size() && std::isspace(static_cast<unsigned char>(body[index])))
        ++index;

    return index;
}

std::optional<std::string> jsonStringValue(const std::string& body, const std::string& key)
{
    size_t position = findKey(body, key);
    if (position == std::string::npos)
        return std::nullopt;

    position = body.find(':', position);
    if (position == std::string::npos)
        return std::nullopt;

    position = skipSpaces(body, position + 1);
    if (position >= body.size() || body[position] != '"')
        return std::nullopt;

    ++position;
    std::string result;

    while (position < body.size())
    {
        char ch = body[position++];

        if (ch == '"')
            return result;

        if (ch == '\\' && position < body.size())
        {
            char escaped = body[position++];
            switch (escaped)
            {
            case 'n':
                result += '\n';
                break;
            case 'r':
                result += '\r';
                break;
            case 't':
                result += '\t';
                break;
            default:
                result += escaped;
                break;
            }
        }
        else
        {
            result += ch;
        }
    }

    return std::nullopt;
}

std::optional<double> jsonNumberValue(const std::string& body, const std::string& key)
{
    size_t position = findKey(body, key);
    if (position == std::string::npos)
        return std::nullopt;

    position = body.find(':', position);
    if (position == std::string::npos)
        return std::nullopt;

    position = skipSpaces(body, position + 1);

    size_t end = position;
    while (end < body.size())
    {
        char ch = body[end];
        if (!(std::isdigit(static_cast<unsigned char>(ch)) || ch == '-' || ch == '+' || ch == '.'))
            break;
        ++end;
    }

    if (end == position)
        return std::nullopt;

    try
    {
        return std::stod(body.substr(position, end - position));
    }
    catch (...)
    {
        return std::nullopt;
    }
}

std::string jsonError(const std::string& message)
{
    return "{\"error\":\"" + jsonEscape(message) + "\"}";
}

std::string jsonMessage(const std::string& message)
{
    return "{\"message\":\"" + jsonEscape(message) + "\"}";
}
