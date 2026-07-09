#pragma once

#include <functional>
#include <map>
#include <string>

struct HttpRequest
{
    std::string method;
    std::string path;
    std::string body;
    std::map<std::string, std::string> headers;
};

struct HttpResponse
{
    int status = 200;
    std::string body = "{}";
    std::string contentType = "application/json";
};

class HttpServer
{
public:
    using Handler = std::function<HttpResponse(const HttpRequest& request)>;

    explicit HttpServer(int port);

    void setHandler(Handler handler);
    bool listenAndServe();
    void stop();

private:
    int m_port;
    bool m_running = false;
    Handler m_handler;

    static HttpRequest parseRequest(const std::string& rawRequest);
    static std::string buildResponse(const HttpResponse& response);
    static std::string statusText(int status);
};
