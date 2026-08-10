/*
===============================================================================
36 - What is the Difference Between Class and Structure in C++?
===============================================================================

IMPORTANT:
----------
In C++, `struct` and `class` are almost the SAME language feature.

The two real language differences are:

    1. Default member access
       struct  -> public by default
       class   -> private by default

    2. Default inheritance access
       struct Derived : Base  -> public inheritance by default
       class  Derived : Base  -> private inheritance by default

Almost everything else can be done with BOTH:

    - Data members
    - Member functions
    - public / private / protected
    - Constructors
    - Destructors
    - Copy constructors
    - Move constructors
    - Operator overloading
    - Static members
    - Inheritance
    - Virtual functions / polymorphism
    - Templates
    - Objects on the stack
    - Objects on the heap

-------------------------------------------------------------------------------
1) KEYWORD
-------------------------------------------------------------------------------

    struct stPerson
    {
    };

    class clsPerson
    {
    };

The keyword is different, but both define a user-defined type.

-------------------------------------------------------------------------------
2) DEFAULT MEMBER ACCESS
-------------------------------------------------------------------------------

STRUCT:

    struct stExample
    {
        int X;       // public automatically
    };

CLASS:

    class clsExample
    {
        int X;       // private automatically
    };

So this works:

    stExample S;
    S.X = 10;

But this does NOT work:

    clsExample C;
    C.X = 10;        // ERROR: X is private

Of course, we can explicitly write public/private/protected in BOTH.

-------------------------------------------------------------------------------
3) DEFAULT INHERITANCE ACCESS
-------------------------------------------------------------------------------

    struct stEmployee : clsPerson
    {
    };

is the same as:

    struct stEmployee : public clsPerson
    {
    };

But:

    class clsEmployee : clsPerson
    {
    };

is the same as:

    class clsEmployee : private clsPerson
    {
    };

This is one of the most important real differences between struct and class.

-------------------------------------------------------------------------------
4) PURPOSE: CONVENTION, NOT A C++ RULE
-------------------------------------------------------------------------------

A common style is:

    struct -> simple grouped data
    class  -> encapsulated object with behavior and private state

Example from our previous lessons:

    struct stPersonData
    {
        string FirstName;
        string LastName;
    };

This is convenient when we simply want to group related values.

For a class such as clsPerson, we often hide the data and expose controlled
functions such as GetFirstName(), GetFullName(), etc.

BUT C++ does NOT force this rule.
A struct may use encapsulation, methods, inheritance, and virtual functions.
A class may also simply contain public data.

-------------------------------------------------------------------------------
5) STACK VS HEAP - THE COMMON MISCONCEPTION
-------------------------------------------------------------------------------

WRONG idea:

    struct = value type / stack
    class  = reference type / heap

That is NOT how C++ works.

Both structs and classes can be created with automatic storage:

    stAddress Address1;
    clsPerson Person1;

And both can be dynamically allocated:

    stAddress* Address2 = new stAddress;
    clsPerson* Person2 = new clsPerson;

The choice between stack/automatic storage and dynamic storage has nothing to
with whether the type was declared with `struct` or `class`.

-------------------------------------------------------------------------------
6) CONSTRUCTORS - ANOTHER COMMON MISCONCEPTION
-------------------------------------------------------------------------------

WRONG idea:

    struct -> only parameterized constructors
    class  -> all constructor types

In C++, BOTH struct and class can have:

    - Default constructor
    - Parameterized constructor
    - Copy constructor
    - Move constructor
    - Destructor

The examples below demonstrate this.

-------------------------------------------------------------------------------
7) AGGREGATE INITIALIZATION
-------------------------------------------------------------------------------

Structs are often used as simple aggregates:

    struct IntPair
    {
        int _IntA{};
        int _IntB{};
    };

    IntPair P1{1, 2};

This style is very common with struct because its members are public by default.
But `struct` itself does NOT automatically mean "aggregate". A struct can stop
being an aggregate depending on its declarations, and a class can also satisfy
aggregate requirements if it follows the required C++ rules.

-------------------------------------------------------------------------------
8) WHICH ONE SHOULD I USE?
-------------------------------------------------------------------------------

A practical convention:

Use STRUCT when:
    - The type mainly groups related data.
    - Public data is intentional.
    - There is little or no invariant to protect.

Use CLASS when:
    - You want encapsulation.
    - Internal data should normally be private.
    - The object controls how its state changes.
    - You are modeling behavior as well as data.

Remember:

    These are conventions.
    The compiler mainly distinguishes them by DEFAULT ACCESS.

===============================================================================
EXAMPLES
===============================================================================
*/

#include <iostream>
#include <memory>
#include <string>
#include <utility>

using namespace std;

//=============================================================================
// Example 1: struct for simple grouped data
//=============================================================================

struct stPersonData
{
    string FirstName;
    string LastName;
};

//=============================================================================
// Example 2: class for encapsulated data
// Similar to the clsPerson examples from our previous lessons.
//=============================================================================

class clsPerson
{
private:
    int     _ID;
    string  _FirstName;
    string  _LastName;

public:
    clsPerson()
        : _ID(0), _FirstName(""), _LastName("")
    {
    }

