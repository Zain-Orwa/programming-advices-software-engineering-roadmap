/*
 Problem 56
 ==========
 Create a program that reads two dates and checks whether the first date
 comes after the second date.

 Notes
 =====
 - Equality is checked by comparing year → month → day.
 - "After" is defined as not before and not equal.
 - Comparison helpers: isDate1EqualDate2, isDate1BeforeDate2, isDate1AfterDate2.
 - Minimal input validation; intended for learning purposes.
*/



#include <iostream>

using namespace std;


struct sDate {
    short Day;
    short Month;
    short Year;
};

short ReadDay(){
    short Day = 1;
    cout << "Please enter a day: ";
    cin >> Day;
    return (Day);
}

short ReadMonth(){
    short Month = 1;
    cout << "Please enter a month: ";
    cin >> Month;
    return (Month);
}

short ReadYear(){
    short Year = 1900;
    cout << "Please enter a year: ";
    cin >> Year;
    cout << '\n';
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

bool isDate1BeforeDate2(sDate Date1, sDate Date2){
    return (Date1.Year < Date2.Year) || (Date1.Year == Date2.Year && Date1.Month < Date2.Month) || 
        (Date1.Year == Date2.Year && Date1.Month == Date2.Month && Date1.Day < Date2.Day);
}

bool isDate1AfterDate2(sDate Date1, sDate Date2){
    return (!isDate1BeforeDate2(Date1, Date2) && !isDate1EqualDate2(Date1, Date2));
}


int main(void){
    sDate Date1 = ReadFullDate();
    sDate Date2 = ReadFullDate();
    
    if (isDate1AfterDate2(Date1, Date2))
        cout << "\nYes, Date1 is after Date2!\n";
    else
        cout << "\nNo, Date1 is not after Date2!" << endl;

    return (0);
}


