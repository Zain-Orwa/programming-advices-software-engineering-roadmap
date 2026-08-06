#include <iostream>
#include <string>

using namespace std;

/*
    ================================================================
                  UP CASTING vs DOWN CASTING
    ================================================================

    Inheritance direction:

            clsPerson            Base class
                ▲
                │
            clsEmployee          Derived class

    Up casting:

            clsEmployee*  ─────────►  clsPerson*
            Derived pointer           Base pointer

            Safe and usually automatic.

    Down casting:

            clsPerson*  ─────────►  clsEmployee*
            Base pointer              Derived pointer

            It is valid only when the base pointer actually points to
            a clsEmployee object.
*/

class clsPerson
{
public:
    string FullName = "Adam Smith";

    // A polymorphic base class is required when using dynamic_cast
    // for safe down casting. A virtual destructor makes this class
    // polymorphic and also allows safe destruction through a base pointer.
    virtual ~clsPerson() = default;

    virtual void PrintInfo() const
    {
        cout << "Full Name : " << FullName << '\n';
    }
};

class clsEmployee : public clsPerson
{
public:
    string Title = "CEO";

    void PrintInfo() const override
    {
        cout << "Full Name : " << FullName << '\n';
        cout << "Title     : " << Title << '\n';
    }
};

int main(void)
{
    cout << "========================================\n";
    cout << "1. Normal derived-class object\n";
    cout << "========================================\n";

    clsEmployee Employee1;

    // A derived object contains both parts:
    //
    // Employee1
    // ┌──────────────────────────────┐
    // │ clsPerson part: FullName     │
    // │ clsEmployee part: Title      │
    // └──────────────────────────────┘

    cout << Employee1.FullName << '\n';
    cout << Employee1.Title << "\n\n";


    cout << "========================================\n";
    cout << "2. Up casting\n";
    cout << "========================================\n";

    // UP CASTING:
    // Convert a derived-class pointer into a base-class pointer.
    //
    // clsEmployee*  --->  clsPerson*
    //
    // This conversion is safe because every clsEmployee IS a clsPerson.
    // The conversion is implicit, so no cast syntax is required.

    clsPerson* PersonPtr = &Employee1;

    // PersonPtr still points to the same Employee1 object.
    // No new object is created and no data is copied.
    cout << "Address of Employee1 : " << &Employee1 << '\n';
    cout << "Address in PersonPtr : " << PersonPtr << "\n\n";

    // Through a base pointer, we can directly access only members that
    // belong to the base-class interface.
    cout << PersonPtr->FullName << '\n';

    // WRONG: Title is not declared inside clsPerson.
    // The object still has Title, but the pointer type controls which
    // members can be accessed directly.
    //
    // cout << PersonPtr->Title << '\n'; // Compilation error

    // Because PrintInfo() is virtual, C++ checks the real object type.
    // PersonPtr points to a clsEmployee, so clsEmployee::PrintInfo() runs.
    PersonPtr->PrintInfo();


    cout << "\n========================================\n";
    cout << "3. Correct and safe down casting\n";
    cout << "========================================\n";

    // DOWN CASTING:
    // Convert a base-class pointer into a derived-class pointer.
    //
    // clsPerson*  --->  clsEmployee*
    //
    // This is not automatically safe because not every clsPerson is
    // necessarily a clsEmployee.
    //
    // dynamic_cast checks the real object type at runtime.

    clsEmployee* EmployeePtr = dynamic_cast<clsEmployee*>(PersonPtr);

    if (EmployeePtr != nullptr)
    {
        // The cast succeeded because PersonPtr really points to Employee1.
        cout << "Down casting succeeded.\n";
        cout << "Employee title: " << EmployeePtr->Title << '\n';
    }
    else
    {
        cout << "Down casting failed.\n";
    }


    cout << "\n========================================\n";
    cout << "4. Failed down casting detected safely\n";
    cout << "========================================\n";

    clsPerson PersonOnly;
    clsPerson* PersonOnlyPtr = &PersonOnly;

    // PersonOnlyPtr points to a real clsPerson object, not to clsEmployee.
    // dynamic_cast detects this and returns nullptr.
    clsEmployee* CheckedEmployeePtr =
        dynamic_cast<clsEmployee*>(PersonOnlyPtr);

    if (CheckedEmployeePtr == nullptr)
    {
        cout << "The cast failed safely: PersonOnly is not an Employee.\n";
    }


    /*
        ================================================================
        5. WRONG DOWN-CASTING EXAMPLE
        ================================================================

        The following static_cast compiles, but it is logically wrong:

        clsEmployee* WrongEmployeePtr =
            static_cast<clsEmployee*>(PersonOnlyPtr);

        cout << WrongEmployeePtr->Title << '\n';

        Why is it wrong?

            PersonOnlyPtr
                 │
                 ▼
            ┌──────────────────────┐
            │ Real clsPerson object│
            │ FullName             │
            │ NO Employee Title    │
            └──────────────────────┘

        static_cast does not check the real object type at runtime.
        It tells the compiler:

            "Trust me; this Person is actually an Employee."

        But that statement is false. Accessing WrongEmployeePtr->Title
        would produce UNDEFINED BEHAVIOR. The program could print garbage,
        appear to work accidentally, crash, or behave unpredictably.

        The wrong code is kept commented out so this lesson still compiles.
    */


    cout << "\n========================================\n";
    cout << "6. Up casting and down casting references\n";
    cout << "========================================\n";

    // Up casting with references is also automatic and safe.
    clsPerson& PersonRef = Employee1;
    PersonRef.PrintInfo();

    // Safe down casting with a reference:
    // dynamic_cast returns a reference when successful.
    // If it fails, it throws std::bad_cast instead of returning nullptr.
    clsEmployee& EmployeeRef = dynamic_cast<clsEmployee&>(PersonRef);
    cout << "Employee title through reference: "
         << EmployeeRef.Title << '\n';


    /*
        ================================================================
        IMPORTANT RULES TO REMEMBER
        ================================================================

        1. UP CASTING

           clsEmployee* ---> clsPerson*

           - Moves from derived type to base type.
           - Safe and normally implicit.
           - Does not create or copy an object.
           - The base pointer still points to the complete derived object.
           - Direct access is limited by the base pointer's type.
           - Virtual functions still use the real object's implementation.

        2. DOWN CASTING

           clsPerson* ---> clsEmployee*

           - Moves from base type to derived type.
           - Requires an explicit cast.
           - Valid only when the object is really a clsEmployee.
           - Prefer dynamic_cast when runtime checking is required.
           - Always check a pointer result against nullptr.

        3. dynamic_cast REQUIREMENT

           - The base class must be polymorphic.
           - A class is polymorphic when it has at least one virtual function.
           - A virtual destructor is commonly used for this purpose.

        4. POINTER vs REFERENCE FAILURE

           dynamic_cast<Derived*>(basePointer)
               -> returns nullptr when the cast fails.

           dynamic_cast<Derived&>(baseReference)
               -> throws std::bad_cast when the cast fails.

        5. static_cast

           - Performs no runtime type check.
           - It can be used only when you are already certain that the
             object really has the requested derived type.
           - A wrong static down cast leads to undefined behavior.

        6. OBJECT SLICING IS DIFFERENT FROM POINTER UP CASTING

           clsPerson PersonCopy = Employee1;

           This creates a new clsPerson object and copies only the Person
           portion. Employee-specific data such as Title is sliced away.

           A pointer or reference up cast does not slice the object:

           clsPerson* PersonPtr = &Employee1;
           clsPerson& PersonRef = Employee1;

        Simple memory rule:

           UP   = Employee becomes visible as a Person.
           DOWN = Person is treated as an Employee only after verification.
    */

    return (0);
}
