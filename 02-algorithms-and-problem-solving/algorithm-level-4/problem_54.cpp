/*
 Problem 54
 ==========
 Create a program that reads a vacation start and end date, then prints the
 number of actual vacation days (business days only, excluding weekends).

 Notes
 =====
 - Day-of-week is computed via a Gregorian formula (0=Sun..6=Sat).
 - Leap years follow the Gregorian rule; February becomes 29 days in leap years.
 - A helper advances the date one day at a time and counts only Mon–Fri.
 - Counting is start-inclusive and end-exclusive, matching the loop condition.
 - Some helpers depend on earlier functions (e.g., NumberOfDaysInMonth).
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
    return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
}

short NumberOfDaysInMonth(short Month, short Year){
    short arrMonthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return ((Month == 2) ? (isLeapYear(Year) ? 29 : 28) : arrMonthDays[Month - 1]);
}

short DayOfTheWeekOrder(short Day, short Month, short Year){
    short a, y, m;
    a = (14 - Month) / 12;
    y = Year - a;
    m = Month + (12 * a) - 2;
    return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
}

short DayOfTheWeekOrder(sDate Date){
    return DayOfTheWeekOrder(Date.Day, Date.Month, Date.Year);
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

string DayShortName(short DayOrder){
    string arrDayName[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    return arrDayName[DayOrder];
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

bool isWeekend(sDate Date){
    short DayIndex = DayOfTheWeekOrder(Date);
    return (DayIndex == 0 || DayIndex == 6);
}

bool isBusinessDay(sDate Date){
    return (!isWeekend(Date));
}

short CalculateActualVacationDays(sDate DateFrom, sDate DateTo){
    short DayCount = 0;
    while (isDate1BeforeDate2(DateFrom, DateTo))
    {
        if (isBusinessDay(DateFrom))
            DayCount++;

        DateFrom = IncreaseDateByOneDay(DateFrom);
    }
    return (DayCount);
}

int main(){
    cout << "\nVacation Starts:\n";
    sDate DateFrom = ReadFullDate();

    cout << "\nVacation Ends:\n";
    sDate DateTo = ReadFullDate();

    cout << "\nVacation From: " << DayShortName(DayOfTheWeekOrder(DateFrom)) << ", " << DateFrom.Day << "/"
         << DateFrom.Month << "/" << DateFrom.Year;

    cout << "\nVacation To  : "  << DayShortName(DayOfTheWeekOrder(DateTo)) << ", " << DateTo.Day << "/"
         << DateTo.Month << "/" << DateTo.Year;

    cout << "\n\nAcctual vaction days is: " << CalculateActualVacationDays(DateFrom, DateTo) << endl;

    
    return (0);
}

