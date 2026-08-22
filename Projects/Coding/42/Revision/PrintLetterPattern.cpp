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

void PrintPatternLetters(int Number){
	for (int i = 1; i <= Number; i++){
		for (int j = 1; j <= i; j++){
			cout << char(i + 64);
		}
		cout << "\n";
	}
}

int main(){
	PrintPatternLetters(ReadPositiveNumber("Please Enter a Positive Number: "));

	return (0);
}

