# clsString

A lightweight C++ string utility library that extends common `std::string` operations with reusable functions for analyzing, formatting, splitting, joining, trimming, replacing, and manipulating strings.

The library supports two ways of working:

- **Static functions** — operate directly on any supplied string.
- **Object functions** — operate on the string stored inside the object's `_Value`.

This allows `clsString` to work both as a string utility library and as a simple object-oriented wrapper around `std::string`.

---

# Project Information

```text
Project     : clsString
Language    : C++
Type        : Header-only String Utility Library
Created By  : Zain Orwa
Created On  : August 10, 2026
Time        : 15:03 CEST
Standard    : C++17
```

---

# Features

## Word Operations

- Count words in a string
- Print the first letter of every word
- Print each word on a separate line
- Reverse word order
- Replace specific words
- Split strings into `std::vector<std::string>`
- Join vectors or arrays of strings

## Letter Operations

- Convert the first letter of each word to uppercase
- Convert the first letter of each word to lowercase
- Convert the entire string to uppercase
- Convert the entire string to lowercase
- Invert the case of a character
- Invert the case of all characters
- Count capital letters
- Count lowercase letters
- Count specific letters
- Support case-sensitive and case-insensitive counting

## Vowel Operations

- Check whether a character is a vowel
- Count vowels
- Print all vowels

## String Cleaning

- Trim whitespace from the left
- Trim whitespace from the right
- Trim whitespace from both sides
- Remove punctuation

---

# Installation

`clsString` is implemented as a header-only library.

Add:

```cpp
clsString.h
```

to your project and include it:

```cpp
#include "clsString.h"
```

---

# Basic Usage

```cpp
#include <iostream>
#include "clsString.h"

int main()
{
    clsString MyString("Welcome to C++ Programming");

    std::cout << MyString.GetValue() << "\n";

    return 0;
}
```

Output:

```text
Welcome to C++ Programming
```

---

# Static vs Object Usage

Most operations can be used in two different ways.

## Static Version

The static version works directly with a string passed to the function.

```cpp
std::size_t Count =
    clsString::CountWords("Welcome to C++ Programming");

std::cout << Count << "\n";
```

Output:

```text
4
```

## Object Version

The object version works directly with the object's internal `_Value`.

```cpp
clsString MyString("Welcome to C++ Programming");

std::cout << MyString.CountWords() << "\n";
```

Output:

```text
4
```

The general design is:

```text
                clsString
                    │
          ┌─────────┴─────────┐
          │                   │
     Static Functions    Object Functions
          │                   │
          ▼                   ▼
   Supplied std::string      _Value
```

---

# Creating and Changing a String

Create an object:

```cpp
clsString MyString("Hello");
```

Read its value:

```cpp
std::cout << MyString.GetValue();
```

Change its value:

```cpp
MyString.SetValue("Hello World");
```

---

# Word Functions

## CountWords()

Counts the number of words inside a string.

```cpp
std::size_t Count =
    clsString::CountWords("Welcome to C++ Programming");

std::cout << Count;
```

Output:

```text
4
```

Object version:

```cpp
clsString MyString("Welcome to C++ Programming");

std::cout << MyString.CountWords();
```

---

## PrintFirstLetterOfEachWord()

Prints the first character of every word.

```cpp
clsString::PrintFirstLetterOfEachWord(
    "Welcome to C++ Programming"
);
```

Output:

```text
W
t
C
P
```

---

## PrintEachWord()

Prints every word on a separate line.

```cpp
clsString::PrintEachWord(
    "Welcome to C++ Programming"
);
```

Output:

```text
Welcome
to
C++
Programming
```

---

## ReverseWord()

Reverses the order of the words.

```cpp
std::string Result =
    clsString::ReverseWord(
        "Welcome to C++ Programming"
    );

std::cout << Result;
```

Output:

```text
Programming C++ to Welcome
```

Object version:

```cpp
clsString MyString("Welcome to C++ Programming");

MyString.ReverseWord();

std::cout << MyString.GetValue();
```

---

# Letter Case Functions

## UpperFirstLetterOfEachWord()

Converts the first letter of every word to uppercase.

```cpp
std::string Result =
    clsString::UpperFirstLetterOfEachWord(
        "welcome to cpp programming"
    );

std::cout << Result;
```

Output:

