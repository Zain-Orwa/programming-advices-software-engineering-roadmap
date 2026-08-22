#include <iostream>
#include <string>

using namespace std;

string ReadPassword(){
	string Password = "";

	cout << "Please Enter Password From 3 Capital Letters: ";
	cin >> Password;

	return (Password);
}


bool GuessPassword(string Password){
	string word = "";
	int Counter = 0;

	for (int i = 65; i <= 90; i++){
		for (int j = 65; j <= 90; j++){
			for (int k = 65; k <= 90; k++){

					Counter++;

					word += i;
					word += j;
					word += k;

					cout << "Trail [" << Counter << "]: " << word << endl; 

					if (word == Password)
					{
						cout << "\nPassword Is: " << word << endl;
						cout << "Found at Iteration:[" << Counter << "]" << endl;
						return (true);
					}
					word = "";
			}
			cout << "\n__________________\n";
		}
	}
	return (false);
}

int main(){

	GuessPassword(ReadPassword());

	return (0);
}

