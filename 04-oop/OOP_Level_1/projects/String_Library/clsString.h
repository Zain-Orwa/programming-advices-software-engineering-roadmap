#pragma once

#include <iostream>
#include <vector>

using namespace std;

class clsString
{
private:
    string  _Value;

public:
    clsString()
    {
        _Value = "";
    }

    clsString(string Value)
    {
        _Value = Value;
    }

    void    SetValue(string Value)
    {
        _Value = Value;
    }

    string  GetValue()
    {
        return (_Value);
    }

    static size_t CountWords(const std::string& str)
    {
        size_t counter = 0;
        size_t i = 0;

        while (i < str.length())
        {
            // Skip spaces
            while (i < str.length() && isspace(static_cast<unsigned char>(str[i])))
                i++;

            // If we found a non-space character,
            // then we found the beginning of a word.
            if (i < str.length())
                counter++;

            // Skip the current word
            while (i < str.length() && !isspace(static_cast<unsigned char>(str[i])))
                i++;
        }

        return counter;
    }

    size_t  CountWords()
    {
        return (CountWords(_Value));
    }

    static void PrintFirstLetterOfEachWord(const std::string& str)
    {
        bool isFirstLetter = true;

        for (size_t i = 0; i < str.length(); i++)
        {
            if (str[i] != ' ' && isFirstLetter)
                std::cout << str[i] << std::endl;

            isFirstLetter = (str[i] == ' ');
        }
    }

    void PrintFirstLetterOfEachWord(void)
    {
        PrintFirstLetterOfEachWord(_Value);
    }
   
    static string    UpperFirstLetterOfEachWord(std::string str)
    {
        bool    isFirstLetter;

        isFirstLetter = true;
        for (size_t i = 0; i < str.length(); i++)
        {
            if (str[i] != ' ' && isFirstLetter)
                str[i] -= 32;
            isFirstLetter = (str[i] == ' ' ? true : false);
        }
        return (str);
    }

    void    UpperFirstLetterOfEachWord()
    {
        _Value = UpperFirstLetterOfEachWord(_Value);
    }

    static string    LowerFirstLetterOfEachWord(std::string str)
    {
        bool    isFirstLetter;

        isFirstLetter = true;
        for (size_t i = 0; i < str.length(); i++)
        {
            if (str[i] != ' ' && isFirstLetter)
                str[i] += 32;
            isFirstLetter = (str[i] == ' ' ? true : false);
        }
        return (str);
    }

    void    LowerFirstLetterOfEachWord()
    {
        _Value = LowerFirstLetterOfEachWord(_Value);
    }

    static string AllToUpper(std::string str)
    {
        for (size_t i = 0; i < str.length(); i++)
        {
            if (islower(str[i]))
                str[i] -= 32;
        }
        return (str);
    }

    void    AllToUpper()
    {
        _Value = AllToUpper(_Value);
    }

    static string AllToLower(std::string str)
    {
        for (size_t i = 0; i < str.length(); i++)
        {
            if (isupper(str[i]))
                str[i] += 32;
        }
        return (str);
    }

    void    AllToLower()
    {
        _Value = AllToLower(_Value);
    }

















};






