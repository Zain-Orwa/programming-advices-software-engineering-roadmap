/*
 Problem 03
 ==========
 Re-implement the leap-year checker using a more concise and efficient
boolean expression instead of nested if/else statements.

 Notes
 =====
 - Uses a single logical expression:
       (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0)
 - Produces identical results to Problem 02 but with cleaner code.
 - Example:
     * 2000 → Leap year (divisible by 400)
     * 1900 → Not a leap year (divisible by 100 but not 400)
     * 2024 → Leap year (divisible by 4 but not 100)
 - Demonstrates:
     * Boolean operator precedence.
     * Compact condition design.
     * Cleaner, production-style code.
 - Serves as an optimized continuation of the previous Problem 02.
*/


#include <iostream>
using namespace std;

short ReadYear() {
    short Year = 1900;
    cout << "Enter Year: ";
    cin >> Year;
    return Year;	
}

bool is_leap_year(short Year) {
    return ((Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0));
}

int main() {
    short Year = ReadYear();

    if (is_leap_year(Year)) {
        cout << "\nYes, year [" << Year << "] is a leap year.\n";
    } else {
        cout << "\nNo, year [" << Year << "] is not a leap year.\n";
    }

    return 0;
}

