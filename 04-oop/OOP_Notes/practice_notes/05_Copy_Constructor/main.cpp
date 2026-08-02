#include "copy_constructor.h"


int main()
{
    Distance d1;
    Distance d2(5, 5.5);
    Distance d3(d2);

    d1.Print();
    d3.Print();
    
    d3.SetDistance(7, 7.7);
    Distance d4 = d3;

    d4.Print();

    return 0;
}