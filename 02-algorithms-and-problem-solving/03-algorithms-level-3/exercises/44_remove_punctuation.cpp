#include <iostream>

std::string RemoveStringPunctuation(std::string str)
{
    std::string str_2 = "";

    for (size_t i = 0; i < str.length(); i++)
    {
        if (!ispunct(str[i]))
        {
            str_2 += str[i];
        }
    }
    return (str_2);
}

int main(void)
{
    std::string str = "Welcome: to, Jordan , Jordan, is a nice, country";
    std::cout << "Original punctuation string:\n"; 
    std::cout << str << std::endl;

    std::cout << "\nRemoved punctuation string:\n";
    std::cout << RemoveStringPunctuation(str) << std::endl;

    return (0);
}
