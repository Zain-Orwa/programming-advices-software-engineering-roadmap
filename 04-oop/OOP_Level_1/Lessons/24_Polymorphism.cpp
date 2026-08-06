/*
    Polymorphism means "one name, many forms."

    In C++, polymorphism can be demonstrated through:

    1. Function Overloading
       The same function name is used with different parameter lists.
       The compiler chooses the correct function at compile time.

    2. Operator Overloading
       An operator is given a special meaning for objects of a class.
       The compiler chooses the overloaded operator at compile time.

    3. Function Overriding
       A derived class writes its own version of a function that already
       exists in the base class.

    4. Virtual Functions
       A base-class pointer or reference can call the overridden function
       that belongs to the actual derived object at runtime.
*/

#include <iostream>

using namespace std;

// ------------------------------------------------------------
// 1. Function Overloading: same function name, different inputs.
// ------------------------------------------------------------
class clsCalculator
{
public:
    int Add(int Number1, int Number2)
    {
        return Number1 + Number2;
    }

    double Add(double Number1, double Number2)
    {
        return Number1 + Number2;
    }
};

// ------------------------------------------------------------
// 2. Operator Overloading: give + a meaning for clsNumber objects.
// ------------------------------------------------------------
class clsNumber
{
private:
    int _Value;

public:
    clsNumber(int Value) : _Value(Value)
    {
    }

    clsNumber operator+(const clsNumber& Other) const
    {
        return clsNumber(_Value + Other._Value);
    }

    int GetValue() const
    {
        return _Value;
    }
};

// ------------------------------------------------------------
// 3. Function Overriding: derived class replaces the base version.
//    This example uses direct objects, so the object type is known.
// ------------------------------------------------------------
class clsPerson
{
public:
    void PrintRole()
    {
        cout << "I am a Person.\n";
    }
};

class clsEmployee : public clsPerson
{
public:
    void PrintRole()
    {
        cout << "I am an Employee.\n";
    }
};

// ------------------------------------------------------------
// 4. Virtual Functions: runtime polymorphism through a base pointer.
// ------------------------------------------------------------
class clsAnimal
{
public:
    virtual void MakeSound()
    {
        cout << "The animal makes a sound.\n";
    }

    virtual ~clsAnimal() = default;
};

class clsCat : public clsAnimal
{
public:
    void MakeSound() override
    {
        cout << "The cat says: Meow!\n";
    }
};

int main(void)
{
    cout << "1. Function Overloading\n";
    clsCalculator Calculator;

    cout << Calculator.Add(5, 3) << '\n';
    cout << Calculator.Add(2.5, 1.5) << "\n\n";

    cout << "2. Operator Overloading\n";
    clsNumber Number1(10);
    clsNumber Number2(20);
    clsNumber Result = Number1 + Number2;

    cout << Result.GetValue() << "\n\n";

    cout << "3. Function Overriding\n";
    clsPerson Person1;
    clsEmployee Employee1;

    Person1.PrintRole();
    Employee1.PrintRole();
    cout << '\n';

    cout << "4. Virtual Function\n";
    clsCat Cat1;

    // The pointer type is clsAnimal*, but it points to a clsCat object.
    // Because MakeSound() is virtual, C++ chooses clsCat::MakeSound()
    // at runtime according to the actual object.
    clsAnimal* AnimalPointer = &Cat1;
    AnimalPointer->MakeSound();

    return 0;
}
