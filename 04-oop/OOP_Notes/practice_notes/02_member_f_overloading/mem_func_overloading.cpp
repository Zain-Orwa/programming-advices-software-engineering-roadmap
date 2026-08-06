/* 
    Best practice[1]:
    Member functions can be used with both structs and classes.
    However, structs should avoid defining constructor member functions, 
    as doing so makes them a non-aggregate. 


    Best practice[2]:
    If your class type has no data members, prefer using a namespace.
*/

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