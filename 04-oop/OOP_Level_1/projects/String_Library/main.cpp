#include <iostream>
#include "clsString.h"

using namespace std;


int main(void)
{
    clsString   String1;
    clsString   String2("Mohammed");
    
    String1.SetValue("Ali Ahmed");

    cout << "String1 = " << String1.GetValue() << endl;
    cout << "String2 = " << String2.GetValue() << endl;

    cout << "Number of Word in String1 = " << String1.CountWords() << endl;
    cout << "Number of Word in String2 = " << String2.CountWords() << endl;


    cout << "Using Static Function to count String1: " << 
                String1.CountWords("Fadi Ahmed Ratib Omer") << endl;

    return (0);
}