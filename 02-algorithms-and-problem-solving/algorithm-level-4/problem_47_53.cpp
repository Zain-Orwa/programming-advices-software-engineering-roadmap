/*
 * Problem 47 to 53
 * ================
 * Implement the following date utilities:
 * - IsEndOfWeek
 * - IsWeekend
 * - IsBusinessDay
 * - DaysUntilTheEndOfWeek
 * - DaysUntilTheEndOfMonth
 * - DaysUntilTheEndOfYear
 *
 * Notes
 * =====
 * - Day-of-week is computed via a Gregorian formula (0=Sun..6=Sat).
 * - Leap years follow the Gregorian rule; February becomes 29 days in leap years.
 * - Month lengths come from a helper (e.g., NumberOfDaysInMonth).
 * - Some functions depend on earlier helpers (e.g., IncreaseDateByOneDay, date comparison).
 * - Educational focus on composing small functions; not optimized.
 **/


#include <iostream>
#include <ctime>
using namespace std;

struct sDate {
    short Day;
    short Month;
    short Year;
};

short DayOfTheWeekOrder(short Day, short Month, short Year){
    short a, y, m;
    a = (14 - Month) / 12;
    y = Year -a;
    m = Month + (12 * a) - 2;
    return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
}

short DayOfTheWeekOrder(sDate Date){
    return (DayOfTheWeekOrder(Date.Day, Date.Month, Date.Year));
}

bool isLeapYear(short Year){
    return (Year % 4 == 0 && Year % 100) || (Year % 400 == 0);
}

short NumberOfDaysInMonth(short Month, short Year){
    short arrMonthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return ((Month == 2) ? (isLeapYear(Year) ? 29 : 28) : (arrMonthDays[Month - 1]));
}

string DayShortName(short DayOrder){
    string arrDayOrder[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    return (arrDayOrder[DayOrder]);
}

bool isLastDayInMonth(sDate Date){
    return (Date.Day == NumberOfDaysInMonth(Date.Month, Date.Year));
}

bool isLastMonthInYear(short Month){
    return (Month == 12);
}

bool isEndOfWeek(sDate Date){
    return (DayOfTheWeekOrder(Date) == 6);
}

bool isWeekend(sDate Date){
    short DayIndex = DayOfTheWeekOrder(Date);
    return (DayIndex == 0 || DayIndex == 6);
}

bool isBusinessDay(sDate Date){
    return (!isWeekend(Date));
}

short DaysUntilEndOfWeek(sDate Date){
    return (6 - DayOfTheWeekOrder(Date));
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
        } else{
            Date.Month++;
            Date.Day = 1;
        }
    } else {
        Date.Day++;
    }
    return (Date);
}

short GitDifferenceInDays(sDate Date1, sDate Date2, bool IncludeEndDay = false){
    short Days = 0;

    while (isDate1BeforeDate2(Date1, Date2)){
        Days++;
        Date1 = IncreaseDateByOneDay(Date1);
    }
    return IncludeEndDay ? ++Days : Days;
}

short DaysUntilEndOfMonth(sDate Date){
    sDate EndOfMonDate;
    EndOfMonDate.Day   = NumberOfDaysInMonth(Date.Month, Date.Year);
    EndOfMonDate.Month = Date.Month; 
    EndOfMonDate.Year  = Date.Year;

    return GitDifferenceInDays(Date, EndOfMonDate, true);
}

short DaysUntilEndOfYear(sDate Date){
    sDate EndOfYearDate;
    EndOfYearDate.Day   = 31;
    EndOfYearDate.Month = 12;
    EndOfYearDate.Year  = Date.Year;

    return GitDifferenceInDays(Date, EndOfYearDate, true);
}

sDate GetSystemDate(){
    sDate Date;
    time_t t = time(0);
    tm* now = localtime(&t);

    Date.Year  = now->tm_year + 1900;
    Date.Month = now->tm_mon + 1;
    Date.Day   = now->tm_mday;

    return (Date);
}

int main(){
    sDate Date = GetSystemDate();
    
    cout << "Today is " << DayShortName(DayOfTheWeekOrder(Date)) <<  ", "
         << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;

    //___________________________________//
    cout << "\nIs It End of Week?\n";
    if (isEndOfWeek(Date)){
        cout << "Yes, it's Saturday, It's End of Week!\n";
    } else {
        cout << "No, It's Not End of Week!\n";
    }
    //___________________________________//
    cout << "\nIs It Weekend?\n";
    if (isWeekend(Date)){
        cout << "Yes, It's a Weekend!\n";
    } else {
        cout << "No, Today Is " << DayShortName(DayOfTheWeekOrder(Date)) 
             << " Not a Weekend!\n";
    }
    //___________________________________//
    cout << "\nIs It a Business Day?\n";
    if (isBusinessDay(Date)){
        cout << "Yes, It's a Business Day!\n";
    } else {
        cout << "No, It's Not a Business Day!\n";
    }

    //___________________________________//
    cout << "\nDays Until End of The Week: " 
         << DaysUntilEndOfWeek(Date) << " Days!\n";
    //___________________________________//
    cout << "\nDays Until End of The Month: " <<
        DaysUntilEndOfMonth(Date) << " Days!\n";
    //___________________________________//
    cout << "\nDays Until End of The Year: " << 
        DaysUntilEndOfYear(Date) << " Days!" << endl;
    //___________________________________//

    return (0);
}
