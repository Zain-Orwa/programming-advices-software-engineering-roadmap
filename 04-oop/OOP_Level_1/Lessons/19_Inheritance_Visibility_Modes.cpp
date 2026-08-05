#include <iostream>
using namespace std;

/*
========================================================
Inheritance Visibility Modes
========================================================

Base class clsA has:
- private    : V1, Fun1()
- protected  : V2, Fun2()
- public     : V3, Fun3()

Important:
1) private members of clsA are NEVER directly accessible in clsB or clsC.
2) protected members can be used inside derived classes.
3) public members can be used:
   - inside derived classes
   - and through objects only if they stay public after inheritance.

Change this line:
    class clsB : private clsA

to one of these and test:
    class clsB : public clsA
    class clsB : protected clsA
    class clsB : private clsA
*/

class clsA
{
private:
    int V1;

    int Fun1()
    {
        return 1;
    }

protected:
    int V2;

    int Fun2()
    {
        return 2;
    }

public:
    int V3;

    int Fun3()
    {
        return 3;
    }
};


// Try changing private -> public / protected / private
class clsB : private clsA
{
public:
    int Fun4()
    {
        return 4;
    }

    void TestInsideB()
    {
        /*
        Inside clsB:

        - V1 and Fun1() are NOT accessible
          because they are private in clsA.

        - V2 and Fun2() ARE accessible
          because protected members are accessible inside derived class.

        - V3 and Fun3() ARE accessible inside clsB,
          no matter if they later become public/protected/private in clsB.
        */

        // V1 = 10;      // ❌ Error: private in clsA
        // Fun1();       // ❌ Error: private in clsA

        V2 = 20;         // ✅ OK
        cout << "clsB can access V2 and Fun2(): " << Fun2() << "\n";

        V3 = 30;         // ✅ OK
        cout << "clsB can access V3 and Fun3(): " << Fun3() << "\n";
    }
};


class clsC : public clsB
{
public:
    int Fun5()
    {
        return 5;
    }

    void TestInsideC()
    {
        /*
        What clsC can access depends on the inheritance mode used in clsB:

        CASE 1: class clsB : public clsA
        --------------------------------
        - V2 / Fun2() stay protected in clsB
        - V3 / Fun3() stay public in clsB
        - clsC can access V2 / Fun2() and V3 / Fun3() inside clsC

        CASE 2: class clsB : protected clsA
        -----------------------------------
        - V2 / Fun2() stay protected in clsB
        - V3 / Fun3() become protected in clsB
        - clsC can still access them inside clsC

        CASE 3: class clsB : private clsA
        ---------------------------------
        - V2 / Fun2() become private in clsB
        - V3 / Fun3() become private in clsB
        - clsC CANNOT access them
        */

        // This code only works when clsB inherits from clsA as public or protected.
        // It does NOT work if clsB inherits from clsA as private.

        // V2 = 100;                        // ✅ / ❌ depends on clsB visibility mode
        // cout << Fun2() << "\n";          // ✅ / ❌ depends on clsB visibility mode

        // V3 = 200;                        // ✅ / ❌ depends on clsB visibility mode
        // cout << Fun3() << "\n";          // ✅ / ❌ depends on clsB visibility mode

        cout << "Fun5(): " << Fun5() << "\n";
    }
};


int main()
{
    clsB B1;
    clsC C1;

    cout << "----- Access inside class functions -----\n";
    B1.TestInsideB();
    C1.TestInsideC();

    cout << "\n----- Access through objects -----\n";

    /*
    Try these lines after changing the inheritance mode in clsB.
    Only PUBLIC members of the final class are accessible through objects.
    */

    // =========================
    // Test object B1
    // =========================

    cout << "B1.Fun4(): " << B1.Fun4() << "\n";   // ✅ Always OK (Fun4 is public in clsB)

    // B1.V3 = 10;                                // ✅ only if clsB : public clsA
    // cout << B1.Fun3() << "\n";                 // ✅ only if clsB : public clsA

    // B1.V2 = 20;                                // ❌ Never accessible through object
    // cout << B1.Fun2() << "\n";                 // ❌ Never accessible through object

    // =========================
    // Test object C1
    // =========================

    cout << "C1.Fun4(): " << C1.Fun4() << "\n";   // ✅ Always OK (public in clsB, inherited publicly by clsC)
    cout << "C1.Fun5(): " << C1.Fun5() << "\n";   // ✅ Always OK

    // C1.V3 = 50;                                // ✅ only if clsB : public clsA
    // cout << C1.Fun3() << "\n";                 // ✅ only if clsB : public clsA

    // C1.V2 = 60;                                // ❌ Never accessible through object
    // cout << C1.Fun2() << "\n";                 // ❌ Never accessible through object

    return 0;
}

