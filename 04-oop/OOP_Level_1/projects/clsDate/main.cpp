#include <iostream>
#include "clsDate.h"




int main(void)
{
    clsDate Date1;
    Date1.Print();

    clsDate Date2("12/05/2026");
    Date2.Print();

    clsDate Date3(01, 01, 2027);
    Date3.Print();

    return (0);
}