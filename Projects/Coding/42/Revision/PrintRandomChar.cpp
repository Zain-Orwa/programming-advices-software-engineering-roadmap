#include <iostream>
#include <cstdlib>
using namespace std;

char RandomChar(int From, int To){
	int randChar = 0;

	randChar = rand() % (To - From + 1) + From;

	return char(randChar);
}

void PrintRandomChar(){

	cout << "Capital Letters   : " << RandomChar(65, 90) << endl;
	cout << "Small Letters     : " << RandomChar(97, 122) << endl;
	cout << "Special Characters: " << RandomChar(33, 47) << endl;
	cout << "Digit Numbers     : " << RandomChar(48, 57) << endl;
}

int main(){
	srand((unsigned)time(NULL));

	PrintRandomChar();

	return (0);
}

