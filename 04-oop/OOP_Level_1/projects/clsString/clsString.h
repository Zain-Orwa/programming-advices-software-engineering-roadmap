#pragma once

#include <iostream>
#include <cstddef>
#include <vector>
#include <string>
#include <cctype>

class clsString
{
private:
    std::string  _Value;

public:
    clsString()
    {
        _Value = "";
    }

    clsString(const std::string& Value)
        : _Value(Value)
    {
    }

    void    SetValue(const std::string& Value)
    {
        _Value = Value;
    }

    const std::string&  GetValue() const
    {
        return (_Value);
    }

    static std::size_t CountWords(const std::string& str)
    {
        std::size_t counter = 0;
        std::size_t i = 0;

        while (i < str.length())
        {
            // Skip spaces
            while (i < str.length() && std::isspace(static_cast<unsigned char>(str[i])))
                i++;

            // If we found a non-space character,
            // then we found the beginning of a word.
            if (i < str.length())
                counter++;

            // Skip the current word
            while (i < str.length() && !std::isspace(static_cast<unsigned char>(str[i])))
                i++;
        }

        return counter;
    }

    std::size_t  CountWords() const
    {
        return (CountWords(_Value));
    }

    static void PrintFirstLetterOfEachWord(const std::string& str)
    {
        bool isFirstLetter = true;

        for (std::size_t i = 0; i < str.length(); i++)
        {
            if (!std::isspace(static_cast<unsigned char>(str[i])) && isFirstLetter)
                std::cout << str[i] << "\n";

            isFirstLetter = std::isspace(static_cast<unsigned char>(str[i]));
        }
    }

    void PrintFirstLetterOfEachWord(void) const
    {
        PrintFirstLetterOfEachWord(_Value);
    }

    static std::string    UpperFirstLetterOfEachWord(std::string str)
    {
        bool    isFirstLetter;

        isFirstLetter = true;
        for (std::size_t i = 0; i < str.length(); i++)
        {
            if (!std::isspace(static_cast<unsigned char>(str[i])) && isFirstLetter)
                str[i] = static_cast<char>(std::toupper(static_cast<unsigned char>(str[i])));

            isFirstLetter = std::isspace(static_cast<unsigned char>(str[i]));
        }
        return (str);
    }

    void    UpperFirstLetterOfEachWord()
    {
        _Value = UpperFirstLetterOfEachWord(_Value);
    }

    static std::string    LowerFirstLetterOfEachWord(std::string str)
    {
        bool    isFirstLetter;

        isFirstLetter = true;
        for (std::size_t i = 0; i < str.length(); i++)
        {
            if (!std::isspace(static_cast<unsigned char>(str[i])) && isFirstLetter)
                str[i] = static_cast<char>(std::tolower(static_cast<unsigned char>(str[i])));

            isFirstLetter = std::isspace(static_cast<unsigned char>(str[i]));
        }
        return (str);
    }

    void    LowerFirstLetterOfEachWord()
    {
        _Value = LowerFirstLetterOfEachWord(_Value);
    }

    static std::string AllToUpper(std::string str)
    {
        for (std::size_t i = 0; i < str.length(); i++)
        {
            str[i] = static_cast<char>(std::toupper(static_cast<unsigned char>(str[i])));
        }
        return (str);
    }

    void    AllToUpper()
    {
        _Value = AllToUpper(_Value);
    }

    static std::string AllToLower(std::string str)
    {
        for (std::size_t i = 0; i < str.length(); i++)
        {
            str[i] = static_cast<char>(std::tolower(static_cast<unsigned char>(str[i])));
        }
        return (str);
    }

    void    AllToLower()
    {
        _Value = AllToLower(_Value);
    }

    static char InvertLetterCase(char c)
    {
        unsigned char Ch = static_cast<unsigned char>(c);

        return (std::isupper(Ch) ? static_cast<char>(std::tolower(Ch)) : static_cast<char>(std::toupper(Ch)));
    } 

    static std::string InvertAllLettersCase(std::string str)
    {
        for (std::size_t i = 0; i < str.length(); i++)
        {
            str[i] = InvertLetterCase(str[i]);
        }
        return (str);
    }

