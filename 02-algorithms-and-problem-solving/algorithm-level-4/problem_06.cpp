/*
 Problem 06
 ==========
 Create a program that reads a year and a month number, then calculates how many
 days, hours, minutes, and seconds exist in that month — accurately handling leap years.

 Notes
 =====
 - The program prompts the user for:
      * A year (used for leap year calculation).
      * A month (1–12).
 - February has 29 days in leap years, otherwise 28.
 - Helper functions:
      * `is_leap_year()` – determines if the year follows the Gregorian leap rule.
      * `NumberOfDaysInAMonth()` – returns days per month.
      * `NumberOfHoursInAMonth()` – converts days to hours.
      * `NumberOfMinutesInAMonth()` – converts hours to minutes.
      * `NumberOfSecondsInAMonth()` – converts minutes to seconds.
 - Demonstrates hierarchical function composition and arithmetic precision with `long long`.
 - Builds upon Problems 04 and 05, extending date logic to time units.
*/


#include <iostream>
using namespace std;

short ReadYear() {
    short Year;
    cout << "Please enter a year to check: ";
    cin >> Year;
    return Year;	
}

short ReadMonth() {
    short Month;
    cout << "\nPlease enter a month to check: ";
    cin >> Month;
    return Month;
}

bool is_leap_year(short Year) {
    return ((Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0));
}

short NumberOfDaysInAMonth(short Month, short Year) {
    if (Month < 1 || Month > 12)
        return 0;

    short arrNumberOfDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return (Month == 2) ? (is_leap_year(Year) ? 29 : 28) : arrNumberOfDays[Month - 1];
}

short NumberOfHoursInAMonth(short Month, short Year) {
    return NumberOfDaysInAMonth(Month, Year) * 24;
}

int NumberOfMinutesInAMonth(short Month, short Year) {
    return NumberOfHoursInAMonth(Month, Year) * 60;
}

long long NumberOfSecondsInAMonth(short Month, short Year) {
    return static_cast<long long>(NumberOfMinutesInAMonth(Month, Year)) * 60LL;
}

int main() {
    short Year  = ReadYear();
    short Month = ReadMonth();

    cout << "\nResults for Month [" << Month << "] of Year [" << Year << "]:\n";
    cout << "Number of Days    = " << NumberOfDaysInAMonth(Month, Year)    << '\n';
    cout << "Number of Hours   = " << NumberOfHoursInAMonth(Month, Year)   << '\n';
    cout << "Number of Minutes = " << NumberOfMinutesInAMonth(Month, Year) << '\n';
    cout << "Number of Seconds = " << NumberOfSecondsInAMonth(Month, Year) << '\n';

    return 0;
}

