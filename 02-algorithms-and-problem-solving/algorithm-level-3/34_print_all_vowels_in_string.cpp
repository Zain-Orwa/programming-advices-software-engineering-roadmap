#include <iostream>
#include <string>

std::string ReadString(void)
{
    std::string str;
    std::cout << "Please enter string:\n";
    std::getline(std::cin, str);
    return (str);
}

bool isVowel(char Ch1)
{
    Ch1 = tolower(Ch1);
    return (Ch1 == 'a' || Ch1 == 'e' || Ch1 == 'i' || Ch1 == 'o' || Ch1 == 'u');
}

void PrintAllVowelsInString(std::string str)
{
    for (size_t i = 0; i < str.length(); i++)
    {
        if (isVowel(str[i]))
            std::cout << str[i] << "    ";
    }
    std::cout << "\n";
}

int main(void)
{
    std::string str = ReadString();

    std::cout << "\nAll vowels in the string are:\n";
    PrintAllVowelsInString(str);

    return (0);
}