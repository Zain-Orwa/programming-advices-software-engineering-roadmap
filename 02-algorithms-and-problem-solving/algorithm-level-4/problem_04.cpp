/*
 Problem 04
 ==========
 Create a program that reads a year and prints all months of that year, showing
 how many days each month has — accounting for leap years.

 Notes
 =====
 - The program reads a single year from the user.
 - It uses the Gregorian leap year rule:
      * A year is a leap year if divisible by 400.
      * Or if divisible by 4 but not by 100.
 - February has 29 days in a leap year, otherwise 28.
 - Uses a helper function `NumberOfDaysInMonth()` to determine each month’s days.
 - Demonstrates conditional logic, arrays, and function modularization in C++.
 - Builds on earlier problems (Problem 02 & 03) where leap year detection was introduced.
*/


#include <iostream>
using namespace std;

short ReadYear() {
    short Year = 1971;
    cout << "Enter Year: ";
    cin >> Year;
    return Year;	
}

bool is_leap_year(short Year) {
    return ((Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0));
}

int NumberOfDaysInYear(short Year) {
    return (is_leap_year(Year) ? 366 : 365);
}

int NumberOfHoursInYear(short Year) {
    return (NumberOfDaysInYear(Year) * 24);
} 

int NumberOfMinutesInYear(short Year) {
    return (NumberOfHoursInYear(Year) * 60);
}

int NumberOfSecondsInYear(short Year) {
    return (NumberOfMinutesInYear(Year) * 60);
}

void PrintDaysHoursMinutesSeconds() {
    short Year = ReadYear();
    cout << "\nYear [" << Year << "] has:\n\n";
    cout << "Number of Days    = " << NumberOfDaysInYear(Year) << endl;
    cout << "Number of Hours   = " << NumberOfHoursInYear(Year) << endl;
    cout << "Number of Minutes = " << NumberOfMinutesInYear(Year) << endl;
    cout << "Number of Seconds = " << NumberOfSecondsInYear(Year) << endl;
}

int main() {
    PrintDaysHoursMinutesSeconds();
    return 0;
}

