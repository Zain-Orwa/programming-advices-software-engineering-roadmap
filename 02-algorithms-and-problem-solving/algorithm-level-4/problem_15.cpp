/*
 Problem 15
 ==========
 Create a program that reads a date (day, month, year) and prints whether
 it is the last day of its month and whether its month is the last month of the year.

 Notes
 =====
 - Leap years follow the Gregorian rule when determining February's length.
 - `NumberOfDaysInMonth(m, y)` returns month length; used by `isLastDayInMonth`.
 - `isLastMonthInYear` checks if the month equals 12 (December).
 - Minimal input validation; intended for learning purposes.
*/





#include <iostream>
using namespace std;

struct sDate {
    short Day;
    short Month;
    short Year;
};

short ReadDay(){
    short Day;
    cout << "Please enter a day: ";
    cin >> Day;
    return (Day);
}


short ReadMonth(){
    short Month;
    cout << "Please enter a month: ";
    cin >> Month;
    return (Month);
}

short ReadYear(){
    short Year = 1900;
    cout << "Please enter a year: ";
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

bool isLeapYear(short Year){
    return ((Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0));
}

short NumberOfDaysInMonth(short Month, short Year){
    if (Month < 1 || Month > 12)
        return (0);

    short arrMonthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return ((Month == 2) ?(isLeapYear(Year) ? 29 : 28) : arrMonthDays[Month - 1]);
}

bool isLastDayInMonth(sDate Date){
   return (Date.Day == NumberOfDaysInMonth(Date.Month, Date.Year));
}

bool isLastMonthInYear(sDate Date){
    return (Date.Month == 12);
}

int main(){
    sDate Date = ReadFullDate();

    if (isLastDayInMonth(Date))
        cout << "\nYes, It's the last day in Month!" << endl;
    else
        cout << "\nNo, It's NOT last day in Month!" << endl;

    if (isLastMonthInYear(Date))
        cout << "\nYes, It's the last month in the year!" << endl;
    else
        cout << "\nNo, It's NOT last month in the year!" << endl;

    return (0);
}
