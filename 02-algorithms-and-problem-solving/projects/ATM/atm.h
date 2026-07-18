#ifndef ATM_H
#define ATM_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>

using   namespace std;
const   string ClientsFileName = "Clients.txt";

struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
};

sClient CurrentClient; 

//===================== Login =====================//
int             main();
void            Login();

//==================== User Inputs ================//
string          ReadAccountNumber();
string          ReadPinCode();
bool            LoadClientInfo(string AccountNumber, string PinCode);

//=================== Find / Lookup ==============//
bool            FindClientByAccountNumberAndPinCode(string AccountNumber, string PinCode);

//=================== utils =======================//
vector<string>  SplitString(string str, string Delim);

//================== File I/O ====================//
string          ConvertRecordToLine(sClient Client, string Seperator = "#//#");
sClient         ConvertLineToRecord(std::string strLine, std::string Separator = "#//#");
vector<sClient> LoadClientsDataFromFile(string FileName);

//================= Show On Scree (print) ========//
void            ClearScreen();
void            LoginScreen();






#endif