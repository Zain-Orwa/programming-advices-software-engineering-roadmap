#include "Car.h"


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