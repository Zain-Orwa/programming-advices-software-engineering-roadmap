/*
 Problem 19
 ==========
 Create a program that reads two dates and prints the difference in days between them,
 with an option to include the end day; if the first date is after the second, return
 a negative difference.

 Notes
 =====
 - Leap years follow the Gregorian rule (February has 29 days in leap years).
 - `NumberOfDaysInMonth` gives month lengths; `IncreaseDateByOneDay` advances dates.
 - If Date1 > Date2, the dates are swapped and the result is negated.
 - When the include-end-day flag is true, the count is inclusive.
 - Minimal input validation; intended for learning purposes.
*/



#include <iostream>
using namespace std;

struct sDate {
    short day;
    short month;
    short year;
};

short ReadDay(){
    short day = 1;
    cout << "Please enter a day: ";
    cin >> day;
    return (day);
} 

short ReadMonth(){
    short month;
    cout << "Please enter a month: ";
    cin >> month;
    return (month);
}

short ReadYear(){
    short year = 1900;
    cout << "Please enter a year: ";
    cin >> year;
    cout << "\n";
    return (year);
}

sDate ReadFullDate(){
    sDate Date;
    Date.day   = ReadDay();
    Date.month = ReadMonth();
    Date.year  = ReadYear();
    return (Date);
}

bool isLeapYear(short year){
    return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

short NumberOfDaysInMonth(short month, short year){
    if (month < 1 || month > 12)
        return (0);

    short arrMonthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return ((month == 2) ? (isLeapYear(year) ? 29 : 28) : arrMonthDays[month -1]);
}

bool isLastDayInMonth(sDate Date){
    return (Date.day == NumberOfDaysInMonth(Date.month, Date.year));
}

bool isLastMonthInYear(short month){
    return (month == 12);
}

bool isDate1BeforeDate2(sDate Date1, sDate Date2){
    return (Date1.year < Date2.year) || (Date1.year == Date2.year && Date1.month < Date2.month) ||
            (Date1.year == Date2.year && Date1.month == Date2.month && Date1.day < Date2.day);
}

sDate IncreaseDateByOneDay(sDate Date){
    if (isLastDayInMonth(Date)){
        if (isLastMonthInYear(Date.month)){
            Date.year++;
            Date.month = 1;
            Date.day   = 1;
        } else {
            Date.month++;
            Date.day = 1;
        }
    } else {
        Date.day++;
    }
    return (Date);
}

void  SwapDates(sDate& Date1, sDate& Date2){
    sDate TempDate;
    TempDate.day   = Date1.day;
    TempDate.month = Date1.month;
    TempDate.year  = Date1.year;

    Date1.day   = Date2.day;
    Date1.month = Date2.month;
    Date1.year  = Date2.year;

    Date2.day   = TempDate.day;
    Date2.month = TempDate.month;
    Date2.year  = TempDate.year;
}

int GetDifferenceInDays(sDate Date1, sDate Date2, bool IncludeEndDay = false){
    int Days = 0;
    short SwapFlagValue = 1;

    if (!isDate1BeforeDate2(Date1, Date2)){
        SwapDates(Date1, Date2);
        SwapFlagValue = - 1;
    }
    
    while (isDate1BeforeDate2(Date1, Date2)){
        
        Days++;
        Date1 = IncreaseDateByOneDay(Date1);
    }
    
    return IncludeEndDay ? ++Days * SwapFlagValue : Days * SwapFlagValue;
}

int main(){
    sDate Date1 = ReadFullDate();
    sDate Date2 = ReadFullDate();
    
    cout << "\n\nDifference is: " << GetDifferenceInDays(Date1, Date2) << " days!\n";
    cout << "Difference [Include End Days] is: " << GetDifferenceInDays(Date1, Date2, true) << " days!" << endl;

    return (0);
}


