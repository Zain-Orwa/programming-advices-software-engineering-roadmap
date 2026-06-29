#include <iostream>
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
    double AccountBalance;
};

sClient ReadNewClient()
{
    sClient Client;

    std::cout << "Enter Account Number? ";
    std::getline(std::cin >> std::ws, Client.AccountNumber);

    std::cout << "Enter PinCode? ";
    std::getline(std::cin, Client.PinCode);

    std::cout << "Enter Name? ";
    std::getline(std::cin, Client.Name);

    std::cout << "Enter Phone? ";
    std::getline(std::cin, Client.Phone);

    std::cout << "Enter AccountBalance? ";
    std::cin >> Client.AccountBalance;

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

void    ClearScreen()
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void    AddDataLineToFile(std::string FileName, std::string strDataLine)
{
    std::fstream MyFile;

    MyFile.open(FileName, std::ios::out | std::ios::app);

    if (MyFile.is_open())
    {
        MyFile << strDataLine << std::endl;
        MyFile.close();
    }
}

void    AddNewClient()
{
    sClient Client;

    Client = ReadNewClient();
    AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));
}

void    AddClients()
{
    char    AddMore = 'Y';
    do
    {
        ClearScreen();
        std::cout << "Adding New Client:\n\n";
        AddNewClient();
        std::cout << "\nClient Added Successfully, do you want to add more client? Y/N? ";
        std::cin >> AddMore;

    } while (toupper(AddMore) == 'Y');
}

int main(void)
{
    AddClients();

    return (0);
}