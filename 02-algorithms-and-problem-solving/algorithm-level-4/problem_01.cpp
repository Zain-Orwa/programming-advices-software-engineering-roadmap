/*
 Problem 01
 ==========
 Create a program that reads a number from the user and converts it
into its full English text representation (e.g., 12345 → "Twelve Thousand Three Hundred Forty Five").

 Notes
 =====
 - Handles numbers from negative trillions up to positive trillions.
 - Uses recursion to decompose the number into smaller chunks (hundreds, thousands, millions, billions).
 - Handles special cases like:
     * Zero → "Zero"
     * Negative numbers → prefixed with "Minus"
 - Demonstrates string concatenation and modular arithmetic for digit isolation.
 - Teaches recursive design thinking and function breakdown.
 - This problem serves as a foundation for understanding number manipulation in C++.
*/


#include <iostream>
#include <string>

using namespace std;

long long ReadNumber() {
    long long Number = 0;
    cout << "Please enter a number: ";
    cin >> Number;
    return Number;
}

string NumberToText(long long Number) {
    if (Number == 0) {
        return "Zero";
    }

    if (Number < 0) {
        return "Minus " + NumberToText(-Number);
    }

    if (Number >= 1 && Number <= 19) {
        string arr[] = {
            "", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine",
            "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen",
            "Sixteen", "Seventeen", "Eighteen", "Nineteen"
        };
        return arr[Number];
    }

    if (Number >= 20 && Number <= 99) {
        string arr[] = { "", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety" };
        return arr[Number / 10] + (Number % 10 ? " " + NumberToText(Number % 10) : "");
    }

    if (Number >= 100 && Number <= 199) {
        return "One Hundred" + (Number % 100 ? " " + NumberToText(Number % 100) : "");
    }

    if (Number >= 200 && Number <= 999) {
        return NumberToText(Number / 100) + " Hundred" + (Number % 100 ? " " + NumberToText(Number % 100) : "");
    }

    if (Number >= 1000 && Number <= 1999) {
        return "One Thousand" + (Number % 1000 ? " " + NumberToText(Number % 1000) : "");
    }

    if (Number >= 2000 && Number <= 999999) {
        return NumberToText(Number / 1000) + " Thousand" + (Number % 1000 ? " " + NumberToText(Number % 1000) : "");
    }

    if (Number >= 1000000 && Number <= 1999999) {
        return "One Million" + (Number % 1000000 ? " " + NumberToText(Number % 1000000) : "");
    }

    if (Number >= 2000000 && Number <= 999999999) {
        return NumberToText(Number / 1000000) + " Million" + (Number % 1000000 ? " " + NumberToText(Number % 1000000) : "");
    }

    if (Number >= 1000000000LL && Number <= 1999999999LL) {
        return "One Billion" + (Number % 1000000000LL ? " " + NumberToText(Number % 1000000000LL) : "");
    }

    if (Number >= 2000000000LL && Number <= 999999999999LL) {
        return NumberToText(Number / 1000000000LL) + " Billion" + (Number % 1000000000LL ? " " + NumberToText(Number % 1000000000LL) : "");
    }

    if (Number >= 1000000000000LL && Number <= 1999999999999LL) {
        return "One Trillion" + (Number % 1000000000000LL ? " " + NumberToText(Number % 1000000000000LL) : "");
    }

    // 2 Trillion and above (continues chunking by trillions)
    return NumberToText(Number / 1000000000000LL) + " Trillion" +
           (Number % 1000000000000LL ? " " + NumberToText(Number % 1000000000000LL) : "");
}

int main() {
    long long Number = ReadNumber();
    cout << "\n" << NumberToText(Number) << endl;
    return 0;
}

