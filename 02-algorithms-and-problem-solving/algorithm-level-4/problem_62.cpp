/*
 Problem 62
 ==========
 Create a program that reads a date (day, month, year) and checks if it is a valid calendar date.

 Notes
 =====
 - A valid date must have:
     * Month between 1 and 12.
     * Day within the number of days of that specific month.
 - Leap years are handled correctly using the Gregorian rule.
 - February has 29 days in a leap year and 28 otherwise.
 - The program ensures:
     * Invalid days (like 31 in April or 30 in February) are rejected.
     * Negative or zero values are treated as invalid.
 - Helper functions used:
     * isLeapYear() → checks leap year condition.
     * NumberOfDaysInMonth() → returns days count in a specific month/year.
     * isValidDate() → checks if given date is valid.
 - Intended for learning validation logic in date-based programs.
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
	cout << "Pease enter a month: ";
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
	return (Month == 2) ? (isLeapYear(Year) ? 29 : 28) : arrMonthDays[Month -1];
}

bool isValidDate(sDate Date){
	if (Date.Day < 1 || Date.Month < 1)
		return false;

	return (Date.Day <= NumberOfDaysInMonth(Date.Month, Date.Year) && Date.Month <= 12);
}

int main(){
	sDate Date = ReadFullDate();

	if (isValidDate(Date))
		cout << "\nYes, It's a valid date!" << endl;
	else
		cout << "\nNo, It's NOT a valid date!" << endl;

}


