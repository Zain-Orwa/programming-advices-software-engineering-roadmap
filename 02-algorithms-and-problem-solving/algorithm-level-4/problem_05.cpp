/*
 Problem 05
 ==========
 Create a program that reads a year and a month number, then prints how many
 days are in that month — accurately accounting for leap years.

 Notes
 =====
 - The program prompts the user for:
      * A year (used to check leap year rules).
      * A month (1–12).
 - February has 29 days in a leap year, otherwise 28.
 - Uses a helper function `isLeapYear()` following the Gregorian rule:
      * Leap year if divisible by 400.
      * Or divisible by 4 but not by 100.
 - Function `NumberOfDaysInMonth(month, year)` determines days per month.
 - Demonstrates use of conditional logic, function reuse, and modular design.
 - Builds directly upon Problem 04 (Year → Month days relationship).
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

    if (Month == 2)
        return (is_leap_year(Year) ? 29 : 28);

    // Months with 31 days
    short arr31Days[] = {1, 3, 5, 7, 8, 10, 12};
    for (short i = 0; i < 7; ++i) {
        if (arr31Days[i] == Month)
            return 31;
    }

    // Otherwise, it's a 30-day month
    return 30;
}

int NumberOfHoursInAMonth(short Month, short Year) {
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
    cout << "Number of Days    = " << NumberOfDaysInAMonth(Month, Year)   << '\n';
    cout << "Number of Hours   = " << NumberOfHoursInAMonth(Month, Year)  << '\n';
    cout << "Number of Minutes = " << NumberOfMinutesInAMonth(Month, Year) << '\n';
    cout << "Number of Seconds = " << NumberOfSecondsInAMonth(Month, Year) << '\n';

    return 0;
}

