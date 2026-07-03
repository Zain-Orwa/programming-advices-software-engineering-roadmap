/*
 Problem 12
 ==========
 Create a program that reads a date (day, month, year) and a number of days to add,
 then prints the resulting calendar date.

 Notes
 =====
 - Leap years follow the Gregorian rule (February has 29 days in leap years).
 - `NumberOfDaysInMonth(m, y)` returns month length; February adjusts for leap years.
 - `NumberOfDaysFromBeginningOfTheYear(d, m, y)` converts a date to its day-order.
 - `DateAddDays(n, date)` adds n days by advancing through months/years as needed.
 - Minimal input validation; intended for learning and function composition.
*/


#include <iostream>
using namespace std;

struct sDate {
    short Day;
    short Month;
    short Year;
};


short ReadDay(){
    short Day = 0;
    cout << "Please enter a day: ";
    cin >> Day;
    return (Day);
}

short ReadMonth(){
    short Month = 0;
    cout << "\nPlease enter a month: ";
    cin >> Month;
    return (Month);
}

short ReadYear(){
    short Year = 1900;
    cout << "\nPlease enter a year: ";
    cin >> Year;
    return (Year);
}

sDate ReadFullDate(){
    sDate Date;
    Date.Day   = ReadDay();
    Date.Month = ReadMonth();
    Date.Year  = ReadYear();
    return (Date);
}

short ReadDaysToAdd(){
    short Days = 0;
    cout << "\nPlease enter days to add: ";
    cin >> Days;
    return (Days);
}

bool    isLeapYear(short Year){
    return ((Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0));
}

short NumberOfDaysInMonth(short Month, short Year){
    if (Month < 1 || Month > 12)
        return (0);
    
    short arrMonthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return (Month == 2) ? (isLeapYear(Year)? 29 : 28) : arrMonthDays[Month - 1];
}

short   NumberOfDaysFromBeginningOfTheYear(short Day, short Month, short Year){
    short TotalDays = 0;
    
    for (int i = 1; i <= Month - 1; i++){
        TotalDays += NumberOfDaysInMonth(i, Year);
    }
    TotalDays += Day;
    return (TotalDays);
}

sDate DateAddDays(short Days, sDate Date){
    short RemainingDays = Days + NumberOfDaysFromBeginningOfTheYear(Date.Day, Date.Month, Date.Year); 
    short MonthDays = 0;

    Date.Month = 1;

    while (true){
        MonthDays = NumberOfDaysInMonth(Date.Month, Date.Year);
        if (RemainingDays > MonthDays){
            RemainingDays -= MonthDays;
            Date.Month++;
            if (Date.Month > 12){
                Date.Month = 1;
                Date.Year++;
            }
        } else {
            Date.Day = RemainingDays;
            break;
        }
    }
    return (Date);
}

int main(){
    sDate Date = ReadFullDate();
    short Days = ReadDaysToAdd();

    Date = DateAddDays(Days, Date);

    cout << "\n\nDate after adding [" << Days << "] is: ";
    cout << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;

    return (0);
}

