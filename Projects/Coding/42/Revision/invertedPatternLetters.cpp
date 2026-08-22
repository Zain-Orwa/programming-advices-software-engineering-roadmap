#include <iostream>

using namespace std;


int ReadPositiveNumber(string Message){

	int Number = 0;

	do{
			cout << Message;
			cin >> Number;
	} while (Number < 1);
	
	return (Number);
}

void PrintInversPatternLetters(int Number){
	
	for (int i = Number; i >= 1; i--){
		for (int j = i; j >= 1; j--){
				cout << char(i + 64);
		}
		cout << "\n";
	}
}

int main(){
	PrintInversPatternLetters(ReadPositiveNumber("Please Enter a Positive Number: "));

	return (0);
}



