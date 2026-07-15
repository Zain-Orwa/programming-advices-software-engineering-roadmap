#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
const std::string ClientsFileName = "Clients.txt";
const std::string UsersFileName = "Users.txt";
void Login();
void ShowMainMenue();
void ShowTransactionsMenue();


enum    enTransactionsMenueOptions
{
    eDeposit = 1,
    eWithdraw = 2,
    eShowTotalBalance = 3,
    eShowMainMenue = 4
};

enum    enMainMenueOptions
{
    eListClients  = 1, eAddClient    = 2,
    eDeleteClient = 3, eUpdateClient = 4, 
    eFindClient   = 5, eShowTransactionsMenue = 6,
    eManageUsers  = 7, eExit = 8
};

enum    enManageUsersMenueOptions
{
    eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3,
    eUpdateUser = 4, eFindUser = 5, eMainMenue = 6
};

struct sClient 
{
    std::string AccountNumber;
    std::string PinCode;
    std::string Name;
    std::string Phone;
    double  AccountBalance;
    bool    MarkForDelete = false;
};

struct sUser
{
    string  UserName;
    string  Password;
    int     Permissions;
    bool    MarkForDelete = false;
};

sUser CurrentUser;


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

sUser   ConverUserLineToRecord(std::string Line, std::string Separator = "#//#")
{
    sUser   User;
    vector<string> vUserData;

    vUserData = SplitString(Line, Separator);

    User.UserName = vUserData[0];
    User.Password = vUserData[1];
    User.Permissions = stoi(vUserData[2]);

    return (User);
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

vector<sUser>   LoadUsersDataFromFile(std::string FileName)
{
    fstream MyFile;
    vector<sUser> vUsers;

    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        std::string Line;
        sUser User;

        while (getline(MyFile, Line))
        {
            User = ConverUserLineToRecord(Line);
            vUsers.push_back(User);
        }

        MyFile.close();
    }

    return (vUsers);
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

short   ReadMainMenueOption()
{
    cout << "Choose what do you want to do? [1 to 8]? ";
    short Choice = 0;
    cin >> Choice;
    return (Choice); 
}
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

vector <sClient> LoadCleintsDataFromFile(string FileName)
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
            vClients.push_back(Client);
        }

        MyFile.close();
    }

    return vClients;
}

string ReadClientAccountNumber()
{
    string AccountNumber = "";

    cout << "\nPlease enter AccountNumber? ";
    cin >> AccountNumber;

    return AccountNumber;
}

bool    FindUserByUsernameAndPassword(string Username, string Password, sUser& User)
{
    vector<sUser> vUsers = LoadUsersDataFromFile(UsersFileName);
    
    for (sUser U : vUsers)
    {
        if (U.UserName == Username && U.Password == Password)
        {
            User = U;
            return (true);
        }
    }
    return (false);
}

bool    LoadUserInfo(std::string Username, std::string Password)
{
    if (FindUserByUsernameAndPassword(Username, Password, CurrentUser))
        return (true);
    else
        return (false);
}

bool FindClientByAccountNumber(string AccountNumber, vector <sClient> vClients, sClient& Client)
{
    for (sClient C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }

    return false;
}

void PrintClientCard(sClient Client)
{
    cout << "\nThe following are the client details:\n";
    cout << "-----------------------------------";
    cout << "\nAccout Number: " << Client.AccountNumber;
    cout << "\nPin Code : " << Client.PinCode;
    cout << "\nName : " << Client.Name;
    cout << "\nPhone : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.AccountBalance;
    cout << "\n-----------------------------------\n";
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{
    for (sClient& C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }
    }

    return false;
}

vector <sClient> SaveCleintsDataToFile(string FileName, vector <sClient> vClients)
{
    fstream MyFile;

    MyFile.open(FileName, ios::out); //overwrite

    string DataLine;

    if (MyFile.is_open())
    {
        for (sClient C : vClients)
        {
            if (C.MarkForDelete == false)
            {
                //we only write records that are not marked for delete.
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;
            }
        }

        MyFile.close();
    }

    return vClients;
}

bool DeleteClientByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{
    sClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientCard(Client);

        cout << "\n\nAre you sure you want delete this client? y/n ? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
            SaveCleintsDataToFile(ClientsFileName, vClients);

            //Refresh Clients
            vClients = LoadCleintsDataFromFile(ClientsFileName);

            cout << "\n\nClient Deleted Successfully.";
            return true;
        }
    }
    else
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
    return false;
}

void ShowDeleteClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDelete Client Screen";
    cout << "\n-----------------------------------\n";

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();

    DeleteClientByAccountNumber(AccountNumber, vClients);
}

sClient ChangeClientRecord(string AccountNumber)
{
    sClient Client;

    Client.AccountNumber = AccountNumber;

    cout << "\n\nEnter PinCode? ";
    getline(cin >> ws, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;
}

bool UpdateClientByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{
    sClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientCard(Client);

        cout << "\n\nAre you sure you want update this client? y/n ? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            for (sClient& C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }
            }

            SaveCleintsDataToFile(ClientsFileName, vClients);

            cout << "\n\nClient Updated Successfully.";
            return true;
        }
    }
    else
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
    return false;
}

void ShowUpdateClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate Client Info Screen";
    cout << "\n-----------------------------------\n";

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();

    UpdateClientByAccountNumber(AccountNumber, vClients);
}

void ShowFindClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tFind Client Screen";
    cout << "\n-----------------------------------\n";

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    sClient Client;
    string AccountNumber = ReadClientAccountNumber();

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
        PrintClientCard(Client);
    else
        cout << "\nClient with Account Number[" << AccountNumber << "] is not found!";
}

void ShowEndScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tProgram Ends :-)";
    cout << "\n-----------------------------------\n";
}

void GoBackToTransactionsMenue()
{
    cout << "\n\nPress any key to go back to Transactions Menue..." << flush;

    #ifdef _WIN32
        system("pause>nul");
    #else
        system("bash -c 'read -rsn1'");
    #endif

    ShowTransactionsMenue();
}

short ReadTransactionsMenueOption()
{
    cout << "Choose what do you want to do? [1 to 4]? ";

    short Choice = 0;
    cin >> Choice;

    return Choice;
}

bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector <sClient>& vClients)
{
    char Answer = 'n';

    cout << "\n\nAre you sure you want perfrom this transaction? y/n ? ";
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {
        for (sClient& C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance += Amount;
                SaveCleintsDataToFile(ClientsFileName, vClients);

                cout << "\n\nDone Successfully. New balance is: " << C.AccountBalance;

                return true;
            }
        }
    }
    return false;
}

void ShowDepositScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDeposit Screen";
    cout << "\n-----------------------------------\n";

    sClient Client;
    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();

    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
        AccountNumber = ReadClientAccountNumber();
    }

    PrintClientCard(Client);

    double Amount = 0;

    cout << "\nPlease enter deposit amount? ";
    cin >> Amount;

    DepositBalanceToClientByAccountNumber(AccountNumber, Amount, vClients);
}

void ShowWithDrawScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tWithdraw Screen";
    cout << "\n-----------------------------------\n";

    sClient Client;
    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();

    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
        AccountNumber = ReadClientAccountNumber();
    }

    PrintClientCard(Client);

    double Amount = 0;

    cout << "\nPlease enter withdraw amount? ";
    cin >> Amount;

    //Validate that the amount does not exceeds the balance
    while (Amount > Client.AccountBalance)
    {
        cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance << endl;
        cout << "Please enter another amount? ";
        cin >> Amount;
    }

    DepositBalanceToClientByAccountNumber(AccountNumber, Amount * -1, vClients);
}

void PrintClientRecordBalanceLine(sClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}

void ShowTotalBalances()
{
    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    double TotalBalances = 0;

    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else
    {
        for (sClient Client : vClients)
        {
            PrintClientRecordBalanceLine(Client);
            TotalBalances += Client.AccountBalance;
            cout << endl;
        }
    }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "\t\t\t\t Total Balances = " << TotalBalances;

        cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}


void ShowTotalBalancesScreen()
{
    ShowTotalBalances();
}

void PerfromTranactionsMenueOption(enTransactionsMenueOptions TransactionMenueOption)
{
    switch (TransactionMenueOption)
    {
        case enTransactionsMenueOptions::eDeposit:
        {
            ClearScreen();
            ShowDepositScreen();
            GoBackToTransactionsMenue();
            break;
        }

        case enTransactionsMenueOptions::eWithdraw:
        {
            ClearScreen();
            ShowWithDrawScreen();
            GoBackToTransactionsMenue();
            break;
        }

        case enTransactionsMenueOptions::eShowTotalBalance:
        {
            ClearScreen();
            ShowTotalBalancesScreen();
            GoBackToTransactionsMenue();
            break;
        }

        case enTransactionsMenueOptions::eShowMainMenue:
        {
            ShowMainMenue();
        }
    }
}

