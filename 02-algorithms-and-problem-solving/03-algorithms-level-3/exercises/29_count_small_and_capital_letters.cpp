#include <iostream>
#include <string>

std::string ReadString(void)
{
    std::string str;
    std::cout << "Please enter string:\n";
    std::getline(std::cin, str);
    return (str);
}

int CountSmallLetters(std::string str)
{
    int count;

    count = 0;
    for (size_t i = 0; i < str.length(); i++)
    {
        if (islower(str[i]))
            count++;
    }
    return (count);
}

int CountCapitalLetters(std::string str)
{
    int count;

    count = 0;
    for (size_t i = 0; i < str.length(); i++)
    {
        if (isupper(str[i]))
            count++;
    }
    return (count);
}

int main(void)
{
    std::string str = ReadString();

    std::cout << "\nString Length: " << str.length() << std::endl;
    std::cout << "Count Capital Letters: " << CountCapitalLetters(str);
    std::cout << "\nCount Small Letters: " << CountSmallLetters(str);

    return (0);
}