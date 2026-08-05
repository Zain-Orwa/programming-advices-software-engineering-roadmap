/*
# What permissions do access modifiers give in inheritance?

1. private:
   - Accessible only inside the same class.
   - The derived class cannot access private members directly.

2. protected:
   - Accessible inside the same class.
   - Accessible inside derived classes.
   - Not accessible outside the class through an object.

3. public:
   - Accessible inside the same class.
   - Accessible inside derived classes.
   - Accessible outside the class through an object.


If clsB inherits publicly from clsA:

1. clsB cannot directly access the private members of clsA.

2. clsB can access the protected members of clsA,
   but only inside a member function of clsB.

3. Public members of clsA can be accessed inside clsB
   and outside through an object.
*/

#include <iostream>

using namespace std;

class clsA
{
private:
    int _Var1;

    void _Func1()
    {
        cout << "Function 1\n";
    }

protected:
    int _Var2;

    void _Func2()
    {
        cout << "Function 2\n";
    }

public:
    int _Var3;

    void _Func3()
    {
        cout << "Function 3\n";
    }
};


class clsB : public clsA
{
    /*
        You cannot write executable statements directly here:

        _Var2 = 10;   // ❌ Wrong
        _Func2();     // ❌ Wrong

        The body of a class is used to declare variables
        and functions, not to execute statements.
    */

public:
    void Func1()
    {
        // ❌ Private members of clsA cannot be accessed directly.
        // _Var1 = 10;
        // _Func1();


        // ✅ Protected members can be accessed inside a clsB function.
        _Var2 = 20;
        _Func2();


        // ✅ Public members can also be accessed inside clsB.
        _Var3 = 30;
        _Func3();


        // You can also explicitly mention the base class:
        clsA::_Var2 = 40;
        clsA::_Func2();
    }
};


int main(void)
{
    clsA A;
    clsB B;


    // ❌ Private members cannot be accessed outside clsA.
    // A._Var1 = 10;
    // A._Func1();


    // ❌ Protected members cannot be accessed through an object.
    // A._Var2 = 20;
    // A._Func2();

    // B._Var2 = 20;
    // B._Func2();


    // ✅ Public members can be accessed through objects.
    A._Var3 = 30;
    A._Func3();

    B._Var3 = 40;
    B._Func3();


    // ✅ This function can internally access inherited protected members.
    B.Func1();


    return (0);
}