/*
============================================================
34_Objects_and_Dynamic_Array.cpp
============================================================

MAIN IDEA
---------

This example shows how to create a DYNAMIC ARRAY OF OBJECTS
using the `new` keyword.

    clsA* arrA = new clsA[NumberOfObjects];

If:

    NumberOfObjects = 5;

then C++ allocates enough dynamic memory for 5 objects of clsA.

Conceptually:

                arrA
                  |
                  v

        Dynamic Memory (Heap)

    +----------+----------+----------+----------+----------+
    | arrA[0]  | arrA[1]  | arrA[2]  | arrA[3]  | arrA[4]  |
    | clsA obj | clsA obj | clsA obj | clsA obj | clsA obj |
    +----------+----------+----------+----------+----------+

IMPORTANT:
----------

This is DIFFERENT from:

    vector<clsA> v1;

An empty vector starts with ZERO clsA objects.

But:

    new clsA[5];

immediately creates 5 clsA objects.

Because C++ must create all 5 objects immediately, clsA needs
a constructor that can be called WITHOUT arguments:

    clsA() {}

That is why this example has a default ("dummy") constructor.


STEP 1
------

    clsA* arrA = new clsA[NumberOfObjects];

If NumberOfObjects = 5, C++ basically needs to create:

    arrA[0] -> clsA()
    arrA[1] -> clsA()
    arrA[2] -> clsA()
    arrA[3] -> clsA()
    arrA[4] -> clsA()

So the default constructor is called for every object.

At this moment, the objects already exist.


STEP 2
------

Then we run:

    arrA[i] = clsA(i);

Example when i = 2:

    arrA[2] = clsA(2);

First:

    clsA(2)

creates a TEMPORARY clsA object using the parameterized constructor.

The constructor does:

    x = 2;

Conceptually:

    temporary object
    +----------+
    | x = 2    |
    +----------+

Then:

    arrA[2] = temporary object;

assigns that object's data into the already-existing arrA[2].

So this line:

    arrA[i] = clsA(i);

does TWO main things:

    1. clsA(i)
       -> creates a temporary object using the parameterized constructor.

    2. arrA[i] = ...
       -> assigns that temporary object to an existing array object.


AFTER THE LOOP
--------------

The dynamic array looks conceptually like:

    arrA
     |
     v

    +-------+-------+-------+-------+-------+
    | x = 0 | x = 1 | x = 2 | x = 3 | x = 4 |
    +-------+-------+-------+-------+-------+
      [0]     [1]     [2]     [3]     [4]


THEN
----

    arrA[i].Print();

means:

    "Go to object number i in the dynamic array,
     then call that object's Print() member function."

For example:

    arrA[3].Print();

calls Print() for the object whose x is 3.


MEMORY
------

    clsA* arrA

is a POINTER variable.

The pointer itself is local to main().

The objects created with:

    new clsA[NumberOfObjects]

are stored in dynamically allocated memory.

Because we used `new[]`, we should release that memory with:

    delete[] arrA;


VERY IMPORTANT DIFFERENCE
-------------------------

vector example:

    vector<clsA> v1;

    -> creates the vector
    -> creates ZERO clsA elements initially


dynamic array example:

    clsA* arrA = new clsA[5];

    -> allocates dynamic memory
    -> immediately creates FIVE clsA objects
    -> therefore the default constructor is needed


SHORT VERSION
-------------

    new clsA[5]
        |
        +--> allocate memory for 5 clsA objects
        |
        +--> call clsA() five times

    arrA[i] = clsA(i)
        |
        +--> create temporary object with clsA(i)
        |
        +--> assign it into existing arrA[i]

============================================================
*/

#include <iostream>

using namespace std;

class clsA
{
public:

    // Default constructor.
    //
    // It is needed because:
    //
    //     new clsA[NumberOfObjects]
    //
    // creates all array objects immediately and C++ needs
    // to know how to construct each object without arguments.
    clsA()
    {
    }

    // Parameterized constructor.
    //
    // Example:
    //
    //     clsA(3)
    //
    // creates an object whose x becomes 3.
    clsA(int value)
    {
        x = value;
    }

    int x;

    void Print()
    {
        cout << "The value of x=" << x << endl;
    }
};


int main()
{
    short NumberOfObjects = 5;


    // ------------------------------------------------------
    // STEP 1: Allocate a dynamic array of clsA objects.
    // ------------------------------------------------------
    //
    // This allocates memory for 5 clsA objects on the heap.
    //
    // IMPORTANT:
    // The 5 objects are CREATED immediately.
    //
    // Therefore clsA() is called once for every array element.
    //
    // Conceptually:
    //
    // arrA
    //   |
    //   v
    //
    // +---------+---------+---------+---------+---------+
    // | clsA()  | clsA()  | clsA()  | clsA()  | clsA()  |
    // | arrA[0] | arrA[1] | arrA[2] | arrA[3] | arrA[4] |
    // +---------+---------+---------+---------+---------+
    //
    clsA* arrA = new clsA[NumberOfObjects];


    // ------------------------------------------------------
    // STEP 2: Give each object a value.
    // ------------------------------------------------------
    //
    // IMPORTANT:
    //
    // The objects arrA[0], arrA[1], ... ALREADY EXIST.
    //
    // This line:
    //
    //     arrA[i] = clsA(i);
    //
    // does not create the array slot.
    //
    // clsA(i) creates a temporary object, and then that
    // temporary object is assigned to arrA[i].
    //
    // Example for i = 2:
    //
    //     clsA(2)
    //        |
    //        v
    //   +----------+
    //   |  x = 2   |
    //   +----------+
    //      temporary
    //
    //          |
    //          | assignment
    //          v
    //
    //      arrA[2]
    //   +----------+
    //   |  x = 2   |
    //   +----------+
    //
    for (int i = 0; i < NumberOfObjects; i++)
    {
        arrA[i] = clsA(i);
    }


    // ------------------------------------------------------
    // STEP 3: Print every object's data.
    // ------------------------------------------------------
    //
    // arrA[i] gives us ONE clsA object.
    //
    // Therefore we can call:
    //
    //     arrA[i].Print();
    //
    // just like with any normal object.
    //
    for (int i = 0; i < NumberOfObjects; i++)
    {
        arrA[i].Print();
    }


    // ------------------------------------------------------
    // STEP 4: Release the dynamic memory.
    // ------------------------------------------------------
    //
    // Because the array was created using:
    //
    //     new clsA[...]
    //
    // we must release it using:
    //
    //     delete[] arrA;
    //
    delete[] arrA;

    // Optional safety habit:
    arrA = nullptr;


    system("pause>0");

    return 0;
}
