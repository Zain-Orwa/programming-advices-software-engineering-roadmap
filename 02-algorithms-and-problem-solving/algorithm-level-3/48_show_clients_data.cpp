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
void PrintAllClientsData(std::vector<sClient> vClients)
{
    std::cout <<    "\n\t\t\t\t\tClient List (" << vClients.size() << ")Client(s).";
    std::cout <<
                    "\n_______________________________________________________";
    std::cout <<    "_________________________________________\n" << std::endl;
    std::cout << "| " << std::left << std::setw(15) << "Accout Number";
    std::cout << "| " << std::left << std::setw(10) << "Pin Code";
    std::cout << "| " << std::left << std::setw(40) << "Client Name";
    std::cout << "| " << std::left << std::setw(12) << "Phone";
    std::cout << "| " << std::left << std::setw(12) << "Balance";
    std::cout <<
                    "\n_______________________________________________________";
    std::cout <<    "_________________________________________\n" << std::endl;
    for (sClient Client : vClients)
    {
        PrintClientRecord(Client);
        std::cout << std::endl;
    }
    std::cout <<
                "\n_______________________________________________________";
    std::cout << "_________________________________________\n" << std::endl;
}


int main(void)
{
    std::vector<sClient> vClients = LoadClientsDataFromFile(ClientsFileName);

    PrintAllClientsData(vClients);

    return (0);
}