```text
Welcome To Cpp Programming
```

---

## LowerFirstLetterOfEachWord()

Converts the first letter of every word to lowercase.

```cpp
std::string Result =
    clsString::LowerFirstLetterOfEachWord(
        "Welcome To CPP Programming"
    );
```

---

## AllToUpper()

Converts the entire string to uppercase.

```cpp
std::string Result =
    clsString::AllToUpper("Hello World");

std::cout << Result;
```

Output:

```text
HELLO WORLD
```

Object version:

```cpp
clsString MyString("Hello World");

MyString.AllToUpper();

std::cout << MyString.GetValue();
```

---

## AllToLower()

Converts the entire string to lowercase.

```cpp
std::string Result =
    clsString::AllToLower("HELLO WORLD");

std::cout << Result;
```

Output:

```text
hello world
```

---

# Invert Letter Case

## InvertLetterCase()

Inverts the case of a single character.

```cpp
char Ch = clsString::InvertLetterCase('A');

std::cout << Ch;
```

Output:

```text
a
```

---

## InvertAllLettersCase()

Inverts the case of every character in the string.

```cpp
std::string Result =
    clsString::InvertAllLettersCase("Hello WORLD");

std::cout << Result;
```

Output:

```text
hELLO world
```

---

# Counting Letters

The library provides the following counting options:

```cpp
clsString::SmallLetters
clsString::CapitalLetters
clsString::All
```

Example:

```cpp
std::size_t Capitals =
    clsString::CountLetters(
        "Hello WORLD",
        clsString::CapitalLetters
    );

std::cout << Capitals;
```

You can also use:

```cpp
clsString::CountCapitalLetters(str);
clsString::CountSmallLetters(str);
```

---

# CountSpecificLetter()

Counts how many times a specific character appears.

```cpp
std::size_t Count =
    clsString::CountSpecificLetter(
        "Hello World",
        'l'
    );

std::cout << Count;
```

The function also supports case-insensitive matching.

```cpp
std::size_t Count =
    clsString::CountSpecificLetter(
        "Hello WORLD",
        'o',
        false
    );
```

`MatchCase` defaults to:

```cpp
true
```

---

# Vowels

## IsVowel()

Checks whether a character is a vowel.

```cpp
if (clsString::IsVowel('A'))
{
    std::cout << "Vowel";
}
```

---

## CountVowels()

Counts all vowels inside a string.

```cpp
std::size_t Count =
    clsString::CountVowels("Hello World");

std::cout << Count;
```

---

## PrintAllVowels()

Prints every vowel found in the string.

```cpp
clsString::PrintAllVowels("Hello World");
```

Output:

```text
e    o    o
```

---

# Split()

Splits a string using a specified delimiter.

The function returns:

```cpp
std::vector<std::string>
```

Example:

```cpp
std::vector<std::string> Languages =
    clsString::Split(
        "C++-Java-Python-Rust",
        "-"
    );
```

Print the resulting vector:

```cpp
for (const std::string& Language : Languages)
{
    std::cout << Language << "\n";
}
```

Output:

```text
C++
Java
Python
Rust
```

---

# JoinString()

`JoinString()` combines multiple strings using a delimiter.

Two overloads are available:

- `std::vector<std::string>`
- Array of `std::string`

## Vector Version

```cpp
std::vector<std::string> Languages =
{
    "C++",
    "Python",
    "Rust"
};

std::string Result =
    clsString::JoinString(
        Languages,
        " | "
    );

std::cout << Result;
```

Output:

```text
C++ | Python | Rust
```

---

## Array Version

```cpp
std::string Languages[] =
{
    "C++",
    "Python",
    "Rust"
};

std::string Result =
    clsString::JoinString(
        Languages,
        3,
        " - "
    );

std::cout << Result;
```

Output:

```text
C++ - Python - Rust
```

---

# Trim Functions

## TrimLeft()

Removes whitespace from the beginning of a string.

```cpp
std::string Result =
    clsString::TrimLeft("    Hello World");
```

Result:

```text
Hello World
```

---

## TrimRight()

Removes whitespace from the end of a string.

```cpp
std::string Result =
    clsString::TrimRight("Hello World    ");
```

Result:

```text
Hello World
```

---

## Trim()

Removes whitespace from both sides.

```cpp
std::string Result =
    clsString::Trim("    Hello World    ");
```

