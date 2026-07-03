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

sDate StringToDate(string DateString){
	sDate Date;
	vector<string> vDate = SplitString(DateString, "/");

	Date.Day   = stoi(vDate[0]);
	Date.Month = stoi(vDate[1]);
	Date.Year  = stoi(vDate[2]);

	return (Date);
}

string ReplaceWordInString(string str, string StringToReplace, string sReplace){
	
	size_t pos = str.find(StringToReplace);
	while (pos != std::string::npos)
	{
		str = str.replace(pos, StringToReplace.length(), sReplace);
		pos = str.find(StringToReplace);
	}

	return (str);
}

string FormatDate(sDate Date, string DateFormat = "dd/mm/yyy"){
	string FormattedDateString = "";

	FormattedDateString = ReplaceWordInString(DateFormat, "dd", to_string(Date.Day));
	FormattedDateString = ReplaceWordInString(FormattedDateString, "mm", to_string(Date.Month));
	FormattedDateString = ReplaceWordInString(FormattedDateString, "yyy", to_string(Date.Year));

	return (FormattedDateString);
}

int main(){
	string DateString = ReadStringDate("Please enter Date: dd/mm/yyy? ");

	sDate Date = StringToDate(DateString);

	cout << "\n" << FormatDate(Date) << "\n";
	cout << "\n" << FormatDate(Date, "yyy/dd/mm") << "\n";
	cout << "\n" << FormatDate(Date, "mm/dd/yyy") << "\n";
	cout << "\n" << FormatDate(Date, "mm-dd-yyy") << "\n";
	cout << "\n" << FormatDate(Date, "dd.mm.yyy") << "\n";
	cout << "\n" << FormatDate(Date, "Day: dd, Month: mm, Year: yyy") << endl;

	return (0);
}

