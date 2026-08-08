#include <iostream>

using namespace std;

class clsA
{
public:
    int _x;

    void    Print()
    {
        cout << "The value x = " << _x << endl;
    }

    // object sent by value will not be reflectd on the original object.
    void    Func1(clsA A1)
    {
        A1._x = 100;
    }

    // object sent by Reference, any update will be reflected on the original object.
    void    Func2(clsA& A1)
    {
        A1._x = 200;
    }
}; 

int main(void)
{
    clsA    A1;

    A1._x = 50;
    cout << "A1.x before calling Function1 or Function1:\n";
    A1.Print();

    A1.Func1(A1);
    cout << "A1.x After calling Function1:\n";
    A1.Print();

    A1.Func2(A1);
    cout << "A1.x after calling Function2:\n";
    A1.Print();

    return (0);
}