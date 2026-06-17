#include <iostream>

void    PrintFibonacciSeries(int Number)
{
    int prev1;
    int prev2;
    int fibon;

    prev1 = 1;
    prev2 = 1;
    fibon = 0;    
    std::cout << prev1 << "     ";
    std::cout << prev2 << "     ";
    for (int i = 2; i < Number; i++)
    {
        fibon = prev1 + prev2;
        std::cout << fibon << "     ";
        prev2 = prev1;
        prev1 = fibon;
    }
    std::cout << "\n";
}

int main(void)
{
    PrintFibonacciSeries(-1);

    return (0);
}