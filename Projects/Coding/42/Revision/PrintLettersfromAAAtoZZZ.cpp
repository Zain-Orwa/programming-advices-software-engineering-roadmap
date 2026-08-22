#include <iostream>

using namespace std;

void PrintWordsAAAtoZZZ(){

	string word = "";

	for (int i = 1; i <= 26; i++){
		for (int j = 1; j <= 26; j++){
			for (int k = 1; k <= 26; k++){
					word += char(i + 64);
					word += char(j + 64);
					word += char(k + 64);

					cout << word << endl;

					word = "";
			}
			cout << "____\n";
		}
	}
}



int main(){
	
	PrintWordsAAAtoZZZ();

	return (0);
}


