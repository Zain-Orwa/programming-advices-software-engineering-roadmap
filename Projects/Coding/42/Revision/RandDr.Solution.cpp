#include <iostream>
#include <cstdlib>
using namespace std;


int RandomNumber(int From, int To){
	
	int randNum = 0;

	randNum = rand() % (To - From + 1) + From;

	return (randNum);
}

enum	enCharType {SmallLetters= 1, CapitalLetters = 2, SpecialCharacter = 3, DigitNumber = 4};


char GetRandomCharacter(enCharType CharType){
	switch (CharType){
		case SmallLetters:
			return char(RandomNumber(97, 122));
		case CapitalLetters:
			return char(RandomNumber(65, 90));
		case SpecialCharacter:
			return char(RandomNumber(33, 47));
		case DigitNumber:
			return char(RandomNumber(48, 57));
		default:
			return '?';
	}
}

int main(){
	srand((unsigned)time(NULL));

	cout << "Small Letters    : " << GetRandomCharacter(SmallLetters) << endl;
	cout << "Capital Letters  : " << GetRandomCharacter(CapitalLetters) << endl;
	cout << "Special Character: " <<  GetRandomCharacter(SpecialCharacter) << endl;
	cout << "Digit Number     : " <<  GetRandomCharacter(DigitNumber) << endl;

	return (0);
}





