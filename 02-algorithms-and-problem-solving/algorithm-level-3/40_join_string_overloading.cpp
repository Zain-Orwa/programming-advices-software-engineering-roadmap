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

std::string JoinString(std::string arr_str[], size_t size, std::string Delim)
{
    std::string str2 = "";

    for (size_t i = 0; i < size; i++)
    {
        str2 = str2 + arr_str[i] + Delim;
    }
    return (str2.substr(0, str2.length() - Delim.length()));
}

int main(void)
{
    std::vector<std::string>  vString = {"Mohammed", "Fadi", "Ali", "Maher"};
    std::string arr_str[] = {"Mohammed", "Fadi", "Ali", "Maher"};

    //functions overloading:
    std::cout << "\nVector after join:\n";
    std::cout << JoinString(vString, "#V#") << std::endl;

    std::cout << "\nArray after join:\n";
    std::cout << JoinString(arr_str, 4,  "#A#") << std::endl;


    return (0);
}