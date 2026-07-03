/*
 Problem 59
 ==========
 Create a program that reads a period (start date and end date) and prints the
 length of the period in days, with an option to include the end day.

 Notes
 =====
 - Leap years follow the Gregorian rule (February has 29 days in leap years).
 - Difference is computed by advancing the start date one day at a time until it reaches the end date.
 - Start-exclusive by default; when IncludeEndDay=true, the count is inclusive.
 - Helpers used: IncreaseDateByOneDay, isDate1BeforeDate2, NumberOfDaysInMonth.
 - Minimal input validation; intended for learning purposes.
*/


#include <iostream>
using namespace std;

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

bool isLeapYear(short Year){
    return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
}

short NumberOfDaysInMonth(short Month, short Year){
    short arrMonthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return (Month == 2) ? ((isLeapYear(Year) ? 29 : 28)) : arrMonthDays[Month - 1];
}

bool isLastDayInMonth(sDate Date){
    return (Date.Day == NumberOfDaysInMonth(Date.Month, Date.Year));
}

bool isLastMonthInYear(short Month){
    return (Month == 12);
}

bool isDate1BeforeDate2(sDate Date1, sDate Date2){
    return (Date1.Year < Date2.Year) || (Date1.Year == Date2.Year && Date1.Month < Date2.Month) ||
           (Date1.Year == Date2.Year && Date1.Month == Date2.Month && Date1.Day < Date2.Day);
}

sDate IncreaseDateByOneDay(sDate Date){
    if (isLastDayInMonth(Date)){
        if (isLastMonthInYear(Date.Month)){
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

short GetDifferenceInDays(sDate Date1, sDate Date2, bool IncludeEndDay = false){
    short Days = 0;
    while (isDate1BeforeDate2(Date1, Date2)){
        Days++;
        Date1 = IncreaseDateByOneDay(Date1);
    }
    
    return IncludeEndDay ? ++Days : Days;
}

int PeriodLengthInDays(stPeriod Period, bool IncludeEndDay = false){
    return GetDifferenceInDays(Period.StartDate, Period.EndDate, IncludeEndDay);
}

int main(){
    stPeriod Period;
    cout << "Enter Period: ";
    Period = ReadPeriod();

    cout << "\nPeriod Length Is: " << PeriodLengthInDays(Period) << endl;
    cout << "\nPeriod Length Including End Day: "
         << PeriodLengthInDays(Period, true) << endl;

    return (0);
}
