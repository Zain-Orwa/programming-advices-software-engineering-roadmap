#include "Car.h"

int main(void)
{
    Car c1;

    c1.SetMaker("Honda");
    cout << c1.GetMaker() << endl;

    c1.SetModel(1956);
    cout << c1.GetModel() << endl;

    return (0);
}