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
    for (size_t i = 0; i < str.length(); i++)
    {
        if (isupper(str[i]))
            str[i] += 32;
    }
    return (str);
}

std::string UpperAllLetters(std::string str)
{
    for (size_t i = 0; i < str.length(); i++)
    {
        if (islower(str[i]))
            str[i] -= 32;
    }
    return (str);
}

int main(void)
{
    std::string str = ReadString();

    str = LowerAllLetters(str);
    std::cout << "\nAll string to lower:\n";
    std::cout << str << std::endl;

    str = UpperAllLetters(str);
    std::cout << "\nAll string to upper:\n";
    std::cout << str << std::endl;

    return (0);
}