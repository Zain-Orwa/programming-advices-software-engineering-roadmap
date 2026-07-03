/*
 Problem 55
 ==========
 Create a program that reads a vacation start date and the number of vacation days,
 then calculates and prints the return date, skipping weekends.

 Notes
 =====
 - Leap years follow the Gregorian rule (February has 29 days in leap years).
 - Day-of-week is computed using a Gregorian formula (0=Sun..6=Sat).
 - The algorithm:
      * If the start date is a weekend, advance to the next business day.
      * Count vacation days, skipping Saturdays and Sundays.
      * If the return date falls on a weekend, advance to the next Monday.
 - Helpers: IncreaseDateByOneDay, isWeekend, DayOfTheWeekOrder.
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

short ReadNumberOfDays(){
    short VacationDays = 0;
    cout << "\nPlease enter vacation days: ";
    cin >> VacationDays;
    return (VacationDays);
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

bool isWeekend(sDate Date){
    short DayIndex = DayOfTheWeekOrder(Date);
    return (DayIndex == 0 || DayIndex == 6);
}

sDate CalculateVacationReturnDate(sDate DateFrom, short VacationDays){
   short WeekendCounter = 0;

    while (isWeekend(DateFrom))
    {
       DateFrom = IncreaseDateByOneDay(DateFrom);
    }

    for (short i = 1; i < VacationDays + WeekendCounter; i++){
       if (isWeekend(DateFrom))
           WeekendCounter++;
       DateFrom = IncreaseDateByOneDay(DateFrom);
    }

    while (isWeekend(DateFrom))
    {
       DateFrom = IncreaseDateByOneDay(DateFrom);
    }

    return (DateFrom);
}

int main(){
    cout << "\nVacation starts:\n";
    sDate DateFrom = ReadFullDate();

    short VacationDays = ReadNumberOfDays();
    
    DateFrom = CalculateVacationReturnDate(DateFrom, VacationDays);
    cout << "\nThe return date is: " << DayShortName(DayOfTheWeekOrder(DateFrom)) << ", " 
         << DateFrom.Day << "/" << DateFrom.Month << "/" << DateFrom.Year << endl;

    return (0);
}

