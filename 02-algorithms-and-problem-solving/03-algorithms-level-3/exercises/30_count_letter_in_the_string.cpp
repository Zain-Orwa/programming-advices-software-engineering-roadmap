#include <iostream>
#include <string>

std::string ReadString(void)
{
    std::string str;
    std::cout << "please enter string:\n";
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

int CountLetterInString(std::string str, char Letter)
{
    short Counter;

    Counter = 0;
    for (size_t i = 0; i < str.length(); i++)
    {
        if (str[i] == Letter)
            Counter++;
    }
    return (Counter);
}

int main(void)
{
    std::string str = ReadString();
    char Char1 = ReadCharacter();

    std::cout << "Character '" << Char1 << "' Counted: " << CountLetterInString(str, Char1) << std::endl;

    return (0);
}