    clsPerson(int ID, string FirstName, string LastName)
        : _ID(ID), _FirstName(FirstName), _LastName(LastName)
    {
    }

    int GetID() const
    {
        return (_ID);
    }

    string GetFirstName() const
    {
        return (_FirstName);
    }

    string GetLastName() const
    {
        return (_LastName);
    }

    string GetFullName() const
    {
        return (_FirstName + " " + _LastName);
    }
};

//=============================================================================
// Example 3: default member access
//=============================================================================

struct stPublicByDefault
{
    int Value;          // public by default
};

class clsPrivateByDefault
{
    int Value;          // private by default

public:
    void SetValue(int NewValue)
    {
        Value = NewValue;
    }

    int GetValue() const
    {
        return (Value);
    }
};

//=============================================================================
// Example 4: BOTH struct and class can use all access specifiers
//=============================================================================

struct stAccessExample
{
private:
    int _PrivateValue = 10;

protected:
    int _ProtectedValue = 20;

public:
    int PublicValue = 30;

    int GetPrivateValue() const
    {
        return (_PrivateValue);
    }
};

class clsAccessExample
{
private:
    int _PrivateValue = 100;

protected:
    int _ProtectedValue = 200;

public:
    int PublicValue = 300;

    int GetPrivateValue() const
    {
        return (_PrivateValue);
    }
};

//=============================================================================
// Example 5: constructors in a struct
// This proves that a struct is NOT limited to parameterized constructors.
//=============================================================================

struct stAddress
{
    string AddressLine1;
    string AddressLine2;
    string POBox;
    string ZipCode;

    // Default constructor
    stAddress()
        : AddressLine1(""), AddressLine2(""), POBox(""), ZipCode("")
    {
    }

    // Parameterized constructor
    stAddress(string Line1, string Line2, string PO, string Zip)
        : AddressLine1(Line1), AddressLine2(Line2), POBox(PO), ZipCode(Zip)
    {
    }

    // Copy constructor
    stAddress(const stAddress& Other)
        : AddressLine1(Other.AddressLine1), AddressLine2(Other.AddressLine2),
          POBox(Other.POBox), ZipCode(Other.ZipCode)
    {
    }

    // Move constructor
    stAddress(stAddress&& Other) noexcept
        : AddressLine1(move(Other.AddressLine1)),
          AddressLine2(move(Other.AddressLine2)),
          POBox(move(Other.POBox)),
          ZipCode(move(Other.ZipCode))
    {
    }

    // Destructor
    ~stAddress() = default;
};

//=============================================================================
// Example 6: a class can have the same constructor types
//=============================================================================

class clsNumber
{
private:
    int _Value;

public:
    clsNumber()
        : _Value(0)
    {
    }

    clsNumber(int Value)
        : _Value(Value)
    {
    }

    clsNumber(const clsNumber& Other)
        : _Value(Other._Value)
    {
    }

    clsNumber(clsNumber&& Other) noexcept
        : _Value(Other._Value)
    {
        Other._Value = 0;
    }

    ~clsNumber() = default;

    int GetValue() const
    {
        return (_Value);
    }
};

//=============================================================================
// Example 7: aggregate-style struct from our previous IntPair lesson
//=============================================================================

struct IntPair
{
    int _IntA{};
    int _IntB{};
};

//=============================================================================
// Example 8: default inheritance difference
//=============================================================================

class clsBase
{
protected:
    int _ProtectedValue = 20;

public:
    int PublicValue = 10;
};

// struct inheritance is PUBLIC by default.
struct stDerived : clsBase
{
    int GetProtectedValue() const
    {
        return (_ProtectedValue);
    }
};

// class inheritance is PRIVATE by default.
class clsDerivedPrivate : clsBase
{
public:
    int GetBasePublicValue() const
    {
        // Accessible INSIDE the derived class.
        return (PublicValue);
    }
};

// We can explicitly make class inheritance public.
class clsDerivedPublic : public clsBase
{
public:
    int GetProtectedValue() const
    {
        return (_ProtectedValue);
    }
};

//=============================================================================
// Example 9: both struct and class can have member functions
//=============================================================================

struct stRectangle
{
    double Width;
    double Height;

    double Area() const
    {
        return (Width * Height);
    }
};

class clsRectangle
{
private:
    double _Width;
    double _Height;

public:
    clsRectangle(double Width, double Height)
        : _Width(Width), _Height(Height)
    {
    }

    double Area() const
    {
        return (_Width * _Height);
    }
};

//=============================================================================
// Main
//=============================================================================

