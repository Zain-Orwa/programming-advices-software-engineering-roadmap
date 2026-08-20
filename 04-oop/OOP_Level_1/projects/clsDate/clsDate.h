#pragma once

#include <iostream>
#include <string>
#include "clsString.h"

using namespace std;
class clsDate
{
private:
    short   _Day = 1;
    short   _Month = 1;
    short   _Year = 1900;

public:
    clsDate()
    {
        time_t  t = time(0);
        tm* now = localtime(&t);
        _Day = now->tm_mday;
        _Month = now->tm_mon + 1;
        _Year = now->tm_year + 1900;
    }

    clsDate(string sDate)
    {
        vector<string> vDate = clsString::Split(sDate, "/");
        _Day = stoi(vDate[0]);
        _Month = stoi(vDate[1]);
        _Year = stoi(vDate[2]);
    }

    clsDate (short Day, short Month, short Year)
    {
        _Day = Day;
        _Month = Month;
        _Year = Year;
    }


    void    Print()
    {
        cout << to_string(_Day) + "/" + to_string(_Month) + "/" + to_string(_Year) << endl;
    }





};
