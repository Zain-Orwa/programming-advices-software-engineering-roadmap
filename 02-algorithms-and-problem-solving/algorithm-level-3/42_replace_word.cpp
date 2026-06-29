#include <iostream>

std::string ReadString(void)
{
    std::string str;
    std::getline(std::cin, str);
    return (str);
}

std::string ReplaceWordInTheString(std::string str, std::string old_word, std::string new_word)
{
    size_t  pos = str.find(old_word);

    while (pos != std::string::npos)
    {
        str = str.replace(pos, old_word.length(), new_word);
        pos = str.find(old_word);
    }
    return (str);
}

int main(void)
{
    std::cout << "Please enter string:\n";
    std::string str = ReadString();
    std::cout << "\nEnter word you want to replace:\n";
    std::string old_word = ReadString();
    std::cout << "\nEnter the new word:\n";
    std::string new_word = ReadString(); 
    
    std::cout << "\n\nThe replace string:\n";
    std::cout << ReplaceWordInTheString(str, old_word, new_word) << std::endl;

    return (0);
}