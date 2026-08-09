/*
===============================================================================
35_Objects_with_Parameterized_Constructor_and_Array.cpp
===============================================================================

SUBJECT
-------
Creating an array of objects when the class has a parameterized constructor.

The class in this example has:

    clsA(int value)
    {
        x = value;
    }

It does NOT have a default constructor:

    clsA() {}

That is important because every clsA object must receive an integer when
it is created.


===============================================================================
1. ONE NORMAL OBJECT
===============================================================================

If we write:

    clsA A1(10);

C++ calls:

    clsA(int value)

with:

    value = 10

Then the constructor executes:

    x = value;

So the object becomes:

    A1
    +----------+
    | x = 10   |
    +----------+


===============================================================================
2. ARRAY OF OBJECTS
===============================================================================

The main example uses:

    clsA obj[] = { clsA(10), clsA(20), clsA(30) };

This creates THREE clsA objects.

Conceptually:

                         obj

          index 0       index 1       index 2
             |             |             |
             v             v             v

        +----------+  +----------+  +----------+
        | clsA     |  | clsA     |  | clsA     |
        | x = 10   |  | x = 20   |  | x = 30   |
        +----------+  +----------+  +----------+

          obj[0]        obj[1]        obj[2]


Each expression calls the parameterized constructor:

    clsA(10)  -> creates object with x = 10
    clsA(20)  -> creates object with x = 20
    clsA(30)  -> creates object with x = 30


===============================================================================
3. WHY CAN WE LEAVE THE ARRAY SIZE EMPTY?
===============================================================================

We write:

    clsA obj[] = { clsA(10), clsA(20), clsA(30) };

instead of:

    clsA obj[3] = { clsA(10), clsA(20), clsA(30) };

Because C++ can count the initializer elements.

There are 3 objects in the initializer list, so the compiler knows:

    array size = 3


===============================================================================
4. WHY DOES THIS WORK WITHOUT A DEFAULT CONSTRUCTOR?
===============================================================================

This works:

    clsA obj[] = { clsA(10), clsA(20), clsA(30) };

because every array element is told exactly how to be constructed:

    obj[0] -> clsA(10)
    obj[1] -> clsA(20)
    obj[2] -> clsA(30)

C++ never needs to call:

    clsA()

for these elements.


But this would NOT compile with the current class:

    clsA obj[3];

Why?

Because C++ would need to create:

    obj[0] -> clsA()
    obj[1] -> clsA()
    obj[2] -> clsA()

and clsA() does not exist.

The only constructor available is:

    clsA(int value)

So C++ would need values:

    clsA( ? )
    clsA( ? )
    clsA( ? )

but none were provided.


===============================================================================
5. EACH ARRAY ELEMENT IS A COMPLETE OBJECT
===============================================================================

obj is not an array of integers.

It is an array of clsA objects.

Therefore:

    obj[0]

is one complete clsA object.

    obj[1]

is another complete clsA object.

    obj[2]

is another complete clsA object.


That means we can access object members:

    obj[0].x

or call object methods:

    obj[0].Print();


For example:

    obj[1].Print();

means:

    Go to object at index 1
    then call that object's Print() method.

Since:

    obj[1].x = 20

the output is:

    The value of x = 20


===============================================================================
6. WHAT THE LOOP DOES
===============================================================================

The example uses:

    for (int i = 0; i < 3; i++)
    {
        obj[i].Print();
    }

Iteration by iteration:

    i = 0
        obj[0].Print()
        prints x = 10

    i = 1
        obj[1].Print()
        prints x = 20

    i = 2
        obj[2].Print()
        prints x = 30


So the final output is:

    The value of x = 10
    The value of x = 20
    The value of x = 30


===============================================================================
7. CREATION VS ASSIGNMENT
===============================================================================

This example is different from the previous dynamic-array pattern:

    clsA* arrA = new clsA[5];

followed by:

    arrA[i] = clsA(i);


In that earlier pattern:

    new clsA[5]

first creates 5 objects using the default constructor.

Then:

    arrA[i] = clsA(i);

creates another object and ASSIGNS it to an object that already exists.


In THIS example:

    clsA obj[] = { clsA(10), clsA(20), clsA(30) };

the objects receive their constructor values as the array itself is created.

So:

    clsA obj[] = { ... };

is INITIALIZATION of the array objects.

It is not the same as first creating empty/default objects and then
assigning values later.


===============================================================================
8. MEMORY
===============================================================================

This array:

    clsA obj[] = { clsA(10), clsA(20), clsA(30) };

is a normal local array inside main().

It is NOT created with:

    new

Therefore we do NOT write:

    delete[] obj;

Its lifetime is automatic.

When main() finishes, the array objects are destroyed automatically.


===============================================================================
9. A SHORTER FORM
===============================================================================

The explicit form used in this lesson is:

    clsA obj[] = { clsA(10), clsA(20), clsA(30) };

It clearly shows that the constructor is being used.

C++ can also initialize these objects more compactly as:

    clsA obj[] = { 10, 20, 30 };

Each number can be used to construct one clsA object through:

    clsA(int value)

But the explicit form is kept in this example because it makes the
constructor calls easier to see while learning.


===============================================================================
10. MAIN IDEA TO REMEMBER
===============================================================================

    clsA obj[] = { clsA(10), clsA(20), clsA(30) };

means:

    "Create an array of clsA objects, and construct each object with
     the value provided for that position."

So after creation:

    obj[0].x == 10
    obj[1].x == 20
    obj[2].x == 30

And because every obj[i] is a clsA object:

    obj[i].Print();

calls the Print() method on that specific object.

===============================================================================
*/

#include <iostream>

using namespace std;


class clsA
{
public:

    // Parameterized Constructor
    //
    // Every clsA object must receive an integer when it is created.
    //
    // Example:
    //
    //     clsA(10)
    //
    // calls this constructor with value = 10,
    // then stores 10 inside x.
    //
    clsA(int value)
    {
        x = value;
    }


    int x;


    void Print()
    {
        cout << "The value of x = " << x << endl;
    }
};


int main(void)
{
    // ------------------------------------------------------------------------
    // Create and initialize 3 clsA objects.
    // ------------------------------------------------------------------------
    //
    // obj[0] is constructed using clsA(10)
    // obj[1] is constructed using clsA(20)
    // obj[2] is constructed using clsA(30)
    //
    // Since every object gets its required constructor argument,
    // we do NOT need a default constructor.
    //
    // The compiler also determines the array size automatically: 3.
    //
    clsA obj[] = { clsA(10), clsA(20), clsA(30) };


    // ------------------------------------------------------------------------
    // Loop through the array of objects.
    // ------------------------------------------------------------------------
    //
    // obj[i] is a complete clsA object.
    //
    // Therefore we can call:
    //
    //     obj[i].Print();
    //
    for (int i = 0; i < 3; i++)
    {
        obj[i].Print();
    }


    // ------------------------------------------------------------------------
    // The loop above is equivalent to:
    // ------------------------------------------------------------------------
    //
    // obj[0].Print();
    // obj[1].Print();
    // obj[2].Print();
    //


    return 0;
}
