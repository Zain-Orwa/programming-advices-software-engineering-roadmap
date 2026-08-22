#include <iostream>
using namespace std;

int recursive_FebNumber(int Prev1, int Prev2){
	int FebNumber = 0;

	if (FebNumber == 55)
		return (0);

	return recursive_FebNumber(Prev1 + FebNumber, Prev2);
}

int main(){
	int Prev1 = 1;
	int Prev2 = 0;

	cout << "sum m to n = " << 	recursive_FebNumber(Prev1, Prev2) << endl;

	return (0);
}