    void    InvertAllLettersCase(void)
    {
        _Value = InvertAllLettersCase(_Value);
    }

    enum    enWhatToCount{SmallLetters=0, CapitalLetters=1, All=2};

    static std::size_t   CountLetters(const std::string& str, enWhatToCount WhatToCount=enWhatToCount::All)
    {
        std::size_t count;

        if (WhatToCount == enWhatToCount::All)
        {
            return (str.length());
        }

        count = 0;
        for (std::size_t i = 0; i < str.length(); i++)
        {
            if (WhatToCount == CapitalLetters && std::isupper(static_cast<unsigned char>(str[i])))
                count++;
            if (WhatToCount == SmallLetters && std::islower(static_cast<unsigned char>(str[i])))
                count++;

        }
        return (count);
    }

    std::size_t   CountLetters(enWhatToCount WhatToCount=enWhatToCount::All) const
    {
        return (CountLetters(_Value, WhatToCount));
    }

    static std::size_t CountCapitalLetters(const std::string& str)
    {
        std::size_t count;

        count = 0;
        for (std::size_t i = 0; i < str.length(); i++)
        {
            if (std::isupper(static_cast<unsigned char>(str[i])))
                count++;
        }
        return (count);
    }

    std::size_t    CountCapitalLetters() const
    {
        return (CountCapitalLetters(_Value));
    }

    static std::size_t CountSmallLetters(const std::string& str)
    {
        std::size_t count;

        count = 0;
        for (std::size_t i = 0; i < str.length(); i++)
        {
            if (std::islower(static_cast<unsigned char>(str[i])))
                count++;
        }
        return (count);
    }

    std::size_t    CountSmallLetters() const
    {
        return (CountSmallLetters(_Value));
    }

    static std::size_t  CountSpecificLetter(const std::string& str, char Letter, bool MatchCase = true)
    {

        std::size_t Counter = 0;

        for (std::size_t i = 0; i < str.length(); i++)
        {

            if (MatchCase)
            {
                if (str[i] == Letter)
                    Counter++;
            }
            else
            {
                if (std::tolower(static_cast<unsigned char>(str[i])) ==
                    std::tolower(static_cast<unsigned char>(Letter)))
                    Counter++;
            }

        }

        return Counter;
    }

    std::size_t  CountSpecificLetter(char Letter, bool MatchCase = true) const
    {
        return CountSpecificLetter(_Value, Letter, MatchCase);
    }

    static bool IsVowel(char Ch1)
    {
        Ch1 = static_cast<char>(std::tolower(static_cast<unsigned char>(Ch1)));

        return ((Ch1 == 'a') || (Ch1 == 'e') || (Ch1 == 'i') || (Ch1 == 'o') || (Ch1 == 'u'));
    }

    static std::size_t  CountVowels(const std::string& str)
    {

        std::size_t Counter = 0;

        for (std::size_t i = 0; i < str.length(); i++)
        {

            if (IsVowel(str[i]))
                Counter++;

        }

        return Counter;
    }

    std::size_t  CountVowels() const
    {
        return CountVowels(_Value);
    }

    static void PrintAllVowels(const std::string& str)
    {
        for (std::size_t i = 0; i < str.length(); i++)
        {
            if (IsVowel(str[i]))
                std::cout << str[i] << "    ";
        }
        std::cout << "\n";
    }

    void PrintAllVowels() const
    {
        PrintAllVowels(_Value);
    }

    static void    PrintEachWord(const std::string& str)
    {
        bool IsInsideWord;

        IsInsideWord = false;

        for (std::size_t i = 0; i < str.length(); i++)
        {
            if (!std::isspace(static_cast<unsigned char>(str[i])))
            {
                std::cout << str[i];
                IsInsideWord = true;
            }
            else if (IsInsideWord)
            {
                std::cout << "\n";
                IsInsideWord = false;
            }
        }

        if (IsInsideWord)
            std::cout << "\n";
    }

    void    PrintEachWord() const
    {
        PrintEachWord(_Value);
    }

