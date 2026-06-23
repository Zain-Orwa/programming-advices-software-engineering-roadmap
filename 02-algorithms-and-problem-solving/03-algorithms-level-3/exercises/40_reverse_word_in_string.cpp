#include <iostream>

std::string ReadString(void)
{
    std::string str;
    std::cout << "Please enter string:\n";
    std::getline(std::cin, str);
    return (str);
}
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

std::string ReverseWordInString(std::string str)
{
    std::string str2= "";
    std::vector<std::string> vString ;
    vString = SplitString(str, " "); 
    
    //Declare iterator//
    std::vector<std::string>::iterator iter = vString.end();

    while (iter != vString.begin())
    {
        iter--;
        str2 += *iter + " ";
    }
    return (str2 = str2.substr(0, str2.length() - 1)); //remove the last space//
}

int main(void)
{
   std::string str = ReadString();

    std::cout << "\nString after reversing words:\n\n";
    std::cout << ReverseWordInString(str) << std::endl;

    return (0);
}