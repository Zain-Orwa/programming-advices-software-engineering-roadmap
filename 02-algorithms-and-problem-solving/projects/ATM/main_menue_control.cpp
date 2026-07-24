/* atm */
#include "atm.h"

using namespace std;

void    GoBackToMainMenue()
{
    std::cout << "\n\nPress any key to go back to Main Menue..." << std::flush;
    #ifdef _WIN32
        system("pause>nul");
    #else
        system("bash -c 'read -rsn1'");   // -s: silent, -n1: one key, no Enter
    #endif 
    ShowMainMenue();
}

void    PerformMainMenueOption(enMainMenueOptions MainMenueOption)
{
    switch (MainMenueOption)
    {
        case enMainMenueOptions::eQuickWithdraw:
        ClearScreen();
        ShowQuickWithdrawScreen();
        GoBackToMainMenue();
        break;

        case enMainMenueOptions::eNormalWithdraw:
        ClearScreen();
        ShowNormalWithdrawScreen();
        GoBackToMainMenue();
        break;

        case enMainMenueOptions::eDeposit:
        ClearScreen();
        ShowDepositScreen();
        GoBackToMainMenue();
        break;

        case enMainMenueOptions::eCheckBalance:
        ClearScreen();
        ShowCheckBalanceScreen();
        GoBackToMainMenue();
        break;

        case enMainMenueOptions::eExit:
        ClearScreen();
        Login();
        break;
    }
}

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

        cout << "\nEnter Pin Code? ";
        cin >> PinCode;

        LoginFaild = !LoadClientInfo(AccountNumber, PinCode);

    } while (LoginFaild);

        ShowMainMenue();
}
