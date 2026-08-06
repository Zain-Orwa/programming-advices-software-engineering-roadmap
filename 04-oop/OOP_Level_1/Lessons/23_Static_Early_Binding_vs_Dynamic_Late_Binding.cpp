/*
    Static/Early Binding vs Dynamic/Late Binding

    Binding means deciding which version of a function should be executed.

    1. Static Binding (Early Binding)

       Static binding happens at compile time.
       The compiler already knows the exact object type, so it can choose the
       correct function before the program starts running.

       Example:

           clsEmployee Employee1;
           Employee1.Print();

       Employee1 is directly declared as a clsEmployee object. Therefore, the
       compiler selects clsEmployee::Print().

    2. Dynamic Binding (Late Binding)

       Dynamic binding happens at runtime. It is used when a base-class pointer
       or reference points to a derived-class object and calls a virtual function.

       Example:

           clsEmployee Employee1;
           clsPerson* Person1 = &Employee1;
           Person1->Print();

       Person1 is a clsPerson pointer, but the real object is clsEmployee.
       Because Print() is virtual, C++ checks the real object type at runtime and
       executes clsEmployee::Print().

       Without the virtual keyword, the call would use static binding and execute
       clsPerson::Print() because the pointer type is clsPerson*.

    Simple summary:

        Direct object call                         -> Static/Early Binding
        Base pointer + virtual function call       -> Dynamic/Late Binding

        Employee1.Print()                          -> clsEmployee::Print()
        Person1->Print()                           -> Real object's Print()
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
    clsEmployee Employee1;
    clsStudent Student1;

    // Static/Early Binding: the exact object types are already known.
    Employee1.Print();
    Student1.Print();

    cout << "------------------------------\n";

    clsPerson* Person1 = &Employee1;
    clsPerson* Person2 = &Student1;

    // Dynamic/Late Binding: virtual selects the real object's function at runtime.
    Person1->Print();
    Person2->Print();

    return (0);
}
