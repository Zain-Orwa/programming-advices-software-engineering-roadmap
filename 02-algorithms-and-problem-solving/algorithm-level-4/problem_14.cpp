/*
 Problem 14
 ==========
 Create a program that reads two dates from the user and checks whether
 the two dates are equal.

 Notes
 =====
 - Equality is verified by comparing year, then month, then day.
 - The helper function `isDate1BeforeDate2` returns true only if all
   three components are equal.
 - Input validation is minimal; this implementation is for learning purposes.
*/



#include <iostream>
using namespace std;


struct sDate {
    short Day;
    short Month;
    short Year;
};

short ReadDay(){
    short Day = 0;
    cout << "Please enter a day: ";
    cin >> Day;
    return (Day);
}

short ReadMonth(){
    short Month = 0;
    cout << "Please enter a month: ";
    cin >> Month;
    return (Month);
}

short ReadYear(){
    short Year = 1900;
    cout << "Please enter a year: ";
    cin >> Year;
    cout << endl;
    return (Year);
}

sDate ReadFullDate(){
    sDate Date;
    Date.Day   = ReadDay();
    Date.Month = ReadMonth();
    Date.Year  = ReadYear();
    return (Date);
}

bool isDate1EqualDate2(sDate Date1, sDate Date2){
    return (Date1.Year == Date2.Year) ? ((Date1.Month == Date2.Month) ? ((Date1.Day == Date2.Day) ? true : false) : false) : false;
}

int main(){
    sDate Date1 = ReadFullDate();
    sDate Date2 = ReadFullDate();

    if (isDate1EqualDate2(Date1, Date2))
        cout << "\nYes, Date1 is equal to Date2!" << endl;
    else
        cout << "\nNo, Date1 is not equal to Date2!" << endl;
    

    return (0);
}



