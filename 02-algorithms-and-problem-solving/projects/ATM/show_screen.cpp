#include "atm.h"
#include <cstdlib> 


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
    

