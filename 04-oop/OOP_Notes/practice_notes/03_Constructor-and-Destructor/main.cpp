#include "Car.h"

int main(void)
{
    Car c1("Toyota", 2020, "White");

    std::cout << "This car made by  " << c1.GetMaker() << "\n";
    std::cout << "This car model is " << c1.GetModel() << "\n";

    Car c2("Fiat", 2025, "Green");

    std::cout << "This car made by  " << c2.GetMaker() << "\n";
    std::cout << "This car model is " << c2.GetModel() << "\n";

    return (0);
}