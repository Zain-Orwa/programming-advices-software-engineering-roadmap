#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void	PrintFileContent(string FileName){
	fstream MyFile;
	MyFile.open(FileName, ios::in);
	if (MyFile.is_open())
	{
		string Line = "";
		while (getline(MyFile, Line))
		{
			cout << Line << endl;
		}
		MyFile.close();
	}
}


int main(){
	PrintFileContent("file.txt");

	return (0);
}
