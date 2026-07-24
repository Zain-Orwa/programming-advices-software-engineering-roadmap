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

short   ReadMainMenueOption()
{
    short   Choice;

    Choice = 0;
    cout << "\nChoose what do you want to do? [1 to 5]? ";
    cin >> Choice;
    return (Choice);
}

