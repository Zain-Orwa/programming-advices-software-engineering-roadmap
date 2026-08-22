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

void PrintNumbersPattern(int Number){
	
	for (int i = 1; i <= Number; i++){
		for (int j = 1; j <= i; j++){
				
			cout << i;
		}
		cout << "\n";
	}
}

int main(){
	PrintNumbersPattern(ReadPositiveNumber("Please Enter a Positive Number: "));

	return (0);
}





