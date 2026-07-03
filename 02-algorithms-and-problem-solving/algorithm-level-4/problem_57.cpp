/*
 Problem 57
 ==========
 Create a program that reads two dates and compares them, returning whether
 the first date is before, equal to, or after the second date.

 Notes
 =====
 - Comparison result is represented by an enum:
      * -1 = Before
      *  0 = Equal
      *  1 = After
 - Helper functions check for equality and "before" ordering.
 - CompareDates uses these helpers to return the appropriate enum value.
 - Minimal input validation; intended for learning purposes.
*/



#include <iostream>
using namespace std;

enum enDateCompare {Before = -1, Equal = 0, After = 1};

struct sDate {
    short Day;
    short Month;
    short Year;
};

short ReadDay(){
    short Day = 1;
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
    cout << '\n';
    return (Year);
}

sDate ReadFullDate(){
    sDate Date;
    Date.Day   = ReadDay();
    Date.Month = ReadMonth();
    Date.Year  = ReadYear();

    return (Date);
}

bool isDate1EqualDate2(sDate Date1, sDate Date2){
    return (Date1.Year == Date2.Year) ? ((Date1.Month == Date2.Month) ? ((Date1.Day == Date2.Day) ? true : false) : false) : false; 
}

bool isDate1BeforeDate2(sDate Date1, sDate Date2){
    return (Date1.Year < Date2.Year) || (Date1.Year == Date2.Year && Date1.Month < Date2.Month) || 
        (Date1.Year == Date2.Year && Date1.Month == Date2.Month && Date1.Day < Date2.Day);
}

enDateCompare CompareDates(sDate Date1, sDate Date2){
    return (isDate1BeforeDate2(Date1, Date2)) ? enDateCompare::Before : isDate1EqualDate2(Date1, Date2) ?
        enDateCompare::Equal : enDateCompare::After;
}

int main(void){
    sDate Date1 = ReadFullDate();
    sDate Date2 = ReadFullDate();

    enDateCompare Result = CompareDates(Date1, Date2);

    cout << "\nCompare Result = " << Result << endl;
    
    return (0);
}



