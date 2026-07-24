#ifndef ATM_H
#define ATM_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>

using   namespace std;
const   string ClientsFileName = "Clients.txt";

enum    enQuickWithdrawOptions
{

};

enum    enMainMenueOptions
{
    eQuickWithdraw = 1,
    eNormalWithdraw = 2,
    eDeposit = 3,
    eCheckBalance = 4,
    eExit = 5
};

struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
};

extern sClient CurrentClient; 

//==================== User Inputs ================//
short           ReadQuickWithdrawOption();
string          ReadAccountNumber();
string          ReadPinCode();
short           ReadMainMenueOption();

//=================== Find / Lookup ==============//
bool            FindClientByAccountNumberAndPinCode(string AccountNumber, string PinCode, sClient& Client);

//=================== utils =======================//
vector<string>  SplitString(string str, string Delim);

//================== File I/O ====================//
string          ConvertRecordToLine(sClient Client, string Seperator = "#//#");
sClient         ConvertLineToRecord(std::string strLine, std::string Separator = "#//#");
vector<sClient> LoadClientsDataFromFile(string FileName);
bool            LoadClientInfo(string AccountNumber, string PinCode);

//================ Withdraw  ================//
void            GoBackToQuickWithdrawMenue();
short           GetQuickWithdrawAmount(short QuickWithdrawOption);
void            PerfromQuickWithdrawOption(short QuickWithdrawOption);

//================ Deposit  ================//


//================= Show Screen (print) ========//
void            ShowQuickWithdrawScreen();
void            ShowCheckBalanceScreen();
void            ClearScreen();
void            ShowMainMenue();
void            LoginScreen();

//================ Main Menu Control ================//
void            Login();
void            GoBackToMainMenue();
void            PerformMainMenueOption(enMainMenueOptions option);


#endif