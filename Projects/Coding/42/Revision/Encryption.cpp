#include <iostream>
#include <string>

using namespace std;

string ReadText(){

	string Text = "";

	cout << "Please Enter a Text: ";
	getline(cin, Text);

	return (Text);
}

string EncryptText(string Text, short EncryptionKey){
	
	for (size_t i = 0; i < Text.length(); i++)
		Text[i] = Text[i] + EncryptionKey;

	return (Text);
}

string DecryptText(string Text, short EncryptionKey){

	for (size_t i = 0; i < Text.length(); i++)
		Text[i] = Text[i] - EncryptionKey;

	return (Text);
}

int main(){
	
	short EncryptionKey = 2;

	string Text = ReadText();
	string TextEncryption = EncryptText(Text, EncryptionKey);
	string TextDecryption = DecryptText(TextEncryption, EncryptionKey);
	
	cout << "Text Before Encyption : " << Text << endl;
	cout << "Text After Encyption  : " << TextEncryption << endl;
	cout << "Text After Decryption : " << TextDecryption << endl;
	
	return (0);
}

