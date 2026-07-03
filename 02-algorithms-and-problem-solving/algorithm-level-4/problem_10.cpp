/*
 Problem 10
 ==========
 Create a program that calculates how many days have passed since the beginning
 of a given year up to a specified date (day, month, year).

 Notes
 =====
 - The program reads a complete date:
      * Day (1–31)
      * Month (1–12)
      * Year (e.g., 2025)
 - It sums up the total days from January 1st to the entered date.
 - Helper functions:
      * `isLeapYear()` – checks if the year is a leap year using the Gregorian rule.
      * `NumberOfDaysInMonth()` – returns the correct number of days for each month.
      * `NumberOfDaysFromBeginningOfTheYear()` – loops through months before the given one
        and adds all their days plus the current day.
 - February automatically adjusts to 29 days in leap years.
 - Demonstrates cumulative counting, loop logic, and modular function design.
 - Builds on previous problems by introducing date summation logic.
*/


#include <iostream>
using namespace std;

short  ReadYear(){
   short Year = 1971;
   cout << "\nPlease enter a year: ";
   cin >> Year;
   return (Year);
}

short ReadMonth(){
    short Month = 1;
    cout << "\nPlease enter a Month: ";
    cin >> Month;
    return (Month);
}



short ReadDay(){
    short DayOfMonth = 0;
    cout << "\nPlease enter a day: ";
    cin >> DayOfMonth;
    return (DayOfMonth);
}

bool isLeapYear(short Year){
    return ((Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0));
}

short NumberOfDaysInMonth(short Month, short Year){
    if (Month < 1 || Month > 12)
        return (0);

    short NumberOfDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return ((Month == 2) ? (isLeapYear(Year)) ? 29 : 28 : (NumberOfDays[Month - 1]));

}


short NumberOfDaysFromBeginningOfTheYear(short Day, short Month, short Year){

    short TotalDays = 0;

    for (short i = 0; i < Month - 1; i++){
        TotalDays += NumberOfDaysInMonth(i, Year);
    }
    
    TotalDays += Day;

    return (TotalDays); 
}


int main(){
    short Day   = ReadDay();
    short Month = ReadMonth();
    short Year  = ReadYear();

    cout << "\nNumber of Days from the beginning of the year is: "
         << NumberOfDaysFromBeginningOfTheYear(Day, Month, Year);
    cout << "\n\n";


    return (0);
}