void ShowTransactionsMenue()
{
    ClearScreen();
    cout << "===========================================\n";
    cout << "\tTransactions Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Deposit.\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] Total Balances.\n";
    cout << "\t[4] Main Menue.\n";
    cout << "===========================================\n";

    PerfromTranactionsMenueOption((enTransactionsMenueOptions)ReadTransactionsMenueOption());
}

short   ReadManageUsersMenue()
{
    short   Choice = 0;
    cout << "\nChoose what do you want to do? [1 to 6]? ";
    cin >> Choice;
    return (Choice);
}



void ShowAllUsersScreen()
{
    vector<stUser> vUsers = LoadUsersDataFromFile(UsersFileName);

    cout << "\n\t\t\t\t\tUsers List (" << vUsers.size() << ") User(s).";

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "User Name";
    cout << "| " << left << setw(10) << "Password";
    cout << "| " << left << setw(40) << "Permissions";

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    if (vUsers.size() == 0)
        cout << "\t\t\t\tNo Users Available In the System!";
    else
        for (stUser User : vUsers)
        {
            PrintUserRecordLine(User);
            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}



void    ShowListUsersScreen()
{
    ShowAllClientsScreen();
}

void    PerformManageUsersMenue(enManageUsersMenueOptions ManageUsersMenueOptions)
{
    switch (ManageUsersMenueOptions)
    {
        case enManageUsersMenueOptions::eListUsers:
        break;

        case enManageUsersMenueOptions::eAddNewUser:
        break;

        case enManageUsersMenueOptions::eDeleteUser:
        break;

        case enManageUsersMenueOptions::eUpdateUser:
        break;


        case enManageUsersMenueOptions::eFindUser:
        break;


        case enManageUsersMenueOptions::eMainMenue:
        break;
    }
}

void    ShowManageUsersMenue()
{
    

    ClearScreen();
    cout << "===========================================\n";
    cout << "\tManage Users Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] List Users.\n";
    cout << "\t[2] Add New User.\n";
    cout << "\t[3] Delete User.\n";
    cout << "\t[4] Update User.\n";
    cout << "\t[4] Find User.\n";
    cout << "\t[4] Main Menue.\n";
    cout << "===========================================\n";
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
        ShowDeleteClientScreen();
        GoBackToMainMenue();
        break;

        case enMainMenueOptions::eUpdateClient:
        ClearScreen();
        ShowUpdateClientScreen();
        GoBackToMainMenue();
        break;

        case enMainMenueOptions::eFindClient:
        ClearScreen();
        ShowFindClientScreen();
        GoBackToMainMenue();
        break;

        case enMainMenueOptions::eShowTransactionsMenue:
        ClearScreen();
        ShowTransactionsMenue();
        break;

        case enMainMenueOptions::eManageUsers:
        ClearScreen();
        ShowManageUsersMenue();
        break;

        case enMainMenueOptions::eExit:
        ClearScreen();
        //ShowEndScreen();
        Login();
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
    cout << "\t[6] Transactions.\n";
    cout << "\t[7] Manage Users.\n";
    cout << "\t[8] Logout.\n";
    cout << "===========================================\n";
    PerformMainMenueOption((enMainMenueOptions)ReadMainMenueOption());    
}


bool    FindUserByUsernameAndPassword(string Username, string Password, sUser& User)
{
    vector<sUser> vUsers = LoadUsersDataFromFile(UsersFileName);
    
    for (sUser U : vUsers)
    {
        if (U.UserName == Username && U.Password == Password)
        {
            User = U;
            return (true);
        }
    }
    return (false);
}

bool    LoadUserInfo(std::string Username, std::string Password)
{
    if (FindUserByUsernameAndPassword(Username, Password, CurrentUser))
        return (true);
    else
        return (false);
}

void    Login()
{
    bool    LoginFaild = false;
    string  Username, Password;

    do 
    {
        ClearScreen();
        cout << "===========================================\n";
        cout << "\t\tLogin Screen\n";
        cout << "===========================================\n";

        if (LoginFaild)
        {
            cout << "\nInvalid Username/Password!\n";
        }

        std::cout << "\nEnter Username? ";
        std::cin >> Username;

        std::cout << "\nEnter Password? ";
        std::cin >> Password;

        LoginFaild = !LoadUserInfo(Username, Password);

    } while (LoginFaild);

    ShowMainMenue();
}

int main(void)
{
    Login();

    return (0);
}