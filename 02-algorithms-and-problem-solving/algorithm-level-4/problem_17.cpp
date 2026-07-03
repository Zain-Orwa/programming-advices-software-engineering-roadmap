/*
 Problem 17
 ==========
 Create a program that reads two dates and prints the number of days between them,
 with an option to include the end date in the count.

 Notes
 =====
 - Leap years follow the Gregorian rule (February has 29 days in leap years).
 - `NumberOfDaysInMonth` gives month lengths; `IncreaseDateByOneDay` advances dates.
 - `isDate1BeforeDate2` compares dates; the loop counts days by incrementing Date1.
 - The optional flag includes the end day when true.
 - Minimal validation; assumes Date1 <= Date2 (no negative differences).
*/



#include <iostream>
using namespace std;

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
    cout << endl;
    return (Year);
}

sDate   ReadFullDate(){
    sDate Date;
    Date.Day   = ReadDay();
    Date.Month = ReadMonth();
    Date.Year  = ReadYear();
    return (Date);
}

bool    isLeapYear(short Year){
    return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
}

short   NumberOfDaysInMonth(short Month, short Year){
    if (Month < 1 || Month > 12)
        return (0);

    short arrMonthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return ((Month == 2) ? (isLeapYear(Year) ? 29 : 28) : arrMonthDays[Month - 1]);
}

bool isLastDayInMonth(sDate Date){
    return (Date.Day == NumberOfDaysInMonth(Date.Month, Date.Year));
}

bool isLastMonthInYear(short Month){
    return (Month == 12);
}

bool isDate1BeforeDate2(sDate Date1, sDate Date2){
    return (Date1.Year < Date2.Year) || (Date1.Year == Date2.Year && Date1.Month < Date2.Month)
            || (Date1.Year == Date2.Year && Date1.Month == Date2.Month && Date1.Day < Date2.Day);
}

sDate IncreaseDateByOneDay(sDate Date){
    if (isLastDayInMonth(Date)){
        if (isLastMonthInYear(Date.Month)){
            Date.Year++;
            Date.Month = 1;
            Date.Day   = 1;
        } else {
            Date.Month++;
            Date.Day =1;
        }
    } else {
        Date.Day++;
    }
    return (Date);
}

int GetDifferenceInDays(sDate Date1, sDate Date2, bool IncludeEndDay = false){
    int Days = 0;
    
    while (isDate1BeforeDate2(Date1, Date2)){
        Days++;
        Date1 = IncreaseDateByOneDay(Date1);
    }

    return IncludeEndDay ? (Days + 1) : Days;
}

int main(){
    sDate Date1 = ReadFullDate();
    sDate Date2 = ReadFullDate();

    cout << "\nDifference is: " << GetDifferenceInDays(Date1, Date2) << endl;
    cout << "Difference (Including End Day) is: " << GetDifferenceInDays(Date1, Date2, true) << endl;


    return (0);
}

