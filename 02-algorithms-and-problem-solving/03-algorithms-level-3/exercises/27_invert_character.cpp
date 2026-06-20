#include <iostream>

char ReadCharacter()
{
    char c;
    std::cout << "Please Enter a Character:\n";
    std::cin >> c;
    return (c);
}

char InvertCharacter(char c)
{
    return (isupper(c) ? tolower(c) : toupper(c));
}

int main(void)
{
    char c = ReadCharacter();

    std::cout << "\nCharacter after inverting case:\n";
    c = InvertCharacter(c);
    std::cout << c << std::endl;

    return (0);
}