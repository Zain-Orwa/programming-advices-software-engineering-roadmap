#include "atm.h"

using namespace std;

int     ReadNormalWithdrawAmount()
{
    int Amount;

    Amount = 0;
    cout << "\n\nEnter Amount Multiple Of 5's? ";
    cin >> Amount;
    while (Amount % 5 != 0)
    {
        cout << "\n\nEnter Amount Multiple Of 5's? ";
        cin >> Amount;
    }
    return (Amount);
}

short   ReadQuickWithdrawOption()
{
    short   Choice;

    Choice = 0;
    while (Choice < 1 || Choice > 9)
    {
        cout << "\n\nChoose The Amount To Withdraw From [1] to [8] Or [9] for Exit? ";
        cin >> Choice;
    }
    return (Choice);
}

short   ReadMainMenueOption()
{
    short   Choice;

    Choice = 0;
    cout << "\nChoose what do you want to do? [1 to 5]? ";
    cin >> Choice;
    return (Choice);
}

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


