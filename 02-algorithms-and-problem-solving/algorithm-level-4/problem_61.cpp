/*
 Problem 61
 ==========
 Create a program that reads two date periods and calculates how many days overlap between them.

 Notes
 =====
 - Each period is defined by a StartDate and EndDate.
 - Leap years follow the Gregorian rule (February has 29 days in leap years).
 - The program:
     * Checks if the two periods overlap using CompareDate().
     * If they overlap, counts how many days fall within both periods.
     * Handles inclusive bounds when counting days.
 - Helper functions used:
     * isDateInPeriod(), isOverLapPeriod(), PeriodLengthInDays(), IncreaseDateByOneDay().
 - Demonstrates combined use of multiple previously built date utilities.
 - Intended for educational purposes, not optimized for performance.
*/


#include <iostream>
using namespace std;

enum enCompareDate {Before = -1, Equal = 0, After = 1};

struct sDate {
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
    cout << "\nEnter Start Date:";
    Period.StartDate = ReadFullDate();
    cout << "\nEnter End Date: ";
    Period.EndDate = ReadFullDate();
    return (Period);
}

bool isDate1BeforeDate2(sDate Date1, sDate Date2){
    return (Date1.Year < Date2.Year) || (Date1.Year == Date2.Year && Date1.Month < Date2.Month) ||
        (Date1.Year == Date2.Year && Date1.Month == Date2.Month && Date1.Day < Date2.Day);
}

bool isDate1EqualDate2(sDate Date1, sDate Date2){
    return (Date1.Year == Date2.Year) && (Date1.Month == Date2.Month) && (Date1.Day == Date2.Day);
}

enCompareDate CompareDate(sDate Date1, sDate Date2){
    if (isDate1BeforeDate2(Date1, Date2)) return enCompareDate::Before;
    if (isDate1EqualDate2(Date1, Date2))  return enCompareDate::Equal;

    return enCompareDate::After;
}

bool isDateInPeriod(sDate Date, stPeriod Period){
    return !((CompareDate(Date, Period.StartDate) == enCompareDate::Before) || 
              CompareDate(Date, Period.EndDate)   == enCompareDate::After);
}

bool isLeapYear(short Year){
    return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
}

short NumberOfDaysInMonth(short Month, short Year){
    short arrMonthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return (Month == 2) ? (isLeapYear(Year) ? 29 : 28): arrMonthDays[Month -1]; 
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

int GetDiffernceInDays(sDate Date1, sDate Date2, bool IncludeEndDay = false){
    int Days = 0;

    while (isDate1BeforeDate2(Date1, Date2)){
        Days++;
        Date1 = IncreaseDateByOneDay(Date1);
    }

    return IncludeEndDay ? ++Days : Days;
}

int PeriodLengthInDays(stPeriod Period, bool IncludeEndDay = false){
    return GetDiffernceInDays(Period.StartDate, Period.EndDate, IncludeEndDay);
}

bool isOverLapPeriod(stPeriod Period1, stPeriod Period2){
    if (CompareDate(Period2.EndDate, Period1.StartDate) == enCompareDate::Before ||
        CompareDate(Period2.StartDate, Period1.EndDate)  == enCompareDate::After)
        return false;
    else
        return true;
}

int CountOverlapDays(stPeriod Period1, stPeriod Period2){
    int Period1Length = PeriodLengthInDays(Period1, true);
    int Period2Length = PeriodLengthInDays(Period2, true);
    int OverLapDays = 0;

    if (!isOverLapPeriod(Period1, Period2))
        return (false);

    if (Period1Length < Period2Length)
    {
        while (isDate1BeforeDate2(Period1.StartDate, Period1.EndDate))
        {
            if (isDateInPeriod(Period1.StartDate, Period2))
                OverLapDays++;

            Period1.StartDate = IncreaseDateByOneDay(Period1.StartDate);
        }
    }
    else
    {
        while(isDate1BeforeDate2(Period2.StartDate, Period2.EndDate))
        {
            if (isDateInPeriod(Period2.StartDate, Period1))
                OverLapDays++;

            Period2.StartDate = IncreaseDateByOneDay(Period2.StartDate);
        }
    }
    
    return (OverLapDays);
}


int main(){
    cout << "\nEnter Period 1:";
    stPeriod Period1 = ReadPeriod();

    cout << "\nEnter Period2: ";
    stPeriod Period2 = ReadPeriod();

    cout << "\nOverlap Days Count Is = " << CountOverlapDays(Period1, Period2) << endl;

    return (0);
}

