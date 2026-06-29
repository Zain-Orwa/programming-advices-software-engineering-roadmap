#include <iostream>

char ReadCharacter()
{
    char c;
    std::cout << "Please Enter a Character:\n";
    std::cin >> c;
    return (c);
}
bool isVowel(char Ch1)
{
    Ch1 = tolower(Ch1);
    return (Ch1 == 'a' || Ch1 == 'e' || Ch1 == 'i' || Ch1 == 'o' || Ch1 == 'u');
}

int main(void)
{
    char Ch1 = ReadCharacter();

    if (isVowel(Ch1))
        std::cout << "\nYes, letter \'" << Ch1 << "\' is vowel!\n";
    else
        std::cout << "\nNO, letter \'" << Ch1 << "\' is vowel!\n";

    return (0);
}