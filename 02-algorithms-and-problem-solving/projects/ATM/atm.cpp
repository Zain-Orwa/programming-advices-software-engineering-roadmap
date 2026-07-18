#include "atm.h"

using namespace std;

void Login()
{
    bool    LoginFaild;
    string  AccountNumber;
    string  PinCode;

 
    LoginFaild = false;
    AccountNumber = "";
    PinCode = "";
    do
    {
        ClearScreen();
        LoginScreen();

         if (LoginFaild)
        {
            cout << "\nInvalid Username/Password!\n";
        }

        cout << "\nEnter Account Number? ";
        cin >> AccountNumber;

        cout << "\nEnter Your Pin Code? ";
        cin >> PinCode;

        LoginFaild = !LoadClientInfo(AccountNumber, PinCode);

    } while (LoginFaild);
}