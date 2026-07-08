#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
const std::string ClientsFileName = "Clients.txt";
void ShowMainMenue();

struct sClient 
{
    std::string AccountNumber;
    std::string PinCode;
    std::string Name;
    std::string Phone;
    double  AccountBalance;
};

std::vector<std::string> SplitString(std::string str, std::string delim)
{
    std::vector<std::string> vString;
    size_t pos = 0;
    std::string sWord;
    
    while ((pos = str.find(delim)) != std::string::npos)
    {
        sWord = str.substr(0, pos);
        if (sWord != " ")
        {
            vString.push_back(sWord);
        }
        str.erase(0, pos + delim.length());
    }
    if (str != " ")
    {
        vString.push_back(str);
    }
    return (vString);
}

sClient ConvertLineToRecord(std::string strLine, std::string Separator = "#//#")
{
    sClient Client;
    std::vector<std::string> vClientData;

    vClientData = SplitString(strLine, Separator);

    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]);

   return (Client);
}

std::vector<sClient> LoadClientsDataFromFile(std::string FileName)
{
    std::vector<sClient> vClients;
    std::fstream MyFile;
    
    MyFile.open(FileName, std::ios::in);
    
    if (MyFile.is_open())
    {
        std::string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {
            Client = ConvertLineToRecord(Line); 
            vClients.push_back(Client);
        }
        MyFile.close();
    }
    return (vClients);
}

void PrintClientRecord(sClient Client)
{
    std::cout << "| " << std::setw(15) << std::left << Client.AccountNumber;
    std::cout << "| " << std::setw(10) << std::left << Client.PinCode;
    std::cout << "| " << std::setw(40) << std::left << Client.Name;
    std::cout << "| " << std::setw(12) << std::left << Client.Phone;
    std::cout << "| " << std::setw(12) << std::left << Client.AccountBalance;
}
void ShowAllClientsScreen()
{
    std::vector<sClient> vClients = LoadClientsDataFromFile(ClientsFileName);

    std::cout <<    "\n\t\t\t\t\tClient List (" << vClients.size() << ")Client(s).";
    std::cout <<    "\n_______________________________________________________";
    std::cout <<    "_________________________________________\n" << std::endl;
    std::cout << "| " << std::left << std::setw(15) << "Accout Number";
    std::cout << "| " << std::left << std::setw(10) << "Pin Code";
    std::cout << "| " << std::left << std::setw(40) << "Client Name";
    std::cout << "| " << std::left << std::setw(12) << "Phone";
    std::cout << "| " << std::left << std::setw(12) << "Balance";
    std::cout <<
                    "\n_______________________________________________________";
    std::cout <<    "_________________________________________\n" << std::endl;

    if (vClients.size() == 0)
    {
        std::cout << "\t\t\t\tNo Clients Available In The System!\n";
    }
    else
    {
        for (sClient Client : vClients)
        {
            PrintClientRecord(Client);
            std::cout << std::endl;
        }
    }
    std::cout <<
                "\n_______________________________________________________";
    std::cout << "_________________________________________\n" << std::endl;
}

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
    cout << "Choose what do you want to do? [1 to 6]? ";
    short Choice = 0;
    cin >> Choice;
    return (Choice); 
}
void    GoBackToMainMenue()
{
 std::cout << "\nPress any key to go back to Main Menue..." << std::flush;
    #ifdef _WIN32
        system("pause>nul");
    #else
        system("bash -c 'read -rsn1'");   // -s: silent, -n1: one key, no Enter
    #endif 
    ShowMainMenue();
}

sClient ConvertLinetoRecord(string Line, string Seperator = "#//#")
{
    sClient Client;
    vector<string> vClientData;

    vClientData = SplitString(Line, Seperator);

    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]); //cast string to double

    return Client;
}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{
    string stClientRecord = "";

    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);

    return stClientRecord;
}

bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{
    vector <sClient> vClients;
    fstream MyFile;

    MyFile.open(FileName, ios::in); //read Mode

    if (MyFile.is_open())
    {
        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {
            Client = ConvertLinetoRecord(Line);

            if (Client.AccountNumber == AccountNumber)
            {
                MyFile.close();
                return true;
            }

            vClients.push_back(Client);
        }

        MyFile.close();
    }

    return false;
}

sClient ReadNewClient()
{
    sClient Client;

    cout << "Enter Account Number? ";

    // Usage of std::ws will extract allthe whitespace character
    getline(cin >> ws, Client.AccountNumber);

    while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName))
    {
        cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Account Number? ";
        getline(cin >> ws, Client.AccountNumber);
    }

    cout << "Enter PinCode? ";
    getline(cin, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;
}

void AddDataLineToFile(string FileName, string stDataLine)
{
    fstream MyFile;

    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {
        MyFile << stDataLine << endl;
        MyFile.close();
    }
}

void AddNewClient()
{
    sClient Client;

    Client = ReadNewClient();

    AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));
}

void AddNewClients()
{
    char AddMore = 'Y';

    do
    {
        cout << "Adding New Client:\n\n";

        AddNewClient();

        cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";
        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');
}

void ShowAddNewClientsScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tAdd New Clients Screen";
    cout << "\n-----------------------------------\n";
    AddNewClients();
}

void    PerformMainMenueOption(enMainMenueOptions MainMenueOption)
{
    switch (MainMenueOption)
    {
        case enMainMenueOptions::eListClients:
        ClearScreen();
        ShowAllClientsScreen();
        GoBackToMainMenue();
        break;

        case enMainMenueOptions::eAddClient:
        ClearScreen();
        ShowAddNewClientsScreen();
        GoBackToMainMenue();
        break;

        case enMainMenueOptions::eDeleteClient:
        ClearScreen();
        break;

        case enMainMenueOptions::eUpdateClient:
        ClearScreen();
        break;

        case enMainMenueOptions::eFindClient:
        ClearScreen();
        break;

        case enMainMenueOptions::eExit:
        ClearScreen();
        break;
    }
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
    PerformMainMenueOption((enMainMenueOptions)ReadMainMenueOption());    
}

int main(void)
{
    ShowMainMenue();

    return (0);
}