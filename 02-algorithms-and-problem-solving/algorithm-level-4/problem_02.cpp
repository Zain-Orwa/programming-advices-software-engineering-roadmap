/*
 Problem 02
 ==========
 Create a program that reads a year from the user and checks whether it is
a leap year based on the Gregorian calendar rules using a clear step-by-step
if/else structure.

 Notes
 =====
 - A leap year is:
     * Divisible by 400  → leap year.
     * Divisible by 100 (but not by 400) → not a leap year.
     * Divisible by 4 (but not by 100) → leap year.
     * Otherwise → not a leap year.
 - Functions:->
     * `ReadYear()` – reads input from the user.
     * `IsLeapYear()` – implements the conditional logic explicitly.
 - Demonstrates structured control flow and logical ordering of conditions.
 - This version focuses on clarity and step-by-step reasoning.
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
    if (Year % 400 == 0) {
        return true;
    }
    else if (Year % 100 == 0) {
        return false;
    }
    else if (Year % 4 == 0) {
        return true;
    }
    else {
        return false;
    }
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

