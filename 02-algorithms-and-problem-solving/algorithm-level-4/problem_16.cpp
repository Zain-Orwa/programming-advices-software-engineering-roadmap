/*
 Problem 16
 ==========
 Create a program that reads a date (day, month, year) and prints the date
 after adding exactly one day.

 Notes
 =====
 - Leap years follow the Gregorian rule (February has 29 days in leap years).
 - `NumberOfDaysInMonth(m, y)` provides month length for boundary checks.
 - If it's the last day of a month (but not December), roll to day=1 of next month.
 - If it's December 31, roll to January 1 of the next year.
 - Otherwise, simply increment the day by 1.
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
    short Day = 0;
    cout << "Please enter a day: ";
    cin >> Day;
    return (Day);
}


short ReadMonth(){
    short Month = 1;
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
    return ((Month == 2) ? (isLeapYear(Year) ? 29 : 28) : arrMonthDays[Month - 1]);
}

bool isLastDayInMonth(sDate Date){
   return (Date.Day == NumberOfDaysInMonth(Date.Month, Date.Year));
}

bool isLastMonthInYear(sDate Date){
    return (Date.Month == 12);
}

sDate IncreaseDateByOneDay(sDate Date){
    if (isLastDayInMonth(Date)){
        if (isLastMonthInYear(Date)){
            Date.Year++;
            Date.Month = 1;
            Date.Day   = 1;
        } else {
            Date.Month++;
            Date.Day = 1;
        }
    } else {
        Date.Day++;
    }
    return (Date);
}

int main(){
    sDate Date = ReadFullDate();    

    Date = IncreaseDateByOneDay(Date);

    cout << "\n\nDate after adding one day: ";
    cout << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;

    return (0);
}


