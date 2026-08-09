#include <iostream>

using namespace std;


class clsA
{
public:
    clsA(int value)
    {
        x = value;
    }

    int x;

    void    Print()
    {
        cout << "The value of x = " << x << endl;
    }
};

int main(void)
{
    // Initializing 3 array objects with function call //
    clsA obj[] = {clsA(10), clsA(20), clsA(30)};

    // using the print methods for each of the 3 elements //
    for (int i = 0; i < 3; i++)
    {
        obj[i].Print();
    }


    return (0);
}

