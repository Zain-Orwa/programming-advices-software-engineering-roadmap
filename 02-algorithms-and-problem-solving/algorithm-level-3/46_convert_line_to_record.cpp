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

void    PrintClientRecord(sClient Client)
{
    std::cout << "\nThe following is extracted client record:";
    std::cout << "\n----------------------------------------";
    std::cout << "\nAccount Number : " << Client.AccountNumber;
    std::cout << "\nPin Code       : " << Client.PinCode;
    std::cout << "\nName           : " << Client.Name;
    std::cout << "\nPhone          : " << Client.Phone;
    std::cout << "\nAccount Balance: " << Client.AccountBalance << std::endl;
}

int main(void)
{
    std::string strLine = "A150#//#1234#//#Mohammed Abu-Hadoud#//#079999#//#5270.000000";
    std::cout << "\nLine Record is:\n";
    std::cout << strLine << std::endl;

    sClient Client = ConvertLineToRecord(strLine);
    PrintClientRecord(Client);

    return (0);
}