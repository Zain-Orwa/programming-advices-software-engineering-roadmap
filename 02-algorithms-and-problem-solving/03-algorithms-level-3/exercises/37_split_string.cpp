#include <iostream>
#include <vector>

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

int main(void)
{
    std::vector<std::string>  vString;
    vString = SplitString(ReadString(), " ");

    std::cout << "\nTokens = " << vString.size() << std::endl;

    for (std::string& s : vString)
    {
        std::cout << s << std::endl;
    }

    return (0);
}
