#include <iostream>


struct Person
{
    std::string Name{};
    int Age;

    void    Kisses(const Person& person)
    {
        std::cout << Name << " kisses " << person.Name << std::endl;
    }
};

int main(void)
{
    Person Joe{"Joe", 29};
    Person Kate{"Kate", 27}; 

    Joe.Kisses(Kate);

    return (0);
}