Result:

```text
Hello World
```

---

# ReplaceWord()

Replaces a specific word with another word.

```cpp
std::string Result =
    clsString::ReplaceWord(
        "I love C++",
        "C++",
        "Programming",
        true
    );

std::cout << Result;
```

Output:

```text
I love Programming
```

Case-insensitive matching is also supported:

```cpp
std::string Result =
    clsString::ReplaceWord(
        "I LOVE cpp",
        "CPP",
        "C++",
        false
    );
```

---

# RemoveStringPunctuation()

Removes punctuation characters from a string.

```cpp
std::string Result =
    clsString::RemoveStringPunctuation(
        "Hello, World! Welcome."
    );

std::cout << Result;
```

Output:

```text
Hello World Welcome
```

---

# API Overview

| Function                             | Purpose                                   |
| ------------------------------------ | ----------------------------------------- |
| 01. `CountWords()`                   | Counts words                              |
| 02. `PrintFirstLetterOfEachWord()`   | Prints the first letter of each word      |
| 03. `UpperFirstLetterOfEachWord()`   | Capitalizes the first letter of each word |
| 04. `LowerFirstLetterOfEachWord()`   | Lowercases the first letter of each word  |
| 05. `AllToUpper()`                   | Converts the string to uppercase          |
| 06. `AllToLower()`                   | Converts the string to lowercase          |
| 07. `InvertLetterCase()`             | Inverts one character's case              |
| 08. `InvertAllLettersCase()`         | Inverts all character cases               |
| 09. `CountLetters()`                 | Counts letters by type                    |
| 10. `CountCapitalLetters()`          | Counts uppercase letters                  |
| 11. `CountSmallLetters()`            | Counts lowercase letters                  |
| 12. `CountSpecificLetter()`          | Counts a specific character               |
| 13. `IsVowel()`                      | Checks whether a character is a vowel     |
| 14. `CountVowels()`                  | Counts vowels                             |
| 15. `PrintAllVowels()`               | Prints vowels                             |
| 16. `PrintEachWord()`                | Prints each word on a new line            |
| 17. `Split()`                        | Splits a string using a delimiter         |
| 18. `TrimLeft()`                     | Removes whitespace from the beginning     |
| 19. `TrimRight()`                    | Removes whitespace from the end           |
| 20. `Trim()`                         | Removes surrounding whitespace            |
| 21. `JoinString()`                   | Joins strings using a delimiter           |
| 22. `ReverseWord()`                  | Reverses word order                       |
| 23. `ReplaceWord()`                  | Replaces specific words                   |
| 24. `RemoveStringPunctuation()`      | Removes punctuation characters            |

---

# Standard Library Components Used

The library uses:

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <cstddef>
```

Standard-library names are explicitly qualified with `std::`.

Examples:

```cpp
std::string
std::vector
std::size_t
std::cout
std::isspace
std::tolower
std::toupper
std::ispunct
```

The library does not rely on:

```cpp
using namespace std;
```

This helps avoid namespace conflicts and makes it clear which names belong to the C++ Standard Library.

---

# Design Goals

The main goals of `clsString` are:

- Simple and readable code
- Reusable string operations
- Safe string processing
- Avoid unnecessary copies where possible
- Use appropriate types such as `std::size_t`
- Apply `const` correctness
- Support static and object-oriented usage
- Practice function overloading
- Practice standard-library containers
- Build a reusable C++ utility library

---

# Learning Purpose

`clsString` was created as a learning project to practice and understand:

- C++ classes and objects
- Encapsulation
- Static member functions
- Non-static member functions
- Function overloading
- `const` member functions
- Passing by reference
- `const` references
- `std::string`
- `std::vector`
- Character classification
- String manipulation
- Header files
- Reusable library design
- Basic performance considerations
- Safer C++ programming practices

---

# Requirements

Recommended compiler support:

```text
C++17 or newer
```

Example compilation:

```bash
g++ -std=c++17 -Wall -Wextra -Werror main.cpp -o program
```

---

# Author

**Created by Zain Orwa**

```text
Project : clsString
Author  : Zain Orwa
Date    : August 10, 2026
Time    : 15:03 CEST
```

Built as part of an ongoing journey to understand C++ and software engineering through practical implementation.

---

# License

This project is currently intended for learning and educational purposes.