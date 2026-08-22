#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

void	SaveVectorToFile(string FileName, vector<string> vFileContent){
	fstream MyFile;
	MyFile.open(FileName, ios::out);
	if (MyFile.is_open())
	{
		for (string &Line : vFileContent)
		{
			if (!Line.empty())
			{
				MyFile << Line << endl;
			}
		}
		MyFile.close();
	}

}

int main(){
	vector<string> vFileContent = {"Ali", "Fadi", "Maher", "Lama", "Shadi"};

	SaveVectorToFile("Filecom.txt", vFileContent);

	return (0);
}

