#include <iostream>
#include <string>

std::string ReadString(void)
{
    std::string str;
    
    std::cout << "Please Enter Your String:\n";
    getline(std::cin, str);
    return (str);
}

void    PrintFirstLetterOfEachWord(std::string str)
{
    bool isFirstLetter;

    isFirstLetter = true;
    for (size_t i = 0; i < str.length(); i++)
    {
        if (str[i] != ' ' && isFirstLetter)
            std::cout << str[i] << std::endl;
        isFirstLetter = (str[i] == ' ' ? true : false);
    }
}

int main(void)
{
    std::string str = ReadString();

    std::cout << "The first letter of each word is:\n";
    PrintFirstLetterOfEachWord(str);

    return (0);
}