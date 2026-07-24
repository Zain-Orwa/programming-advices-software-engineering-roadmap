#include "atm.h"

bool    DepositBalanceToClientByAccountNumber(string AccountNumber, double Ammount, vector<sClient>& vClients)
{
    char    Answer = 'n';

    cout << "Are You Sure You Want To Perform This Transaction? Y/N? ";
    cin >> Answer;
    if (Answer == 'Y' || Answer == 'y')
    {
        for (sClient C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance += Ammount;
                SaveClientsDataToFile(ClientsFileName, vClients);
                cout << "\n\nDone Successfully New Balance is " << C.AccountBalance << endl;
                return (true);
            }
        }
    }
    return (false);
}