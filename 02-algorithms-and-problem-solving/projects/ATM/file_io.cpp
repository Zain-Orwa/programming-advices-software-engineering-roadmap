#include "atm.h"

string ConvertRecordToLine(sClient Client, string Seperator)
{

    string stClientRecord = "";

    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);

    return stClientRecord;

}

sClient ConvertLineToRecord(std::string strLine, std::string Separator)
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


vector<sClient> LoadClientsDataFromFile(std::string FileName)
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

vector <sClient> SaveClientsDataToFile(string FileName, vector <sClient> vClients)
{

    fstream MyFile;
    MyFile.open(FileName, ios::out);//overwrite

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
