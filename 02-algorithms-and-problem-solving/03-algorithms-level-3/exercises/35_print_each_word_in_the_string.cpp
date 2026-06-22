#include <iostream>
#include <string>

std::string ReadString(void)
{
    std::string str;
    std::cout << "Please enter string:\n";
    std::getline(std::cin, str);
    return (str);
}
/* void    PrintEachWordInString(std::string str)
{
    size_t  i;

    for (i = 1; i < str.length(); i++)
    {
        if (str[i] != ' ')
            std::cout << str[i];
        if (str[i] == ' ' && isalpha(str[i - 2]))
            std::cout << "\n";
    }
} */
void    PrintEachWordInString(std::string str)
{
    std::string delim = " ";
    std::string sWord;
    size_t pos = 0;

    while ((pos = str.find(delim)) != std::string::npos)
    {
        sWord = str.substr(0, pos);
        if (sWord != " ")
        {
            std::cout << sWord << std::endl;
        }
        str.erase(0, pos + delim.length());
    }
    if (str != " ")
    {
        std::cout << str << std::endl;
    }
}

int main(void)
{
    PrintEachWordInString(ReadString());

    return (0);
}






