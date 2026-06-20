#include <iostream>
#include <string>

std::string ReadString(void)
{
    std::string str;
    std::cout << "\nPlease Enter Your String:\n";
    std::getline(std::cin, str);
    return (str);
}
char    ReadCharacter()
{
    char c;
    std::cout << "Please Enter a Character:\n";
    std::cin >> c;
    return (c);
}

int CountLetterInString(std::string str, char Letter, bool MatchCase=true)
{
    short Counter;

    Counter = 0;
    for (size_t i = 0; i < str.length(); i++)
    {
        if (MatchCase)
        {
            if (str[i] == Letter)
                Counter++;
        }
        else
        {
            if (toupper(str[i]) == toupper(Letter))
                Counter++;
        }
    }
    return (Counter);
}
char    InvertCharacter(char c)
{
    return (isupper(c) ? tolower(c) : toupper(c));
}

int main(void)
{
    std::string str = ReadString();
    char Ch1 = ReadCharacter();

    std::cout << "\nCase sensetive:\n";
    std::cout << "Letter \'" << Ch1 << "\' Count = " << CountLetterInString(str, Ch1) << std::endl;


    std::cout << "\nCase insensetive:\n";
    std::cout << "Letter \'" << Ch1 << "\' Or \'" << InvertCharacter(Ch1) << "\' ";
    std::cout << CountLetterInString(str, Ch1, false) << std::endl; 

    return (0);
}
