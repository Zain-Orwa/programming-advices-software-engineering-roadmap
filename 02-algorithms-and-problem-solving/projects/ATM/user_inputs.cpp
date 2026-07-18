#include "atm.h"

using namespace std;

string    ReadAccountNumber()
{
    string  AccountNumber = "";
    cout << "\nEnter Your Account Number: ";
    getline(cin, AccountNumber);
    return (AccountNumber);
}

string   ReadPinCode()
{
    string   PinCode = "";
    cout << "\nEnter Your PIN Code: ";
    cin >> PinCode;
    return (PinCode);
}

