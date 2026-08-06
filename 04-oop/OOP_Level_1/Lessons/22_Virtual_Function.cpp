/*
    What is a virtual function?

    Before understanding virtual functions, we need to understand two concepts:

    1. Function overriding
       A derived class can provide its own version of a function that already exists
       in the base class.

    2. Upcasting through pointers
       A pointer of the base-class type can point to an object of a derived class.

    The problem appears when we combine these two concepts.

    Example:

        clsEmployee Employee1;
        clsPerson* Person1 = &Employee1;

    Here, Person1 is a clsPerson pointer, but it points to a clsEmployee object.

    Without the virtual keyword, calling:

        Person1->Print();

    would execute clsPerson::Print() because the pointer type is clsPerson*.
    The overridden Print() function inside clsEmployee would not be selected.

    To solve this problem, we declare Print() as virtual inside the base class:

        virtual void Print();

    Now C++ checks the real object type at runtime. Therefore, when a clsPerson
    pointer points to a clsEmployee object, clsEmployee::Print() is executed.

    This behavior is called runtime polymorphism or dynamic dispatch.

    C++ compilers commonly implement virtual functions using a virtual table
    (vtable), although the C++ standard does not require a specific implementation.
*/

#include <iostream>

using namespace std;

class clsPerson
{
public:
    virtual void Print()
    {
        cout << "Hi, I'm a Person!\n";
    }
};

class clsEmployee : public clsPerson
{
public:
    void Print() override
    {
        cout << "Hi, I'm an Employee!\n";
    }
};

class clsStudent : public clsPerson
{
public:
    void Print() override
    {
        cout << "Hi, I'm a Student!\n";
    }
};

int main(void)
{
    // Normal function overriding using derived-class objects.
    clsEmployee Employee1;
    clsStudent Student1;

    Employee1.Print();
    Student1.Print();

    cout << "------------------------------\n";

    // Upcasting: base-class pointers point to derived-class objects.
    clsPerson* Person1 = &Employee1;
    clsPerson* Person2 = &Student1;

    /*
        Because Print() is virtual in clsPerson, C++ checks the real object type:

        Person1 points to a clsEmployee object -> clsEmployee::Print()
        Person2 points to a clsStudent object  -> clsStudent::Print()

        Without virtual, both calls would execute clsPerson::Print().
    */
    Person1->Print();
    Person2->Print();

    return (0);
}
