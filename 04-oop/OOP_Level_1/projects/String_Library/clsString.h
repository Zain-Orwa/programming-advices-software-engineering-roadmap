#pragma once

#include <iostream>
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
};






