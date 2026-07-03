/*
 Problem 13
 ==========
 Create a program that reads two dates from the user and checks whether
 the first date comes before the second one.

 Notes
 =====
 - Comparison is done hierarchically: first by year, then month, then day.
 - The helper function `isDate1BeforeDate2` returns true if Date1 < Date2.
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

bool isDate1BeforeDate2(sDate Date1, sDate Date2){
    return (Date1.Year < Date2.Year) || (Date1.Year == Date2.Year && Date1.Month < Date2.Month) || 
           (Date1.Year == Date2.Year && Date1.Month == Date2.Month && Date1.Day < Date2.Day);
}

int main(){
    sDate Date1 = ReadFullDate();
    sDate Date2 = ReadFullDate();

    if (isDate1BeforeDate2(Date1, Date2))
        cout << "\nYes, Date1 is less than Date2!" << endl;
    else
        cout << "\nNo, Date1 is not less than Date2!" << endl;
    

    return (0);
}


