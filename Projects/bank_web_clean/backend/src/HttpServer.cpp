#include "HttpServer.h"

#include <algorithm>
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sstream>
#include <sys/socket.h>
#include <unistd.h>

HttpServer::HttpServer(int port)
    : m_port(port)
{
}

void HttpServer::setHandler(Handler handler)
{
    m_handler = std::move(handler);
}

bool HttpServer::listenAndServe()
{
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0)
    {
        std::cerr << "Could not create socket.\n";
        return false;
    }

    int option = 1;
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(static_cast<uint16_t>(m_port));

    if (bind(serverSocket, reinterpret_cast<sockaddr*>(&address), sizeof(address)) < 0)
    {
        std::cerr << "Could not bind to port " << m_port << ".\n";
        close(serverSocket);
        return false;
    }

    if (listen(serverSocket, 20) < 0)
    {
        std::cerr << "Could not listen on port " << m_port << ".\n";
        close(serverSocket);
        return false;
    }

    m_running = true;
    std::cout << "API server running at http://localhost:" << m_port << "\n";

    while (m_running)
    {
        int clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket < 0)
            continue;

        std::string rawRequest;
        char buffer[4096];

        while (true)
        {
            ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
            if (bytesRead <= 0)
                break;

            rawRequest.append(buffer, static_cast<size_t>(bytesRead));

            size_t headerEnd = rawRequest.find("\r\n\r\n");
            if (headerEnd != std::string::npos)
            {
                HttpRequest request = parseRequest(rawRequest);
                auto contentLengthIt = request.headers.find("content-length");

                size_t expectedBodyLength = 0;
                if (contentLengthIt != request.headers.end())
                    expectedBodyLength = static_cast<size_t>(std::stoul(contentLengthIt->second));

                size_t currentBodyLength = rawRequest.size() - (headerEnd + 4);
                if (currentBodyLength >= expectedBodyLength)
                    break;
            }
        }

        HttpResponse response;

        try
        {
            HttpRequest request = parseRequest(rawRequest);

            if (m_handler)
                response = m_handler(request);
            else
            {
                response.status = 500;
                response.body = "{\"error\":\"No route handler configured.\"}";
            }
        }
        catch (const std::exception& error)
        {
            response.status = 500;
            response.body = std::string("{\"error\":\"") + error.what() + "\"}";
        }

        std::string rawResponse = buildResponse(response);
        send(clientSocket, rawResponse.c_str(), rawResponse.size(), 0);
        close(clientSocket);
    }

    close(serverSocket);
    return true;
}

void HttpServer::stop()
{
    m_running = false;
}

HttpRequest HttpServer::parseRequest(const std::string& rawRequest)
{
    HttpRequest request;
    std::istringstream stream(rawRequest);
    std::string line;

    if (std::getline(stream, line))
    {
        if (!line.empty() && line.back() == '\r')
            line.pop_back();

        std::istringstream requestLine(line);
        requestLine >> request.method >> request.path;
    }

    while (std::getline(stream, line))
    {
        if (!line.empty() && line.back() == '\r')
            line.pop_back();

        if (line.empty())
            break;

        size_t colon = line.find(':');
        if (colon == std::string::npos)
            continue;

        std::string key = line.substr(0, colon);
        std::string value = line.substr(colon + 1);

        while (!value.empty() && value.front() == ' ')
            value.erase(value.begin());

        std::transform(key.begin(), key.end(), key.begin(), [](unsigned char ch) {
            return static_cast<char>(std::tolower(ch));
        });

        request.headers[key] = value;
    }

    size_t headerEnd = rawRequest.find("\r\n\r\n");
    if (headerEnd != std::string::npos)
        request.body = rawRequest.substr(headerEnd + 4);

    auto contentLengthIt = request.headers.find("content-length");
    if (contentLengthIt != request.headers.end())
    {
        size_t contentLength = static_cast<size_t>(std::stoul(contentLengthIt->second));
        if (request.body.size() > contentLength)
            request.body = request.body.substr(0, contentLength);
    }

    return request;
}

std::string HttpServer::buildResponse(const HttpResponse& response)
{
    std::ostringstream output;

    output << "HTTP/1.1 " << response.status << " " << statusText(response.status) << "\r\n"
           << "Content-Type: " << response.contentType << "\r\n"
           << "Content-Length: " << response.body.size() << "\r\n"
           << "Access-Control-Allow-Origin: *\r\n"
           << "Access-Control-Allow-Methods: GET, POST, PUT, DELETE, OPTIONS\r\n"
           << "Access-Control-Allow-Headers: Content-Type\r\n"
           << "Connection: close\r\n"
           << "\r\n"
           << response.body;

    return output.str();
}

std::string HttpServer::statusText(int status)
{
    switch (status)
    {
    case 200:
        return "OK";
    case 201:
        return "Created";
    case 204:
        return "No Content";
    case 400:
        return "Bad Request";
    case 404:
        return "Not Found";
    case 405:
        return "Method Not Allowed";
    case 500:
        return "Internal Server Error";
    default:
        return "OK";
    }
}
