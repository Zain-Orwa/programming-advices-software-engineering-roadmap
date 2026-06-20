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

int CountAllVowelsInString(std::string str)
{
    int Counter;

    Counter = 0;
    for (size_t i = 0; i < str.length(); i++)
    {
        if (isVowel(str[i]))
            Counter++;
    }
    return (Counter);
}

int main(void)
{
    std::string str = ReadString();

    std::cout << "\nNumber of vowels is:  " << CountAllVowelsInString(str) << std::endl;

    return (0);
}