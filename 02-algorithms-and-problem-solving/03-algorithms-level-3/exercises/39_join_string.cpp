#include <iostream>



std::string JoinString(std::vector<std::string> vString, std::string Delim)
{
   std::string str = "";

   for (std::string& s : vString)
   {
        str = str + s + Delim;
   }
   return (str.substr(0, str.length() - Delim.length()));
}

int main(void)
{
    std::vector<std::string>  vString = {"Mohammed", "Fadi", "Ali", "Maher"};

    std::cout << "Vector after join:\n\n";
    std::cout << JoinString(vString, " ") << std::endl;

    return (0);
}