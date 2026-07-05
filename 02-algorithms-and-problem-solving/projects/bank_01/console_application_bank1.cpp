#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void    ClearScreen()
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

enum enMainMenueOptions
{
    eListClients  = 1, eAddClient    = 2,
    eDeleteClient = 3, eUpdateClient = 4, 
    eFindClient   = 5, eExit = 6
};

short   ReadMainMenueOption()
{
    cout << "Choose what do you want to do? [1 to 5]? ";
    short Choice = 0;
    cin >> Choice;
    return (Choice); 
}
void    PerformMainMenueOption(enMainMenueOptions MainMenueOption)
{

}

void    ShowMainMenue()
{
    ClearScreen();
    cout << "===========================================\n";
    cout << "\t\tMain Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Exit.\n";
    cout << "===========================================\n";

}

int main(void)
{
    ShowMainMenue();

    return (0);
}