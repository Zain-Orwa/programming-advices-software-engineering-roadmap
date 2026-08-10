#include <iostream>
#include <vector>
#include <string>
#include "clsString.h"

int main()
{
    clsString str("Hello World From C++");

    std::cout << "Value: " << str.GetValue() << "\n";

    str.SetValue("Hello World From C++");
    std::cout << "After SetValue: " << str.GetValue() << "\n\n";


    // CountWords
    std::cout << "CountWords static: "
              << clsString::CountWords("Hello World From C++") << "\n";

    std::cout << "CountWords object: "
              << str.CountWords() << "\n\n";


    // PrintFirstLetterOfEachWord
    std::cout << "PrintFirstLetterOfEachWord static:\n";
    clsString::PrintFirstLetterOfEachWord("Hello World From C++");

    std::cout << "PrintFirstLetterOfEachWord object:\n";
    str.PrintFirstLetterOfEachWord();


    // UpperFirstLetterOfEachWord
    std::cout << "\nUpperFirstLetterOfEachWord static: "
              << clsString::UpperFirstLetterOfEachWord("hello world from c++") << "\n";

    str.SetValue("hello world from c++");
    str.UpperFirstLetterOfEachWord();

    std::cout << "UpperFirstLetterOfEachWord object: "
              << str.GetValue() << "\n\n";


    // LowerFirstLetterOfEachWord
    std::cout << "LowerFirstLetterOfEachWord static: "
              << clsString::LowerFirstLetterOfEachWord("Hello World From C++") << "\n";

    str.SetValue("Hello World From C++");
    str.LowerFirstLetterOfEachWord();

    std::cout << "LowerFirstLetterOfEachWord object: "
              << str.GetValue() << "\n\n";


    // AllToUpper
    std::cout << "AllToUpper static: "
              << clsString::AllToUpper("Hello World") << "\n";

    str.SetValue("Hello World");
    str.AllToUpper();

    std::cout << "AllToUpper object: "
              << str.GetValue() << "\n\n";


    // AllToLower
    std::cout << "AllToLower static: "
              << clsString::AllToLower("HELLO WORLD") << "\n";

    str.SetValue("HELLO WORLD");
    str.AllToLower();

    std::cout << "AllToLower object: "
              << str.GetValue() << "\n\n";


    // InvertLetterCase
    std::cout << "InvertLetterCase: "
              << clsString::InvertLetterCase('A') << "\n";


    // InvertAllLettersCase
    std::cout << "InvertAllLettersCase static: "
              << clsString::InvertAllLettersCase("Hello WORLD") << "\n";

    str.SetValue("Hello WORLD");
    str.InvertAllLettersCase();

    std::cout << "InvertAllLettersCase object: "
              << str.GetValue() << "\n\n";


    // CountLetters
    str.SetValue("Hello WORLD");

    std::cout << "CountLetters static: "
              << clsString::CountLetters(
                     "Hello WORLD",
                     clsString::CapitalLetters)
              << "\n";

    std::cout << "CountLetters object: "
              << str.CountLetters(clsString::CapitalLetters)
              << "\n";


    // CountCapitalLetters
    std::cout << "CountCapitalLetters static: "
              << clsString::CountCapitalLetters("Hello WORLD")
              << "\n";

    std::cout << "CountCapitalLetters object: "
              << str.CountCapitalLetters()
              << "\n";


    // CountSmallLetters
    std::cout << "CountSmallLetters static: "
              << clsString::CountSmallLetters("Hello WORLD")
              << "\n";

    std::cout << "CountSmallLetters object: "
              << str.CountSmallLetters()
              << "\n\n";


    // CountSpecificLetter
    std::cout << "CountSpecificLetter static: "
              << clsString::CountSpecificLetter("Hello World", 'l')
              << "\n";

    str.SetValue("Hello World");

    std::cout << "CountSpecificLetter object: "
              << str.CountSpecificLetter('l')
              << "\n\n";


    // IsVowel
    std::cout << "IsVowel('A'): "
              << clsString::IsVowel('A')
              << "\n";


    // CountVowels
    std::cout << "CountVowels static: "
              << clsString::CountVowels("Hello World")
              << "\n";

    str.SetValue("Hello World");

    std::cout << "CountVowels object: "
              << str.CountVowels()
              << "\n\n";


    // PrintAllVowels
    std::cout << "PrintAllVowels static: ";
    clsString::PrintAllVowels("Hello World");

    std::cout << "PrintAllVowels object: ";
    str.PrintAllVowels();


    // PrintEachWord
    std::cout << "\nPrintEachWord static:\n";
    clsString::PrintEachWord("Hello World From C++");

    str.SetValue("Hello World From C++");

    std::cout << "PrintEachWord object:\n";
    str.PrintEachWord();


    // Split
    std::vector<std::string> words =
        clsString::Split("C++-Java-Python", "-");

    std::cout << "\nSplit static:\n";

    for (const std::string& word : words)
        std::cout << word << "\n";


    str.SetValue("C++-Java-Python");

    words = str.Split("-");

    std::cout << "Split object:\n";

    for (const std::string& word : words)
        std::cout << word << "\n";


    // TrimLeft
    std::cout << "\nTrimLeft static: ["
              << clsString::TrimLeft("   Hello   ")
              << "]\n";


    // TrimRight
    std::cout << "TrimRight static: ["
              << clsString::TrimRight("   Hello   ")
              << "]\n";


    // Trim
    std::cout << "Trim static: ["
              << clsString::Trim("   Hello   ")
              << "]\n";


    str.SetValue("   Hello   ");

    std::cout << "TrimLeft object: ["
              << str.TrimLeft()
              << "]\n";

    std::cout << "TrimRight object: ["
              << str.TrimRight()
              << "]\n";

    std::cout << "Trim object: ["
              << str.Trim()
              << "]\n\n";


    // JoinString vector
    std::vector<std::string> languages =
    {
        "C++",
        "Python",
        "Rust"
    };

    std::cout << "JoinString vector: "
              << clsString::JoinString(languages, " | ")
              << "\n";


    // JoinString array
    std::string arr[] =
    {
        "C++",
        "Python",
        "Rust"
    };

    std::cout << "JoinString array: "
              << clsString::JoinString(arr, 3, " - ")
              << "\n\n";


    // ReverseWord
    std::cout << "ReverseWord static: "
              << clsString::ReverseWord("Hello World From C++")
              << "\n";

    str.SetValue("Hello World From C++");
    str.ReverseWord();

    std::cout << "ReverseWord object: "
              << str.GetValue()
              << "\n\n";


    // ReplaceWord
    std::cout << "ReplaceWord static: "
              << clsString::ReplaceWord(
                     "I love C++",
                     "C++",
                     "Programming",
                     true)
              << "\n";

    str.SetValue("I love C++");
    str.ReplaceWord("C++", "Programming");

    std::cout << "ReplaceWord object: "
              << str.GetValue()
              << "\n\n";


    // RemoveStringPunctuation
    std::cout << "RemoveStringPunctuation static: "
              << clsString::RemoveStringPunctuation("Hello, World!")
              << "\n";

    str.SetValue("Hello, World!");
    str.RemoveStringPunctuation();

    std::cout << "RemoveStringPunctuation object: "
              << str.GetValue()
              << "\n";


    return 0;
}
