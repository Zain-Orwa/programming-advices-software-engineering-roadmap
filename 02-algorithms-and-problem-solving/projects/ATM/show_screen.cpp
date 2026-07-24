#include "atm.h"
#include <cstdlib> 

void   ShowNormalWithdrawScreen()
{
    ClearScreen();
    cout << "===========================================\n";
    cout << "\t\tNormal Withdraw Screen\n";
    cout << "===========================================\n";
    PerfromNormalWithdrawOption();
}

void ShowQuickWithdrawScreen()
{
    ClearScreen();
    cout << "===========================================\n";
    cout << "\t\tQucik Withdraw\n";
    cout << "===========================================\n";
    cout << "\t[1] 20\t\t[2] 50\n";
    cout << "\t[3] 100\t\t[4] 200\n";
    cout << "\t[5] 400\t\t[6] 600\n";
    cout << "\t[7] 800\t\t[8] 1000\n";
    cout << "\t[9] Exit\n";
    cout << "===========================================\n";
    cout << "Your Balance is " << CurrentClient.AccountBalance;

    PerfromQuickWithdrawOption(ReadQuickWithdrawOption());
}

void    ShowCheckBalanceScreen()
{
    ClearScreen();
    cout << "===========================================\n";
    cout << "\t\tCheck Balance Screen\n";
    cout << "===========================================\n";    
    cout << "\nYour Balance is " << CurrentClient.AccountBalance << endl;
}

void    ClearScreen()
{
    #ifdef _WIN32
        system("pause>nul");
    #else
        system("clear");   // -s: silent, -n1: one key, no Enter
    #endif 
}

void    LoginScreen()
{
    cout << "===========================================\n";
    cout << "\t\tLogin Screen\n";
    cout << "===========================================\n";
}

void    ShowMainMenue()
{
    ClearScreen();
    cout << "===========================================\n";
    cout << "\t\tATM Main Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Quick Withdraw.\n";
    cout << "\t[2] Normal Withdraw.\n";
    cout << "\t[3] Deposit.\n";
    cout << "\t[4] Check Balance.\n";
    cout << "\t[5] Logout.\n";
    cout << "===========================================\n";
    PerformMainMenueOption((enMainMenueOptions)ReadMainMenueOption());    
}
    
