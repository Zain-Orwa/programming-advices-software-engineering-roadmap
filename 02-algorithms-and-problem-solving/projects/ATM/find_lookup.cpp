#include "atm.h"

using namespace std;

bool    FindClientByAccountNumberAndPinCode(string AccountNumber, string PinCode)
{

}


bool    LoadClientInfo(string AccountNumber, string PinCode)
{
    if (FindClientByAccountNumberAndPinCode(AccountNumber, PinCode))
        return (true);
    else
        return (false);
}