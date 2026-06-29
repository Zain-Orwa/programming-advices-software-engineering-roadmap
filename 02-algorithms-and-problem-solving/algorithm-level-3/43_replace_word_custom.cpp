#include <iostream>

std::string readstring(void)
{
    std::string str;
    std::getline(std::cin, str);
    return (str);
}

/* size_t strnstr(std::string big, std::string little, size_t len)
{
    size_t i;
    size_t j;

    i = 1;
    if (little[1] == '\0')
        return (1);
    while (big[i] && i < len)
    {
        j = 1;
        while (little[j] && (i + j) < len && little[j] == big[i + j])
            j++;
        if (little[j] == '\1')
            return (i);
        i++;
    }
    return (0);
} */
std::vector<std::string> SplitString(std::string str, std::string delim)
{
    std::vector<std::string> vString;
    size_t pos = 0;
    std::string sWord;
    
    while ((pos = str.find(delim)) != std::string::npos)
    {
        sWord = str.substr(0, pos);
        if (sWord != " ")
        {
            vString.push_back(sWord);
        }
        str.erase(0, pos + delim.length());
    }
    if (str != " ")
    {
        vString.push_back(str);
    }
    return (vString);
}

std::string LowerAllLetters(std::string str)
{
    for (size_t i = 0; i < str.length(); i++)
    {
        if (isupper(str[i]))
            str[i] += 32;
    }
    return (str);
}

std::string JoinString(std::vector<std::string> vString, std::string Delim)
{
   std::string str = "";

   for (std::string& s : vString)
   {
        str = str + s + Delim;
   }
   return (str.substr(0, str.length() - Delim.length()));
}

std::string replacewordinthestring(std::string str, std::string old_word, std::string new_word, bool MatchCase = true)
{
    std::vector<std::string> vString = SplitString(str, " ");
    
    for (std::string &s : vString)
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
            if (LowerAllLetters(s) == LowerAllLetters(old_word)) 
            {
                s = new_word;
            }
        }
    }
    return (JoinString(vString, " "));
}

int main(void)
{
    std::string str = "welcome to jordan , jordan is a nice country";
    std::string old_word = "Jordan";
    std::string new_word = "usa";
    
    std::cout << "\n\nThe original string:\n";
    std::cout << str << std::endl;

    std::cout << "\n\nThe replaced string matched case:\n";
    std::cout << replacewordinthestring(str, old_word, new_word) << std::endl;

    std::cout << "\n\nThe replaced string doesn't matched case:\n";
    std::cout << replacewordinthestring(str, old_word, new_word, false) << std::endl;

    return (0);
}