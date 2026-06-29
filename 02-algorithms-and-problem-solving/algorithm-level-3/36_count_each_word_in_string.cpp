#include <iostream>
#include <string>

using namespace std;

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
size_t CountWordsInTheString(std::string str)
{
    size_t counter = 0;
    size_t i = 0;

    while (i < str.length())
    {
        while (i < str.length() && isspace(str[i]))
            i++;

        if (i < str.length())
            counter++;

        while (i < str.length() && !isspace(str[i]))
            i++;
    }

    return counter;
}
short CountWords(string S1)
{
    string delim = " "; // delimiter
    short Counter = 0;
    size_t pos = 0;
    string sWord; // define a string variable
    // use find() function to get the position of the delimiters
    while ((pos = S1.find(delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos);
        if (sWord != " ")
        {
            Counter++;
        }
        S1.erase(0, pos + delim.length());
    }
    if (S1 != " ")
    {
        Counter++;
    }
    return Counter;
}

int main(void)
{
    std::string str = ReadString();
    std::cout << "\nMy Word Coutner = " << CountWordsInTheString(str) << std::endl;

    std::cout << "\nDr. Words Counter = " << CountWords(str) << std::endl;

    return (0);
}
