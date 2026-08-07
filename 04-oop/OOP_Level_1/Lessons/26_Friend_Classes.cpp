/*
    Friend Classes in C++

    A friend class is a class that is given special permission to access
    another class's private and protected members.

    In this example, clsA contains:

        private:    _Var1
        protected:  _Var3
        public:      Var2

    Normally, clsB could access only the public member Var2.

    But inside clsA we write:

        friend class clsB;

    This tells C++:

        "Allow clsB to access all members of clsA, including its
         private and protected members."

    Therefore, inside clsB these are all valid:

        A._Var1   // private   -> accessible because clsB is a friend
        A.Var2    // public    -> accessible normally
        A._Var3   // protected -> accessible because clsB is a friend

    Visual idea:

        clsA
        +---------------------------+
        | private:   _Var1 = 10     |
        | protected: _Var3 = 30     |
        | public:     Var2  = 20    |
        |                           |
        | friend class clsB;        |
        +-------------+-------------+
                      |
                      | gives access
                      v
        +---------------------------+
        |           clsB            |
        |                           |
        | can access:               |
        | A._Var1   -> YES          |
        | A.Var2    -> YES          |
        | A._Var3   -> YES          |
        +---------------------------+

    Important rules:

    1. Friendship is NOT inheritance.
       clsB does not inherit members from clsA.

    2. Friendship is one-way.
       "friend class clsB;" inside clsA gives clsB access to clsA,
       but it does not automatically give clsA access to clsB.

    3. Friendship is not automatically inherited.
       A class derived from clsB does not automatically become a friend of clsA.

    4. Friendship is not automatically transitive.
       If clsB is a friend of clsA and clsC is a friend of clsB,
       clsC does not automatically become a friend of clsA.

    5. clsB still needs an object of clsA to access these non-static members.
       In this example, that object is A inside the clsB constructor.
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

    friend class clsB;
};

class clsB
{
public:
    clsB(clsA A)
    {
        cout << "The value of Var1 = " << A._Var1 << endl;
        cout << "The value of Var2 = " << A.Var2 << endl;
        cout << "The value of Var3 = " << A._Var3 << endl;
    }

};


int main(void)
{
    clsA A1;

    clsB B1(A1);


    return (0);
}