#include <iostream>

using namespace std;

int ReadNumber(string Message){
	int Number = 0;

	cout << Message;
	cin >>Number;

	return (Number);
}

int ReverseNumber(int Number){
	int Remainder = 0;
	int Reversed = 0;
	
	while (Number != 0)
	{
		Remainder = Number % 10;
		Number = Number / 10;
		Reversed = Reversed * 10 + Remainder;
	}
	
	return (Reversed);
}

bool	isPalindrome(int Number){

	return (ReverseNumber(Number) == Number);
}

int main(){

	if (isPalindrome(ReverseNumber(ReadNumber("\nPlease Enter a Number: "))))
		cout << "\nThe Number Is Palindrome!" << endl;
	else
		cout << "\nThe Number Is Not Palindrome!" << endl;

	return (0);
}
