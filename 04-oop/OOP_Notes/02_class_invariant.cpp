#include <iostream>

struct Fraction 
{
    int Numerator {0};
    int Denominator {1};
};

void    PrintFractionValue(const Fraction& f)
{
    std::cout << f.Numerator / f.Denominator << '\n';
}

int main(void)
{
    Fraction f {5, 0}; // this here is the problem //

    PrintFractionValue(f); // cause divide by zero error //

    return (0);
}
