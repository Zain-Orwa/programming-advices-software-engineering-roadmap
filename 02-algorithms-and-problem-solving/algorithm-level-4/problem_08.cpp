/*
 Problem 08
 ==========
 Create a program that prints a monthly calendar for a given month and year,
 correctly aligned with the day names using the Gregorian calendar rules.

 Notes
 =====
 - The program prompts the user for:
      * A year (e.g., 2025)
      * A month (1–12)
 - Uses helper functions to modularize logic:
      * `isLeapYear()` – determines leap years using the Gregorian rule.
      * `NumberOfDaysInMonth()` – returns the total days in a month.
      * `DayOfTheWeekOrder()` – finds the weekday index (0=Sun, …, 6=Sat).
      * `MonthShortName()` and `DayShortName()` – return string abbreviations.
      * `PrintMonthCalendar()` – prints the calendar grid with proper spacing.
 - February adjusts automatically for leap years.
 - Demonstrates combined arithmetic, date calculation, and formatted console output.
 - Builds upon Problem 07 by extending weekday logic into a formatted month layout.
*/


#include <iostream>
#include <string>

using namespace std;

short ReadMonth() {
	short Month = 0;
	cout << "Please enter a month: ";
	cin >> Month;
	return Month;
}

short ReadYear() {
	short Year;
	cout << "\nPlease enter a year: "; // fixed "an year" → "a year"
	cin >> Year;
	return Year;
}

bool isLeapYear(short Year) {
	return ((Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0));
}

short NumberOfDaysInMonth(short Month, short Year) {
	if (Month < 1 || Month > 12)
		return 0;

	short arrNumberOfDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	return (Month == 2) ? (isLeapYear(Year) ? 29 : 28) : arrNumberOfDays[Month - 1];
}

short DayOfTheWeekOrder(short Day, short Month, short Year) {
	short a, y, m;
	a = (14 - Month) / 12;
	y = Year - a;
	m = Month + (12 * a) - 2;
	// Gregorian Calendar formula
	// 0:Sun, 1:Mon, 2:Tue, 3:Wed, 4:Thu, 5:Fri, 6:Sat

	return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
}

string MonthShortName(short Month) {
	string arrMonthName[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
	                           "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
	return arrMonthName[Month - 1];
}

string DayShortName(short DayOfTheWeekOrder) {
	string arrDayNames[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
	return arrDayNames[DayOfTheWeekOrder];
}

void PrintMonthCalendar(short Month, short Year) {
	short NumberOfDays = NumberOfDaysInMonth(Month, Year);
	short current = DayOfTheWeekOrder(1, Month, Year);

	printf("\n___________________%s______________________\n\n",
	       MonthShortName(Month).c_str());

	printf("   Sun   Mon   Tue   Wed   Thu   Fri   Sat\n");

	short i = 0;
	for (i = 0; i < current; i++)
		printf("%6s", "");
	for (short j = 1; j <= NumberOfDays; j++) {
		printf("%6d", j);

		if (++i == 7) {
			i = 0;
			printf("\n");
		}
	}
	printf("\n___________________________________________\n");
}

int main() {
	short Year  = ReadYear();
	short Month = ReadMonth();

	PrintMonthCalendar(Month, Year);

	return 0;
}

