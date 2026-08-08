/*
    ============================================================================
                              C++: THE `this` POINTER
    ============================================================================

    1) WHAT IS `this`?
    ---------------------------------------------------------------------------
    `this` is a special pointer that C++ makes available inside a NON-STATIC
    member function of a class.

    It points to the CURRENT OBJECT -- the object that called the member
    function.

    Example:

        clsEmployee Employee1(44, "Momo", 500.50);
        Employee1.Print();

    While Print() is running for Employee1:

        this == &Employee1

    So if Employee1 is stored at address 0x1000, then inside Employee1.Print(),
    `this` contains 0x1000.

    IMPORTANT:
    - The object has memory and therefore has an address.
    - The object's DATA MEMBERS are stored as part of that object's memory.
    - Ordinary member functions are NOT copied into every object.
      The function code is shared, and `this` tells the function WHICH object
      it is currently working with.

    Conceptually, a call such as:

        Employee1.Print();

    can be imagined roughly like:

        clsEmployee::Print(&Employee1);

    C++ does this automatically. `this` is the hidden connection between the
    member function and the object that called it.


    2) WHERE CAN `this` BE USED?
    ---------------------------------------------------------------------------
    `this` is available inside non-static member functions, including:

        - constructors
        - normal member functions
        - const member functions
        - destructors

    `this` is NOT available inside:

        - static member functions
        - free/global functions
        - friend functions (a friend is not a member function)

    A static member function belongs to the class but is not called on one
    specific object, so there is no current object and therefore no `this`.


    3) ACCESSING MEMBERS THROUGH `this`
    ---------------------------------------------------------------------------
    Inside a member function:

        ID

    is normally equivalent to:

        this->ID

    Example:

        void Print()
        {
            cout << this->ID << endl;
            cout << this->Name << endl;
            cout << this->Salary << endl;
        }

    Usually we omit `this->` when there is no ambiguity.


    ============================================================================
                         MAIN USE CASES OF `this`
    ============================================================================

    USE CASE 1: DISTINGUISH DATA MEMBERS FROM PARAMETERS
    ---------------------------------------------------------------------------
    This is the most common beginner use case.

    If a constructor parameter has the same name as a data member:

        clsEmployee(int ID, string Name, float Salary)
        {
            this->ID     = ID;
            this->Name   = Name;
            this->Salary = Salary;
        }

    Meaning:

        this->ID   -> the ID that belongs to the current object
        ID         -> the constructor parameter

    Without `this->`:

        ID = ID;

    both names refer to the parameter, so the object's ID would not be changed.


    USE CASE 2: EXPLICITLY ACCESS THE CURRENT OBJECT'S MEMBERS
    ---------------------------------------------------------------------------
    `this->` can make it explicit that a variable or function belongs to the
    current object.

        void PrintSalary()
        {
            cout << this->Salary << endl;
            this->Print();
        }

    In ordinary classes, these are usually equivalent:

        Print();
        this->Print();


    USE CASE 3: PASS THE CURRENT OBJECT TO ANOTHER FUNCTION
    ---------------------------------------------------------------------------
    `this` is a pointer to the current object.
    `*this` is the current object itself.

    Pass the current object by reference:

        static void Func1(const clsEmployee& Employee)
        {
            Employee.Print();
        }

        void Func2()
        {
            Func1(*this);
        }

    Pass the current object's address:

        static void Func3(const clsEmployee* Employee)
        {
            Employee->Print();
        }

        void Func4()
        {
            Func3(this);
        }

    Remember:

        this   -> pointer/address of the current object
        *this  -> the current object


    USE CASE 4: PASS THE CURRENT OBJECT TO ANOTHER CLASS
    ---------------------------------------------------------------------------
    Another class may need to receive or work with the current object.

        class clsPrinter
        {
        public:
            static void PrintEmployee(const clsEmployee& Employee);
        };

        void clsEmployee::SendToPrinter()
        {
            clsPrinter::PrintEmployee(*this);
        }

    Or pass its address if the other class expects a pointer:

        clsPrinter::RegisterEmployee(this);


    USE CASE 5: RETURN THE CURRENT OBJECT FOR METHOD CHAINING
    ---------------------------------------------------------------------------
    Returning `*this` by reference lets several member functions be chained.

        class clsCounter
        {
            int Value = 0;

        public:
            clsCounter& Add(int Number)
            {
                Value += Number;
                return *this;
            }
        };

        clsCounter Counter;
        Counter.Add(10).Add(20).Add(30);

    `return *this;` returns the same current object, not a new object.


    USE CASE 6: CHECK WHETHER TWO REFERENCES ARE THE SAME OBJECT
    ---------------------------------------------------------------------------
    This is often used in assignment operators to protect against
    self-assignment.

        clsEmployee& operator=(const clsEmployee& Other)
        {
            if (this == &Other)
                return *this;

            ID     = Other.ID;
            Name   = Other.Name;
            Salary = Other.Salary;

            return *this;
        }

    Here:

        this   -> address of the current object
        &Other -> address of the other object

    If the addresses are equal, both names refer to the same object.


    USE CASE 7: CAPTURE THE CURRENT OBJECT IN A LAMBDA
    ---------------------------------------------------------------------------
    A lambda created inside a member function can capture `this` so it can use
    members of the current object.

        void ShowLater()
        {
            auto Func = [this]()
            {
                cout << ID << " " << Name << endl;
            };

            Func();
        }

    `[this]` captures the POINTER to the current object.

    Since C++17, `[*this]` captures a COPY of the current object instead:

        auto Func = [*this]()
        {
            cout << ID << endl;
        };

    Be careful with `[this]` if the lambda may live longer than the object,
    because the stored pointer would then point to an object that no longer
    exists.


    USE CASE 8: ACCESS MEMBERS IN SOME CLASS-TEMPLATE SITUATIONS
    ---------------------------------------------------------------------------
    In a derived class template, `this->` may be required so the compiler knows
    that a name comes from a dependent base class.

        template <typename T>
        class Base
        {
        protected:
            int Value = 10;
        };

        template <typename T>
        class Derived : public Base<T>
        {
        public:
            void Print()
            {
                cout << this->Value << endl;
            }
        };

    This is a more advanced use of `this->` that becomes important when
    learning templates.


    ============================================================================
                              IMPORTANT DETAILS
    ============================================================================

    A) `this` IN A CONST MEMBER FUNCTION
    ---------------------------------------------------------------------------
    In a const member function, `this` points to a const object, so you cannot
    normally modify its data members through `this`.

        void Print() const
        {
            cout << this->ID << endl;   // OK: reading
            // this->ID = 50;           // ERROR: modifying through const `this`
        }


    B) `this` CANNOT BE REASSIGNED
    ---------------------------------------------------------------------------
    `this` always represents the object for the current member-function call.
    You cannot make it point to another object.

        // this = &Other;   // ERROR


    C) STATIC FUNCTIONS DO NOT HAVE `this`
    ---------------------------------------------------------------------------

        static void Func()
        {
            // cout << this->ID;   // ERROR
        }

    A static function can still receive an object explicitly:

        static void Func(const clsEmployee& Employee)
        {
            cout << Employee.ID << endl;
        }


    D) FRIEND FUNCTIONS DO NOT HAVE `this`
    ---------------------------------------------------------------------------
    A friend function may access private/protected members if friendship gives
    it permission, but it is still NOT a member function and gets no automatic
    `this` pointer.

        friend void Show(const clsEmployee& Employee)
        {
            cout << Employee.ID << endl;
            // cout << this->ID;   // ERROR
        }


    E) `delete this` EXISTS, BUT IS DANGEROUS
    ---------------------------------------------------------------------------
    C++ technically allows code such as:

        delete this;

    in very special designs, but it is extremely easy to create undefined
    behavior. The object must have been allocated correctly (typically with
    `new`), nothing may use the object afterward, and ownership must be very
    carefully controlled.

    For normal C++ code, DO NOT use `delete this`.


    ============================================================================
                                  MEMORY IDEA
    ============================================================================

    Suppose an object begins at address 0x1000:

        Employee1
        address: 0x1000

        +-------------------------+
        | ID                      |
        | Name                    |   <- data belonging to Employee1
        | Salary                  |
        +-------------------------+

    During:

        Employee1.Print();

    conceptually:

        this = &Employee1
        this = 0x1000

    Then:

        this->ID
        this->Name
        this->Salary

    mean: access those members inside the object located at the address stored
    in `this`.


    ============================================================================
                                QUICK SUMMARY
    ============================================================================

        this        = pointer/address of the current object
        *this       = the current object
        this->Member= access a member of the current object
        &Object     = address of an object

    `this` exists because one shared member function needs to know WHICH object
    it is currently working on.

    Example:

        clsEmployee Employee1(...);
        clsEmployee Employee2(...);

        Employee1.Print();   // inside Print(): this == &Employee1
        Employee2.Print();   // inside Print(): this == &Employee2

    Same Print() function code, different `this` pointer for each call.
*/


#include <iostream>

using namespace std;

class clsEmployee
{
public:
    int     ID;
    string  Name;
    float   Salary;

    clsEmployee(int ID, string Name, float Salary)
    {
        this->ID = ID;
        this->Name = Name;
        this->Salary = Salary;
    }

    static  void    Func1(clsEmployee Employee)
    {
        Employee.Print();
    }

    void    Func2()
    {
        Func1(*this);
    }

    void    Print()
    {
        cout << ID << " " << Name << " " << Salary << endl;
        cout << "the object address is " << this << endl;
    }



};

int main(void)
{
    clsEmployee Employee1(44, "Momo", 500.50);

    Employee1.Print();

    return (0);
}
