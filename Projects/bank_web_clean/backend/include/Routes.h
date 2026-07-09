#pragma once

#include "BankService.h"
#include "HttpServer.h"

HttpResponse handleApiRequest(const HttpRequest& request, BankService& bankService);
