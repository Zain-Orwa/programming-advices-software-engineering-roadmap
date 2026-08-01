#include "Car.h"

int main(void)
{
    Car c1("Honda", 2026, "Pink");
    std::cout << c1.GetMaker() << std::endl;
    Car c2;
    std::cout << c2.GetMaker() << std::endl;

    return (0);
}