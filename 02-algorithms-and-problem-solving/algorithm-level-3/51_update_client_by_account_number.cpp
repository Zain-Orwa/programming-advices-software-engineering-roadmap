#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>

const std::string ClientsFileName = "Clients.txt";

struct sClient 
{
    std::string AccountNumber;
    std::string PinCode;
    std::string Name;
    std::string Phone;
    double  AccountBalance;
    bool    MarkForDelete = false;
};

std::string ReadAccountNumber()
{
    std::string AccountNumber;

    std::cout << "\nPlease enter Account Number: ";
    std::cin >> AccountNumber;
    return (AccountNumber);
}

bool    FindClientByAccountNumber(std::string AccountNumber, std::vector<sClient> vClients, sClient& Client)
{
    for (sClient C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return (true);
        }
    }
    return (false);
}

void PrintClientCard(sClient Client)
{
    std::cout << "\nThe following are the client details:\n";
    std::cout << "\nAccount Number: " << Client.AccountNumber;
    std::cout << "\nPin Code : " << Client.PinCode;
    std::cout << "\nName : " << Client.Name;
    std::cout << "\nPhone : " << Client.Phone;
    std::cout << "\nAccount Balance: " << Client.AccountBalance << std::endl;
}

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

std::string ConvertRecordToLine(sClient Client, std::string Separator = "#//#")
{
    std::string strClientRecord = "";

    strClientRecord += Client.AccountNumber + Separator;
    strClientRecord += Client.PinCode + Separator;
    strClientRecord += Client.Name + Separator;
    strClientRecord += Client.Phone + Separator;
    strClientRecord += std::to_string(Client.AccountBalance);

    return (strClientRecord);
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

std::vector<sClient>    SaveClientDataToFile(std::string FileName, std::vector<sClient> vClients)
{
    std::fstream MyFile;
    std::string  DataLine;

    MyFile.open(FileName, std::ios::out);
    
    if (MyFile.is_open())
    {
       for (sClient C : vClients)  
       {
           if (C.MarkForDelete == false)
           {
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << std::endl;
           }
       }
       MyFile.close();
    }
    return (vClients);
}

sClient ChangeClientRecord(std::string AccountNumber)
{
    sClient Client;

    Client.AccountNumber = AccountNumber;

    std::cout << "\n\nEnter PinCode? ";
    std::getline(std::cin >> std::ws, Client.PinCode);

    std::cout << "Enter Name? ";
    std::getline(std::cin, Client.Name);    

    std::cout << "Enter Phone? ";
    std::getline(std::cin, Client.Phone);

    std::cout << "Enter AccountBalance? ";
    std::cin >> Client.AccountBalance;

    return (Client);
}

bool    UpdateClientByAccountNumber(std::string AccountNumber, std::vector<sClient>& vClients)
{
    sClient Client;
    char    Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientCard(Client);

        std::cout << "\n\nAre You Sure You Want To Update This Client? Y/N? ";
        std::cin >> Answer;
        if (Answer == 'Y' || Answer == 'y')
        {
            for (sClient& C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }
            }

            SaveClientDataToFile(ClientsFileName, vClients);
            std::cout << "\n\nClient Updated Successfully!\n";
            return (true);
        }
    }
    else
    {
        std::cout << "\nClient With Account Number [" << AccountNumber << "] Is Not Found\n";
    }
    return (false);
}

int main(void)
{
    std::string AccountNumber = ReadAccountNumber();
    std::vector<sClient> vClients = LoadClientsDataFromFile(ClientsFileName);

    UpdateClientByAccountNumber(AccountNumber, vClients);

    return (0);
}
