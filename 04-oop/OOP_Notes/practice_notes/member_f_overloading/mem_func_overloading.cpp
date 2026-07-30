#include <iostream>
#include <string>

struct Date
{
    int year {};
    int month {};
    int day {}; 

    void    print()
    {
        std::cout << year << '/' << month << '/' << day << std::endl;
    }

    void    print(std::string_view prefix)
    {
        std::cout << prefix << year << '/' << month << '/' << day << std::endl; 
    }
};


int main(void)
{
    Date today{2026,7,30};

    today.print();

    today.print("today is: ");

    return (0);
}