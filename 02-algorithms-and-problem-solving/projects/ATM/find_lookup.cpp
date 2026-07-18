/* Find / Lookup */

#include "atm.h"

using namespace std;

bool    FindClientByAccountNumberAndPinCode(string AccountNumber, string PinCode, sClient& Client)
{
    vector<sClient> vClients = LoadClientsDataFromFile(ClientsFileName);

    for (sClient C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return (true);
        }
    }
    return (false);
}

bool    LoadClientInfo(string AccountNumber, string PinCode)
{
    if (FindClientByAccountNumberAndPinCode(AccountNumber, PinCode, CurrentClient))
        return (true);
    else
        return (false);
}
