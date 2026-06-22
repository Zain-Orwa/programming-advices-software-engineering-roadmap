#include <iostream>

std::string TrimLeft(std::string str)
{
   for (size_t i = 0; i < str.length(); i++) 
   {
        if (str[i] != ' ')
        {
            return (str.substr(i, str.length() - i));
        }
   }
   return ("");
}

std::string TrimRight(std::string str)
{
    for (size_t i = str.length() - 1; i >= 0; i--)
    {
        if (str[i] != ' ')
            return (str.substr(0, i + 1));
    }
    return ("");
}


std::string TrimAll(std::string str)
{
    return (TrimLeft(TrimRight(str)));
}

int main(void)
{
    std::string str = "   Trim my string from left and right    ";

    std::cout << "\nTrimed left :" << TrimLeft(str) << std::endl;
    std::cout << "\nTrimed right:" << TrimRight(str) << std::endl;
    std::cout << "\nTrimed all  :" << TrimAll(str) << std::endl;

    return (0);
}