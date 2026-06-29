#include <iostream>
#include <string>
#include <fstream>
#include <vector>

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
    std::getline(std::cin, Client.AccountNumber);

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

int main(void)
{
    sClient Client = ReadNewClient();

    std::cout << "\n\nClient Record For Saving Is:\n";
    std::cout << ConvertRecordToLine(Client) << std::endl;

    return (0);
}