int main(void)
{
    cout << "\n============================================\n";
    cout << "1) Simple struct vs encapsulated class\n";
    cout << "============================================\n";

    stPersonData PersonData{"Alex", "John"};
    cout << "Struct Full Name : " << PersonData.FirstName << " "
         << PersonData.LastName << '\n';

    clsPerson Person1(10, "Alex", "John");
    cout << "Class Full Name  : " << Person1.GetFullName() << '\n';


    cout << "\n============================================\n";
    cout << "2) Default member access\n";
    cout << "============================================\n";

    stPublicByDefault S1;
    S1.Value = 50;                  // Works: public by default.
    cout << "Struct Value : " << S1.Value << '\n';

    clsPrivateByDefault C1;

    // C1.Value = 50;
    // ERROR: Value is private because class members are private by default.

    C1.SetValue(50);
    cout << "Class Value  : " << C1.GetValue() << '\n';


    cout << "\n============================================\n";
    cout << "3) Both can use private/protected/public\n";
    cout << "============================================\n";

    stAccessExample StructAccess;
    clsAccessExample ClassAccess;

    cout << "Struct private value through getter : "
         << StructAccess.GetPrivateValue() << '\n';
    cout << "Struct public value                 : "
         << StructAccess.PublicValue << '\n';

    cout << "Class private value through getter  : "
         << ClassAccess.GetPrivateValue() << '\n';
    cout << "Class public value                  : "
         << ClassAccess.PublicValue << '\n';


    cout << "\n============================================\n";
    cout << "4) Struct constructors\n";
    cout << "============================================\n";

    stAddress Address1;
    stAddress Address2("Main Street 1", "Apartment 2", "PO123", "3500");
    stAddress Address3(Address2);    // Copy constructor.
    stAddress Address4(move(Address3)); // Move constructor.

    cout << "Address2 ZipCode : " << Address2.ZipCode << '\n';
    cout << "Address4 ZipCode : " << Address4.ZipCode << '\n';


    cout << "\n============================================\n";
    cout << "5) Class constructors\n";
    cout << "============================================\n";

    clsNumber Number1;
    clsNumber Number2(42);
    clsNumber Number3(Number2);     // Copy constructor.
    clsNumber Number4(move(Number3)); // Move constructor.

    cout << "Number1 : " << Number1.GetValue() << '\n';
    cout << "Number2 : " << Number2.GetValue() << '\n';
    cout << "Number4 : " << Number4.GetValue() << '\n';


    cout << "\n============================================\n";
    cout << "6) Aggregate-style initialization\n";
    cout << "============================================\n";

    IntPair P1{1, 2};
    cout << "P1._IntA = " << P1._IntA << '\n';
    cout << "P1._IntB = " << P1._IntB << '\n';


    cout << "\n============================================\n";
    cout << "7) Default inheritance\n";
    cout << "============================================\n";

    stDerived StructDerived;

    // Works because `struct stDerived : clsBase` means PUBLIC inheritance.
    StructDerived.PublicValue = 100;
    cout << "StructDerived.PublicValue     : "
         << StructDerived.PublicValue << '\n';
    cout << "StructDerived protected value : "
         << StructDerived.GetProtectedValue() << '\n';

    clsDerivedPrivate ClassDerivedPrivate;
    cout << "ClassDerivedPrivate base value through member function : "
         << ClassDerivedPrivate.GetBasePublicValue() << '\n';

    // ClassDerivedPrivate.PublicValue = 100;
    // ERROR:
    // `class clsDerivedPrivate : clsBase` means PRIVATE inheritance by default,
    // therefore clsBase::PublicValue is not public through clsDerivedPrivate.

    clsDerivedPublic ClassDerivedPublic;

    // Works because we explicitly wrote `public clsBase`.
    ClassDerivedPublic.PublicValue = 200;
    cout << "ClassDerivedPublic.PublicValue : "
         << ClassDerivedPublic.PublicValue << '\n';


    cout << "\n============================================\n";
    cout << "8) Struct and class can BOTH have functions\n";
    cout << "============================================\n";

    stRectangle StructRectangle{5.0, 4.0};
    clsRectangle ClassRectangle(5.0, 4.0);

    cout << "Struct rectangle area : " << StructRectangle.Area() << '\n';
    cout << "Class rectangle area  : " << ClassRectangle.Area() << '\n';


    cout << "\n============================================\n";
    cout << "9) Stack/automatic storage vs heap/dynamic storage\n";
    cout << "============================================\n";

    // Automatic storage: BOTH work.
    stPersonData StackStruct{"Zain", "Orwa"};
    clsPerson StackClass(20, "Zain", "Orwa");

    cout << "Automatic struct : " << StackStruct.FirstName << '\n';
    cout << "Automatic class  : " << StackClass.GetFirstName() << '\n';

    // Dynamic storage: BOTH work.
    // Smart pointers are used here so memory is released automatically.
    unique_ptr<stPersonData> HeapStruct =
        make_unique<stPersonData>(stPersonData{"Dynamic", "Struct"});

    unique_ptr<clsPerson> HeapClass =
        make_unique<clsPerson>(30, "Dynamic", "Class");

    cout << "Dynamic struct : " << HeapStruct->FirstName << '\n';
    cout << "Dynamic class  : " << HeapClass->GetFirstName() << '\n';


    cout << "\n============================================\n";
    cout << "FINAL RULE\n";
    cout << "============================================\n";
    cout << "struct: public members + public inheritance by default\n";
    cout << "class : private members + private inheritance by default\n";
    cout << "Everything else is largely the same in C++.\n\n";

    return (0);
}
