/*
 Problem 58
 ==========
 Create a program that reads two date periods (start date and end date for each)
 and checks whether the two periods overlap.

 Notes
 =====
 - Each period is represented by a struct with start and end dates.
 - Comparison uses an enum (Before, Equal, After) to check date ordering.
 - Two periods do not overlap if one ends before the other starts.
 - Otherwise, they are considered overlapping.
 - Minimal input validation; intended for learning purposes.
*/


#include <iostream>
using namespace std;

enum enDateCompare {Before = -1, Equal = 0, After = 1};

struct sDate {
	short Day;
	short Month;
	short Year;
};

struct stPeriod {
    sDate StartDate;
    sDate EndDate;
};

short ReadDay() {
	short Day = 1;
	cout << "\nPlease enter a day: ";
	cin >> Day;
	return (Day);
}

short ReadMonth() {
	short Month = 1;
	cout << "Please enter a month: ";
	cin >> Month;
	return (Month);
}

short ReadYear() {
	short Year = 1900;
	cout << "Please enter a year: ";
	cin >> Year;
	cout << '\n';
	return (Year);
}

sDate ReadFullDate() {
	sDate Date;
	Date.Day   = ReadDay();
	Date.Month = ReadMonth();
	Date.Year  = ReadYear();

	return (Date);
}

bool isDate1EqualDate2(sDate Date1, sDate Date2) {
	return (Date1.Year == Date2.Year) ? ((Date1.Month == Date2.Month) ? ((Date1.Day == Date2.Day) ? true : false) : false) : false;
}

bool isDate1BeforeDate2(sDate Date1, sDate Date2) {
	return (Date1.Year < Date2.Year) || (Date1.Year == Date2.Year && Date1.Month < Date2.Month) ||
	       (Date1.Year == Date2.Year && Date1.Month == Date2.Month && Date1.Day < Date2.Day);
}

stPeriod ReadPeriod(){
    stPeriod Period;
    cout << "\nEnter Start Date: ";
    Period.StartDate = ReadFullDate();
    cout << "\nEnter End Date: ";
    Period.EndDate = ReadFullDate();
    return (Period);
}

enDateCompare CompareDates(sDate Date1, sDate Date2){
    return isDate1BeforeDate2(Date1, Date2) ? enDateCompare::Before : isDate1EqualDate2(Date1, Date2) ?
        enDateCompare::Equal : enDateCompare::After;
}

bool isOverlapPeriod(stPeriod Period1, stPeriod Period2){
    if (CompareDates(Period1.EndDate, Period2.StartDate) == enDateCompare::Before) return false;
		if (CompareDates(Period2.EndDate, Period1.StartDate) == enDateCompare::Before) return false;

		return true;
}

int main(void) {
    stPeriod Period1;
    cout << "\nEnter Period1: ";
    Period1 = ReadPeriod();

    stPeriod Period2;
    cout << "\nEnter Period2: ";
    Period2 = ReadPeriod();

    if (isOverlapPeriod(Period1, Period2))
        cout << "\nYes, priods are overlaped!\n";
    else
        cout << "\nNo, priods are not overlaped!\n";
	


	return (0);
}

