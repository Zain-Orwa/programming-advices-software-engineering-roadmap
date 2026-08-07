/*
    FRIEND FUNCTION
    ===============

    A friend function is a normal function that is NOT a member of a class,
    but the class gives that function special permission to access its
    private and protected members.

    Normally, code outside clsA cannot access:

        A1._Var1   // private
        A1._Var3   // protected

    But inside clsA we declare:

        friend int MySum(clsA A1);
        friend int MySub(clsA A2);

    This means clsA is saying:

        "MySum() and MySub() are allowed to access my private,
         protected, and public members."

    The friend functions are still OUTSIDE the class:

        class clsA
        {
            ...
            friend int MySum(clsA A1);   // permission is given here
        };

        int MySum(clsA A1)                // function is defined outside
        {
            return (A1._Var1 + A1.Var2 + A1._Var3);
        }

    Because MySum() is a friend of clsA, all of these are valid inside it:

        A1._Var1   // private   -> allowed
        A1._Var3   // protected -> allowed
        A1.Var2    // public    -> allowed

    IMPORTANT:
    - A friend function is NOT a member function of the class.
    - It does NOT use the class :: operator when it is defined.
    - It does NOT have a "this" pointer.
    - It normally needs a class object passed to it to access that object's data.
    - Only the function(s) explicitly declared as friend receive the permission.


    FRIEND CLASS vs FRIEND FUNCTION
    ===============================

    FRIEND CLASS:

        friend class clsB;

        -> The ENTIRE clsB class becomes a friend.
        -> ALL member functions inside clsB can access clsA's
           private and protected members.

        clsA  ----------------------->  clsB
              gives access to          ALL clsB member functions


    FRIEND FUNCTION:

        friend int MySum(clsA A1);

        -> Only MySum() becomes a friend.
        -> Other functions do NOT receive access automatically.

        clsA  ----------------------->  MySum()
              gives access only to     ONE specific function


    Simple difference:

        friend class    = give permission to a WHOLE CLASS.
        friend function = give permission to ONE SPECIFIC FUNCTION.

    In this example:

        friend int MySum(clsA A1);
        friend int MySub(clsA A2);

    MySum() and MySub() can access _Var1 and _Var3 because each function
    was individually declared as a friend of clsA.
*/

#include <iostream>

using namespace std;

class clsA
{
private:
    int _Var1;

protected:
    int _Var3;

public:
    int Var2;

    clsA()
    {
        _Var1 = 10;
        Var2  = 20;
        _Var3 = 30;
    }

    // Only these two functions are given friend access to clsA.
    friend int MySum(clsA A1);
    friend int MySub(clsA A2);
};


int MySum(clsA A1)
{
    // Friend function: can access private, protected, and public members.
    return (A1._Var1 + A1.Var2 + A1._Var3);
}

int MySub(clsA A2)
{
    // Friend function: can access private, protected, and public members.
    return (A2._Var3 - A2.Var2 - A2._Var1);
}

int main(void)
{
    clsA A1;

    // MySum() and MySub() are normal functions, so we call them directly.
    cout << "The sum of the class variables = " << MySum(A1) << endl;
    cout << "The sub of the class variables = " << MySub(A1) << endl;

    return (0);
}
