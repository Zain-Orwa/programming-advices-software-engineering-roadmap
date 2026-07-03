/*
 * Problem 33 to 46
 * ================
/*
 Problem 33 to 46
 ================
 Implement the following date utilities:

 - DecreaseDateByOneDay
 - DecreaseDateByXDays
 - DecreaseDateByOneWeek
 - DecreaseDateByXWeeks
 - DecreaseDateByOneMonth
 - DecreaseDateByXMonths
 - DecreaseDateByOneYear
 - DecreaseDateByXYears
 - DecreaseDateByXYearsFaster
 - DecreaseDateByOneDecade
 - DecreaseDateByXDecades
 - DecreaseDateByXDecadesFaster
 - DecreaseDateByOneCentury
 - DecreaseDateByOneMillennium

 Notes
 =====
 - Leap years follow the Gregorian rule (February has 29 days in leap years).
 - Helper functions handle month lengths, clamping days, and rolling back months/years.
 - Each decrement function composes simpler ones (day → week → month → year).
 - Some functions reuse logic from previous increase/decrease helpers.
 - This section is intended for learning function composition; it is not optimized.
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

bool isLeapYear(short Year){
    return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
}

short NumberOfDaysInMonth(short Month, short Year){
    if (Month < 1 || Month > 12)
        return (0);

    short arrMonthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return ((Month == 2) ? (isLeapYear(Year) ? 29 : 28) : arrMonthDays[Month - 1]);
}


sDate DecreaseDateByOneDay(sDate Date){
    if (Date.Day == 1)
    {
        if (Date.Month == 1)
        {
            Date.Day   = 31;
            Date.Month = 12;
            Date.Year--;
        }
        else
        {
            Date.Month--;
            Date.Day = NumberOfDaysInMonth(Date.Month, Date.Year);
        }
    }
    else 
    {
        Date.Day--;
    }
    
    return (Date);
}

sDate DecreaseDateByXDay(short Day, sDate Date){
    for (int i = 1; i <= Day; i++){
        Date = DecreaseDateByOneDay(Date);
    }
    return (Date);
}

sDate DecreaseDateByOneWeek(sDate Date){
    for (short i = 1; i <= 7; i++){
        Date = DecreaseDateByOneDay(Date);
    }
    return (Date);
}

sDate DecreaseDateByXWeeks(short weeks, sDate Date){
    for (short i = 1; i <= weeks; i++){
        Date = DecreaseDateByOneWeek(Date);
    }
    return (Date);
}

sDate DecreaseDateByOneMonth(sDate Date){

    if (Date.Month == 1)
    {
        Date.Month = 12;
        Date.Year--;
    }
    else 
    {
        Date.Month--;
    }

    short NumberDaysInCurrentMonth = NumberOfDaysInMonth(Date.Month, Date.Year);
    if (Date.Day > NumberDaysInCurrentMonth)
    {
        Date.Day = NumberDaysInCurrentMonth;
    }
    
    return (Date);
}

sDate DecreaseDateByXMonth(short Months, sDate Date){
    for (int i = 1; i <= Months; i++){
        Date = DecreaseDateByOneMonth(Date);
    }
    return (Date);
}

sDate DecreaseDateByOneYear(sDate Date){
    Date.Year--;
    return (Date);
}

sDate DecreaseDateByXYears(short Years, sDate Date){
    for (int i = 1; i <= Years; i++){
        Date = DecreaseDateByOneYear(Date);
    }
    return (Date);
}

sDate DecreaseDateByXYearsFaster(short Years, sDate Date){
    Date.Year -= Years;
    return (Date);
}

sDate DecreaseDateByOneDecade(sDate Date){
    Date.Year -= 10;
    return (Date);
}

sDate DecreaseDateByXDecade(short Decade, sDate Date){
    for (int i = 1; i <= Decade * 10; i++){
        Date = DecreaseDateByOneYear(Date);
    }
    return (Date);
}

sDate DecreaseDateByXDecadeFaster(short Decade, sDate Date){
    Date.Year -= Decade * 10;
    return (Date);
}

sDate DecreaseDateByOneCenturey(sDate Date){
    for (int i = 1; i <= 100; i++){
        Date = DecreaseDateByOneYear(Date);
    }
    return (Date);
}

int main(){
    sDate Date = ReadFullDate();

    cout << "Date After: " << endl;

    Date = DecreaseDateByOneDay(Date);
    cout << "\n01-Decreasing one day is: ";
    cout << Date.Day << "/" << Date.Month << "/" << Date.Year;

    Date = DecreaseDateByXDay(10, Date);
    cout << "\n02-Decreasing 10 days is: ";
    cout << Date.Day << "/" << Date.Month << "/" << Date.Year;

    Date = DecreaseDateByOneWeek(Date);
    cout << "\n03-Decreasing one week is: ";
    cout << Date.Day << "/" << Date.Month << "/" << Date.Year;

    Date = DecreaseDateByXWeeks(10, Date);
    cout << "\n04-Decreasing 10 weeks is: ";
    cout << Date.Day << "/" << Date.Month << "/" << Date.Year;


    Date = DecreaseDateByOneMonth(Date);
    cout << "\n05-Decreasing one month is: ";
    cout << Date.Day << "/" << Date.Month << "/" << Date.Year;

    Date = DecreaseDateByXMonth(5, Date);
    cout << "\n06-Decreasing 5 month is: ";
    cout << Date.Day << "/" << Date.Month << "/" << Date.Year;

    Date = DecreaseDateByOneYear(Date);
    cout << "\n07-Decreasing one year is: ";
    cout << Date.Day << "/" << Date.Month << "/" << Date.Year;

    Date = DecreaseDateByXYears(10, Date);
    cout << "\n09-Decreasing 10 years is: ";
    cout << Date.Day << "/" << Date.Month << "/" << Date.Year;

    Date = DecreaseDateByXYearsFaster(10, Date);
    cout << "\n10-Decreasing 10 years faster is: ";
    cout << Date.Day << "/" << Date.Month << "/" << Date.Year;
    
    Date = DecreaseDateByOneDecade(Date);
    cout << "\n11-Decreasing one decade is: ";
    cout << Date.Day << "/" << Date.Month << "/" << Date.Year;

    Date = DecreaseDateByXDecade(10, Date);
    cout << "\n12-Decreasing 10 decade is: ";
    cout << Date.Day << "/" << Date.Month << "/" << Date.Year;

    Date = DecreaseDateByXDecadeFaster(10, Date);
    cout << "\n13-Decreasing 10 decade faster is: ";
    cout << Date.Day << "/" << Date.Month << "/" << Date.Year;

    Date = DecreaseDateByOneCenturey(Date);
    cout << "\n14-Decreasing one centurey is: ";
    cout << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;

    return (0);
}


