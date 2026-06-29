#include <iostream>
#include <string>

std::string ReadString(void)
{
    std::string str;
    std::cout << "Please enter string:\n";
    std::getline(std::cin, str);
    return (str);
}

std::string LowerAllLetters(std::string str)
{
    bool isFirstLetter;

    isFirstLetter = true;
    for (size_t i = 0; i < str.length(); i++)
    {
        if (str[i] != ' ' && isFirstLetter)
            str[i] += 32;
        isFirstLetter = (str[i] == ' ' ? true : false);
    }
    return (str);
}

int main(void)
{
    std::string str = ReadString();
    std::cout << "\nString after conversion is:\n";
    str = LowerAllLetters(str);
    std::cout << str << std::endl;

    return (0);
}