/*
 Problem 18
 ==========
 Create a program that reads a birth date, fetches today’s system date,
 and prints the person’s age in days.

 Notes
 =====
 - Uses <ctime> to get the current local date (year, month, day).
 - Leap years follow the Gregorian rule (February has 29 days in leap years).
 - Helpers: `NumberOfDaysInMonth`, `IncreaseDateByOneDay`, and a loop to count days.
 - The difference function can include the end day (used here to count inclusively).
 - Minimal input validation; intended for learning purposes.
*/



#include <iostream>
#include <ctime>

using namespace std;

struct sDate {
    short Day;
    short Month;
    short Year;
};

short ReadDay(){
    short Day = 1;
    cout << "Please entere a day: ";
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
    return ((Month == 2) ? ((isLeapYear(Year)) ? 29 : 28) : arrMonthDays[Month - 1]);
}

bool isDate1BeforeDate2(sDate Date1, sDate Date2){
    return (Date1.Year < Date2.Year) || (Date1.Year == Date2.Year && Date1.Month < Date2.Month) ||
            (Date1.Year == Date2.Year && Date1.Month == Date2.Month && Date1.Day < Date2.Day);
}

bool isLastDayInMonth(sDate Date){
    return (Date.Day == NumberOfDaysInMonth(Date.Month, Date.Year));
}

bool isLastMonthInYear(short Month){
    return (Month == 12);
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

int GetDifferenceInDays(sDate Date1, sDate Date2, bool InlcudeEndDay = false){
    int Days = 0;

    while (isDate1BeforeDate2(Date1, Date2)){
        Days++;
        Date1 = IncreaseDateByOneDay(Date1);
    }
    
    return InlcudeEndDay ? ++Days : Days;
}

sDate GetSystemDate(){
    sDate Date;

    time_t t = time(0);
    tm* now = localtime(&t);

    Date.Year  = now->tm_year + 1900;
    Date.Month = now->tm_mon  + 1;
    Date.Day   = now->tm_mday;

    return (Date);
}

int main(){
    cout << "Please enter your date of birth:\n\n";
    sDate Date1 = ReadFullDate();
    sDate Date2 = GetSystemDate();

    cout << "\nYour Age is: " << GetDifferenceInDays(Date1, Date2, true) << " Days" << endl;

    return (0);
}

