/*
 * Problem 20 to 32
 * ================
 *  Write programs to read a date (day, month, year) and create functions that
 *  demonstrate how to increase the date as follows:
 *
 *- IncreaseDateByXDays
 *- IncreaseDateByOneWeek
 *- IncreaseDateByXWeeks
 *- IncreaseDateByOneMonth
 *- IncreaseDateByXMonths
 *- IncreaseDateByOneYear
 *- IncreaseDateByXYears
 *- IncreaseDateByXYearsFaster
 *- IncreaseDateByOneDecade
 *- IncreaseDateByXDecades
 *- IncreaseDateByXDecadesFaster
 *- IncreaseDateByOneCentury
 *- IncreaseDateByOneMillennium
 *
 * Notes
 * =====
 *- Leap years follow the Gregorian rule (February has 29 days in leap years).
 *- Helper functions handle month lengths, clamping days, and rolling over months/years.
 *- Each increment function builds on smaller ones (e.g., add days → add weeks → add months).
 *- Some functions have “faster” variants that use arithmetic instead of loops.
 *- This section is intended to teach how to combine functions;
 * it is not optimized for efficiency.
 **/

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

    short arrMonthDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return ((Month == 2) ? (isLeapYear(Year) ? 29 : 28) : arrMonthDays[Month - 1]);
}

bool isLastDayInMonth(sDate Date){
    return (Date.Day == NumberOfDaysInMonth(Date.Month, Date.Year));
}

bool isLastMonthInYear(short Month){
    return (Month == 12);
}

short ClampDay(short Day, short Month, short Year){
    short Max = NumberOfDaysInMonth(Month, Year);
    return Day > Max ? Max : Day;
}

sDate IncreaseDateByOneDay(sDate Date){
    if (isLastDayInMonth(Date)){
        if (isLastMonthInYear(Date.Month)){
            Date.Year++;
            Date.Month = 1;
            Date.Day   = 1;
        } else{
            Date.Month++;
            Date.Day = 1;
        }
    } else {
        Date.Day++;
    }    
    return (Date);
}

sDate   IncreaseDateByXDays(short Day, sDate Date){
    for (int i = 1; i <= Day; i++){
        Date = IncreaseDateByOneDay(Date);
    }
    return (Date);
}

sDate IncreaseDateByOneWeek(sDate Date){
    for (int i = 1; i <= 7; i++){
        Date = IncreaseDateByOneDay(Date);
    }
    return (Date);
}

sDate IncreaseDateByXweeks(short Week, sDate Date){
    for (int i = 1; i <= Week; i++){
        Date = IncreaseDateByOneWeek(Date);
    }
    return (Date);
}

sDate IncreaseDateByOneMonth(sDate Date){
    if (Date.Month == 12){
        Date.Month = 1;
        Date.Year++;
    } else{
        Date.Month++;
    }    

    short NumberOfDaysInCurrentMonth = NumberOfDaysInMonth(Date.Month, Date.Year);
    if (Date.Day > NumberOfDaysInCurrentMonth){
        Date.Day = NumberOfDaysInCurrentMonth; 
    }

    return (Date);
}

sDate IncreaseDateByXMonth(short Month, sDate Date){
    for (int i = 1; i <= Month; i++){
        Date = IncreaseDateByOneMonth(Date);
    }    
    return (Date);
}

sDate IncreaseDateByOneYear(sDate Date){
    Date.Year++;
    Date.Day = ClampDay(Date.Day, Date.Month, Date.Year);
    return (Date);
}

sDate IncreaseDateByXYear(short Year, sDate Date){
    for (int i = 1; i <= Year; i++){
        Date = IncreaseDateByOneYear(Date);
    }
    return (Date); 
}

sDate IncreaseDateByXYearFaster(short Year, sDate Date){
    Date.Year += Year;
    Date.Day = ClampDay(Date.Day, Date.Month, Date.Year);
    return (Date);
}

sDate IncreaseDateByOneDecade(sDate Date){
    Date.Year += 10;
    Date.Day = ClampDay(Date.Day, Date.Month, Date.Year);
    return (Date);
}

sDate IncreaseDateByXDecade(short Decade, sDate Date){
    for (int i = 1; i <= Decade * 10; i++){
        Date = IncreaseDateByOneYear(Date);
    }
    return (Date);
}

sDate IncreaseDateByXDecadeFaster(short Decade, sDate Date){
    Date.Year += Decade * 10;
    Date.Day = ClampDay(Date.Day, Date.Month, Date.Year);
    return (Date);
}

sDate IncreaseDateByOneCentury(sDate Date){
    Date.Year += 100;
    Date.Day = ClampDay(Date.Day, Date.Month, Date.Year);
    return (Date);
}

sDate IncreaseDateByOneMillennium(sDate Date){
    Date.Year += 1000;
    Date.Day = ClampDay(Date.Day, Date.Month, Date.Year);
    return (Date);
}

int main(){
    sDate Date = ReadFullDate();

    cout << "\nDate After:\n";

    Date = IncreaseDateByOneDay(Date);
    cout << "\n01-Adding one day is: ";
    cout << Date.Day << "/" << Date.Month << "/" << Date.Year;

    Date = IncreaseDateByXDays(10, Date);
    cout << "\n02-Adding 10 day is: ";
    cout << Date.Day << "/" << Date.Month << "/" << Date.Year;

    Date = IncreaseDateByOneWeek(Date);
    cout << "\n03-Adding One Week is: ";
    cout << Date.Day << "/" << Date.Month << "/" << Date.Year;

    Date = IncreaseDateByXweeks(10, Date);
    cout << "\n04-Adding 10 weeks is: ";
    cout << Date.Day << "/" << Date.Month << "/" << Date.Year;

    Date = IncreaseDateByOneMonth(Date);
    cout << "\n05-Adding one month is: ";
    cout << Date.Day << "/" << Date.Month << "/" << Date.Year;

    Date = IncreaseDateByXMonth(5, Date);
    cout << "\n06-Adding 5 Month is: ";
    cout << Date.Day << "/" << Date.Month << "/" << Date.Year;

    Date = IncreaseDateByOneYear(Date);
    cout << "\n07-Adding one year is: ";
    cout << Date.Day << "/" << Date.Month << "/" << Date.Year;

    Date = IncreaseDateByXYear(10, Date);
    cout << "\n08-Adding 10 years is: ";
    cout << Date.Day << "/" << Date.Month << "/" << Date.Year;

    Date = IncreaseDateByXYearFaster(10, Date);
    cout << "\n09-Adding 10 year faster is: ";
    cout << Date.Day << "/" << Date.Month << "/" << Date.Year;

    Date = IncreaseDateByOneDecade(Date);
    cout << "\n10-Adding one decade is: ";
    cout << Date.Day << "/" << Date.Month << "/" << Date.Year;

    Date = IncreaseDateByXDecadeFaster(10, Date);
    cout << "\n11-Adding 10 decade faster is: ";
    cout << Date.Day << "/" << Date.Month << "/" << Date.Year;

    Date = IncreaseDateByOneCentury(Date);
    cout << "\n12-Adding one century is: ";
    cout << Date.Day << "/" << Date.Month << "/" << Date.Year;

    Date = IncreaseDateByOneMillennium(Date);
    cout << "\n13-Adding one millennium is: ";
    cout << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;

    return (0);
}


