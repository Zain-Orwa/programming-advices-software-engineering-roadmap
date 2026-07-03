/*
 Problem 07
 ==========
 Create a program that reads a full date (day, month, year) and determines which
 day of the week it corresponds to — using the Gregorian calendar formula.

 Notes
 =====
 - The program prompts the user for a specific date:
      * Day (1–31)
      * Month (1–12)
      * Year (e.g., 2025)
 - Implements the **Gregorian Day-of-Week algorithm**:
      * Formula: (Day + y + y/4 − y/100 + y/400 + (31*m)/12) % 7
      * Returns a value 0–6 representing:
          0 → Sunday, 1 → Monday, 2 → Tuesday, 3 → Wednesday,
          4 → Thursday, 5 → Friday, 6 → Saturday
 - The helper function `DayShortName()` converts this numeric result to a
   human-readable day abbreviation (e.g., "Mon", "Tue").
 - Demonstrates modularization, integer arithmetic, and calendar computation.
 - Builds upon previous date-based problems by introducing weekday logic.
*/

#include <iostream>
using namespace std;

short DayOfTheWeekOrder(short Day, short Month, short Year){
	short a, y, m;
	a = (14 - Month) / 12;
	y = Year - a;
	m = Month + (12 * a) - 2;
	// Gregorian Calendar formula
	// 0:Sun, 1:Mon, 2:Tue, 3:Wed, 4:Thu, 5:Fri, 6:Sat
	
	return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
}

short ReadDay(){
	short Day;
	cout << "\nPlease enter a day: ";
	cin >> Day;
	return (Day);
}

short ReadMonth(){
	short Month;
	cout << "\nPlease enter a month: "; // fixed typo (Month → month)
	cin >> Month;
	return (Month);
}

short ReadYear(){
	short Year;
	cout << "\nPlease enter a year: "; // fixed typo (an year → a year)
	cin >> Year;
	return (Year);
}

string DayShortName(short DayOfTheWeekOrder){
	string arrDayNames[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
	return arrDayNames[DayOfTheWeekOrder];
}

int main(){
	short Day    = ReadDay();
	short Month  = ReadMonth();
	short Year   = ReadYear();

	cout << "\nDate      : " << Day << "/" << Month << "/" << Year;
	cout << "\nDay Order : " << DayOfTheWeekOrder(Day, Month, Year);
	cout << "\nDay Name  : " << DayShortName(DayOfTheWeekOrder(Day, Month, Year)) << endl;

	return (0);
}

