#include <iostream>

void    PrintFibonacciSeries(int Number, int Previous, int Current)
{
    int Next = 0;

    if (Number > 0)
    {
        std::cout << Current << "   ";
        Next = Previous + Current;
        PrintFibonacciSeries(Number - 1, Current, Next);
    }
}

int main(void)
{
    PrintFibonacciSeries(10, 0, 1);

    return (0);
}