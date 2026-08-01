#include "Car.h"

Car::Car(string m, int mo, string c) : _Maker(m),_Model(mo),_Color(c)
{

}

Car::Car(): _Maker("Toyota"), _Model(2026), _Color("White")
{

}

Car::~Car()
{

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