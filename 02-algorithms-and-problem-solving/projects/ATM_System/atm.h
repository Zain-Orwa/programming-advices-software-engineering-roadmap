#ifndef ATM_H
# define ATM_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
const string    ClientsFileName = "Clients.txt";

struct stClient 
{
    string  AccountNumber;
    string  PinCode;
    string  Name;
    string  Phone;
    double  AccountBalance;
};


#endif