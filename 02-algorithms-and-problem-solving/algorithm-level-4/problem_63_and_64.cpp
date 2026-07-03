/*
 Problem 63 & 64
 ===============
 Write a program that reads a date as a string in the format dd/mm/yyyy,
 converts it into a date structure, and then back into a string format.

 Notes
 =====
 - The program performs both conversions:
     * String → Date Structure (StringToDateStructure)
     * Date Structure → String (DateToString)
 - It also prints the Day, Month, and Year separately for clarity.
 - The input format must be consistent: "dd/mm/yyyy"
 - Helper function SplitString() is used to divide the input based on '/' delimiter.
 - stoi() is used to convert string parts into short integers.
 - The program validates parsing but assumes a correct input format.
 - This demonstrates data conversion between textual and structured formats.

 Functions
 ==========
 * ReadStringDate()       → Reads the date string from user.
 * SplitString()          → Splits the string into parts using delimiter "/".
 * StringToDateStructure()→ Converts date string into sDate struct.
 * ConvertRecordToLine()  → Converts struct to string with custom separator.
 * DateToString()         → Returns string representation of sDate.

 Example
 ========
 Input:
   Please enter Date dd/mm/yyyy? 31/3/2022

 Output:

   Day   : 31
   Month : 3
   Year  : 2022

   You entered: 31/3/2022
*/


#include <iostream>
#include <vector>
#include <string>
using namespace std;

string ReadStringDate(string Message){
	string Date = "";
	cout << Message;
	getline(cin >> ws, Date);
	return (Date);
}

struct sDate {
	short Day;
	short Month;
	short Year;
};

vector<string> SplitString(string str, string Delim){
	vector<string> vString;
	string sWord = "";
	size_t pos = 0;
	while ((pos = str.find(Delim)) != std::string::npos)
	{
		sWord = str.substr(0, pos);
		if (!sWord.empty())
		{
			vString.push_back(sWord);
		}
		str.erase(0, pos + Delim.length());
	}
	if (!str.empty()){
		vString.push_back(str);
	}
	return (vString);
} 

sDate StringToDateStructure(string DateString){
	sDate Date;
	vector<string> vDate = SplitString(DateString, "/");

	Date.Day   = stoi(vDate[0]);
	Date.Month = stoi(vDate[1]);
	Date.Year  = stoi(vDate[2]);

	return (Date);
}

string ConvertRecordToLine(sDate Date, string Seperator = "/"){
	string Line = "";

	Line += to_string(Date.Day)   + Seperator;
	Line += to_string(Date.Month) + Seperator;
	Line += to_string(Date.Year);
	
	return (Line);
}

string DateToString(sDate Date){
	return ConvertRecordToLine(Date, "/");	
}

/**** Another way for solving DateToString ****
	string DateToString(sDate Date){
		return to_string(Date.Day) + "/" + to_string(Date.Month) + "/" + to_string(Date.Year);
	}
*/

int main(){
	string DateString = ReadStringDate("Please enter Date: dd/mm/yyy? ");

	sDate Date = StringToDateStructure(DateString);

	cout << "\nDay   : " << Date.Day << endl;
	cout << "Month : " << Date.Month << endl;
	cout << "Year  : " << Date.Year << endl;

	cout << "\nYou entered: " << DateToString(Date) << endl;

	return (0);
}

