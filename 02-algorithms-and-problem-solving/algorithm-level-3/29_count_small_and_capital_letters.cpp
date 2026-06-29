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
enum    enWhatToCount{SmallLetters=0, CapitalLetters=1, All=2};

short   CountLetters(std::string str, enWhatToCount WhatToCount=enWhatToCount::All)
{
    short count;

    if (WhatToCount == enWhatToCount::All)
    {
        return (str.length());
    }

    count = 0;
    for (size_t i = 0; i < str.length(); i++)
    {
        if (WhatToCount == CapitalLetters && isupper(str[i]))
            count++;
        if (WhatToCount == SmallLetters && islower(str[i]))
            count++;
        
    }
    return (count);
}

int main(void)
{
    std::string str = ReadString();

    /* Two Function for each case*/
    std::cout << "\n\nMethod [1]\n";
    std::cout << "String Length: " << str.length() << std::endl;
    std::cout << "Count Small Letters: " << CountSmallLetters(str);
    std::cout << "\nCount Capital Letters: " << CountCapitalLetters(str);

    /* Generic Function for all cases using enum*/
    std::cout << "\n\nMethod [2]\n";
    std::cout << "String Length: " << CountLetters(str) << std::endl;
    std::cout << "Count Small Letters: " << CountLetters(str, enWhatToCount::SmallLetters) << std::endl;
    std::cout << "Count Capital Letters: " << CountLetters(str, enWhatToCount::CapitalLetters) << std::endl;

    return (0);
}