    static std::vector<std::string> Split(const std::string& str, const std::string& Delim)
    {
        std::vector<std::string> vString;

        std::size_t pos = 0;
        std::size_t Start = 0;

        if (Delim.empty())
        {
            if (!str.empty())
                vString.push_back(str);

            return vString;
        }

        while ((pos = str.find(Delim, Start)) != std::string::npos)
        {
            if (pos > Start)
            {
                vString.emplace_back(str, Start, pos - Start);
            }

            Start = pos + Delim.length();
        }

        if (Start < str.length())
        {
            vString.emplace_back(str, Start);
        }

        return vString;
    }

    std::vector<std::string> Split(const std::string& Delim) const
    {
        return Split(_Value, Delim);
    }

    static std::string TrimLeft(const std::string& str)
    {
        for (std::size_t i = 0; i < str.length(); i++)
        {
            if (!std::isspace(static_cast<unsigned char>(str[i])))
            {
                return (str.substr(i, str.length() - i));
            }
        }
        return ("");
    }

    std::string TrimLeft() const
    {
        return (TrimLeft(_Value));
    }

    static std::string TrimRight(const std::string& str)
    {
        for (std::size_t i = str.length(); i > 0; i--)
        {
            if (!std::isspace(static_cast<unsigned char>(str[i - 1])))
                return (str.substr(0, i));
        }
        return ("");
    }

    std::string TrimRight() const
    {
        return (TrimRight(_Value));
    }

    static std::string Trim(const std::string& str)
    {
        std::size_t Start;
        std::size_t End;

        Start = 0;
        while (Start < str.length() && std::isspace(static_cast<unsigned char>(str[Start])))
            Start++;

        if (Start == str.length())
            return ("");

        End = str.length();
        while (End > Start && std::isspace(static_cast<unsigned char>(str[End - 1])))
            End--;

        return (str.substr(Start, End - Start));
    }

    std::string Trim() const
    {
        return (Trim(_Value));
    }
    
    static std::string JoinString(const std::vector<std::string>& vString, const std::string& Delim)
    {
        std::string str = "";

        for (std::size_t i = 0; i < vString.size(); i++)
        {
            str += vString[i];

            if (i < vString.size() - 1)
                str += Delim;
        }

        return (str);
    }

    static std::string JoinString(const std::string arr_str[], std::size_t size, const std::string& Delim)
    {
        std::string str = "";

        for (std::size_t i = 0; i < size; i++)
        {
            str += arr_str[i];

            if (i < size - 1)
                str += Delim;
        }

        return (str);
    }

    static std::string ReverseWord(const std::string& str)
    {
        std::string str2 = "";
        std::vector<std::string> vString;

        vString = Split(str, " ");

        for (std::size_t i = vString.size(); i > 0; i--)
        {
            str2 += vString[i - 1];

            if (i > 1)
                str2 += " ";
        }

        return (str2);
    }

    void ReverseWord()
    {
        _Value = ReverseWord(_Value);
    }

    static std::string ReplaceWord(const std::string& str, const std::string& old_word,
    const std::string& new_word, bool MatchCase = true)
    {
        std::vector<std::string> vString = Split(str, " ");
        std::string LowerOldWord;

        if (!MatchCase)
            LowerOldWord = AllToLower(old_word);

        for (std::string& s : vString)
        {
            if (MatchCase)
            {
                if (s == old_word)
                {
                    s = new_word;
                }
            }
            else
            {
                if (AllToLower(s) == LowerOldWord)
                {
                    s = new_word;
                }
            }
        }

        return (JoinString(vString, " "));
    }

    void ReplaceWord(const std::string& old_word, const std::string& new_word,
        bool MatchCase = true)
    {
        _Value = ReplaceWord(_Value, old_word, new_word, MatchCase);
    }

    static std::string RemoveStringPunctuation(const std::string& str)
    {
        std::string str_2 = "";

        for (std::size_t i = 0; i < str.length(); i++)
        {
            if (!std::ispunct(static_cast<unsigned char>(str[i])))
            {
                str_2 += str[i];
            }
        }

        return (str_2);
    }

    void RemoveStringPunctuation()
    {
        _Value = RemoveStringPunctuation(_Value);
    }

};