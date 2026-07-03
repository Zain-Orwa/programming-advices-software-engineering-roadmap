/*
 Problem 60
 ==========
 Create a program that reads a date period (start and end) and a single date,
 then prints whether the date falls within the period (inclusive).

 Notes
 =====
 - Bounds are inclusive: StartDate ≤ Date ≤ EndDate.
 - Uses comparison helpers with an enum (Before, Equal, After) to test ordering.
 - Alternate implementation provided using direct comparisons (<= and >=) via helpers.
 - Minimal input validation; intended for learning purposes.
*/



#include <iostream>
using namespace std;

enum enDateCompare {Before = -1, Equal = 0, After = 1};

struct sDate{
    short Day;
    short Month;
    short Year;
};

struct stPeriod {
    sDate StartDate;
    sDate EndDate;
};

short ReadDay(){
    short Day = 1;
    cout << "\nPlease enter a day: ";
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
    cout << "\n";
    return (Year);
}

sDate ReadFullDate(){
    sDate Date;
    Date.Day   = ReadDay();
    Date.Month = ReadMonth();
    Date.Year  = ReadYear();

    return (Date);
}

stPeriod ReadPeriod(){
    stPeriod Period;
    cout << "\nEnter Start Date: ";
    Period.StartDate = ReadFullDate();
    cout << "\nEnter End Date  : ";
    Period.EndDate = ReadFullDate();

    return (Period);
}

bool isDate1BeforeDate2(sDate Date1, sDate Date2){
    return (Date1.Year < Date2.Year) || (Date1.Year == Date2.Year && Date1.Month < Date2.Month) ||
           (Date1.Year == Date2.Year && Date1.Month == Date2.Month && Date1.Day < Date2.Day);
}

bool isDate1EqualDate2(sDate Date1, sDate Date2){
    return (Date1.Year == Date2.Year) ? ((Date1.Month == Date2.Month) ? ((Date1.Day == Date2.Day) ? true : false) : false) : false;
}

enDateCompare CompareDate (sDate Date1, sDate Date2){
    if (isDate1BeforeDate2(Date1, Date2)) return enDateCompare::Before;
    if (isDate1EqualDate2(Date1, Date2))  return enDateCompare::Equal;

    return enDateCompare::After;
}

bool isDateInPeriod(sDate Date, stPeriod Period){
    return !(CompareDate(Date, Period.StartDate) == enDateCompare::Before ||
             CompareDate(Date, Period.EndDate)   == enDateCompare::After);
           
}

/***Another Way***
bool isDateWithinPeriod(stPeriod Period, sDate Date){
    return ((isDate1BeforeDate2(Period.StartDate, Date) || (isDate1EqualDate2(Period.StartDate, Date)))
            && (isDate1BeforeDate2(Date, Period.EndDate) || (isDate1EqualDate2(Date, Period.EndDate))));
}
*/

int main(){
    stPeriod Period;
    cout << "Enter Period: ";
    Period = ReadPeriod();

    sDate Date;
    cout << "\nEnter Date to Check: ";
    Date = ReadFullDate();

    if (isDateInPeriod(Date, Period))
        cout << "\nYes, Date is within period!\n";
    else 
        cout << "\nNo, Date is not within period!\n";


    return (0);
}
