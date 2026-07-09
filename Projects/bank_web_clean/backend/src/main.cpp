#include "BankService.h"
#include "HttpServer.h"
#include "Routes.h"
#include "Storage.h"

#include <cstdlib>
#include <iostream>
#include <string>

int main()
{
    std::string dataFile = "data/Clients.txt";

    if (const char* environmentFile = std::getenv("CLIENTS_FILE"))
        dataFile = environmentFile;

    ClientStorage storage(dataFile);
    BankService bankService(storage);

    HttpServer server(8080);
    server.setHandler([&](const HttpRequest& request) {
        return handleApiRequest(request, bankService);
    });

    std::cout << "Using data file: " << storage.filePath() << "\n";
    std::cout << "Press Ctrl+C to stop the server.\n";

    if (!server.listenAndServe())
        return 1;

    return 0;
}
