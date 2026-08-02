#include "copy_constructor.h"

Distance::Distance()
    : _Feet(0), _Inches(0.0f)
{
}

Distance::Distance(int ft, float in)
    : _Feet(ft), _Inches(in)
{
}

void Distance::SetDistance(int ft, float in)
{
    _Feet = ft;
    _Inches = in;
}

void Distance::Print()
{
    std::cout << "Feet = " << _Feet
              << "\tInches = " << _Inches << '\n';
}