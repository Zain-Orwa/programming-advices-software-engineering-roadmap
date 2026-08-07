#include <iostream>
#include "30_clsPerson.h"
#include "30_clsEmployee.h"

using namespace std;

int main(void)
{
    clsEmployee Employee1(10, "Joko", "Jakoom", "jajo@jao.com", "098765432", "Eater", "Taster", 5000);

    Employee1.Print();

    return (0);
}