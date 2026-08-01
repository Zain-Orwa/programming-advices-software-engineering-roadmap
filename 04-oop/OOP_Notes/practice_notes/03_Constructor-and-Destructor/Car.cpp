#include "Car.h"

Car::Car(string maker, int model, string color) : _Maker(maker),_Model(model),_Color(color)
{

}

Car::~Car()
{
    std::cout << "Goodby!";
}

void    Car::SetMaker(string make)
{
    _Maker = make;
}

string  Car::GetMaker()
{
    return (_Maker);
}


void    Car::SetModel(int mod)
{
    _Model = mod;
}

int  Car::GetModel()
{
    return (_Model);
}