#include <iostream>

using namespace std;

class clsA 
{
private:

public:
    int Var;
    static  int counter;

    clsA()
    {
        counter++;
    }

    void Print()
    {
        cout << "\nVar     = " << Var << endl;
        cout << "Counter = " << counter << endl;
    }

};
int clsA::counter = 0; // initialize the static variable outside the class.

int main(void)
{
    clsA A1, A2, A3, A4;

    A1.Var = 10;
    A2.Var = 20;
    A3.Var = 30;
    A4.Var = 40;

    std::cout << "\nBefore changing the static member variable:\n";
    A1.Print();
    A2.Print();
    A3.Print();
    A4.Print();
    


    // Changing the static variable with change all the value of the static in all the class:
    // also we can call change the static variable from the class itself or the object
    A1.counter = 1000;
    std::cout << "\nAfter changing the static member counter in one object:\n";
    A1.Print();
    A2.Print();
    A3.Print();
    A4.Print();
    
    
    return (0);
}