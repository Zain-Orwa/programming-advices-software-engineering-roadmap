#include <iostream>
#include <string>

std::string ReadString(void)
{
    std::string str;
    std::cout << "Please enter string:\n";
    std::getline(std::cin, str);
    return (str);
}
char    InvertCharacter(char c)
{
    return (isupper(c) ? tolower(c) : toupper(c));
}

std::string InvertAllString(std::string str)
{
    for (size_t i = 0; i < str.length(); i++)
    {
        str[i] = InvertCharacter(str[i]);
    }
    return (str);
}

int main(void)
{
    std::string str = ReadString();
    std::cout << "\nString after inverting:\n";
    str = InvertAllString(str);
    std::cout << str << std::endl;

    return (0);
}