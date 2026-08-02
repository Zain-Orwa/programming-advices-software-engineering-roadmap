#ifndef COPY_CONSTRUCTOR_H
#define COPY_CONSTRUCTOR_H

#include <iostream>

using namespace std;

class Distance
{
private:
    int   _Feet;
    float _Inches;

public:
    Distance();
    Distance(int ft, float in);

    void SetDistance(int ft, float in);
    void Print();
};

#endif