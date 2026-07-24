#include "atm.h"

bool    WithdrawBalanceToClientByAccountNumber(string AccountNumber, double Ammount, vector<sClient>& vClients)
{
    char    Answer = 'n';

    cout << "\nAre You Sure You Want To Perform This Transaction? Y/N? ";
    cin >> Answer;
    if (Answer == 'Y' || Answer == 'y')
    {
        for (sClient& C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance -= Ammount;
                SaveClientsDataToFile(ClientsFileName, vClients);
                cout << "\n\nDone Successfully New Balance is " << C.AccountBalance << endl;
                return (true);
            }
        }
    }
    return (false);
}

void    GoBackToQuickWithdrawMenue()
{
    std::cout << "\n\nPress any key to go back to Quick Withdraw Screen..." << std::flush;
    #ifdef _WIN32
        system("pause>nul");
    #else
        system("bash -c 'read -rsn1'");   // -s: silent, -n1: one key, no Enter
    #endif 
    ShowQuickWithdrawScreen();
}

short   GetQuickWithdrawAmount(short QuickWithdrawOption)
{
    switch (QuickWithdrawOption)
    {
        case 1:
            return (20);
        case 2:
            return (50);
        case 3:
            return (100);
        case 4:
            return (200);
        case 5:
            return (400);
        case 6:
            return (600);
        case 7:
            return (800);
        case 8:
            return (1000);
        default:
            return (0);
    }
}

void    PerfromQuickWithdrawOption(short QuickWithdrawOption)
{
    if (QuickWithdrawOption == 9) //exit
        return;
    
    short   WithdrawAmount = GetQuickWithdrawAmount(QuickWithdrawOption);
    if (WithdrawAmount > CurrentClient.AccountBalance)
    {
        cout << "\nThe Amount Exceed Your Balance, Make Another Choice.\n";
        GoBackToQuickWithdrawMenue();
    }

    vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
    WithdrawBalanceToClientByAccountNumber(CurrentClient.AccountNumber, WithdrawAmount, vClients);
    CurrentClient.AccountBalance -= WithdrawAmount;
}
