# 10 — Static Members in C++

> **Main idea:** A normal data member belongs to **each individual object**, while a static data member belongs to the **class itself** and is shared by every object of that class.

---

## 📌 The Example Used in This Lesson

```cpp
#include <iostream>

using namespace std;

class clsA
{
private:

public:
    int Var;
    static int counter;

    clsA()
    {
        counter++;
    }

    void Print()
    {
        cout << "\nVar     = " << Var << endl;
        cout << "Counter = " << counter << endl;
    }
};

int clsA::counter = 0; // Define and initialize the static variable.

int main(void)
{
    clsA A1, A2, A3, A4;

    A1.Var = 10;
    A2.Var = 20;
    A3.Var = 30;
    A4.Var = 40;

    A1.Print();

    // Changing the shared static variable changes the value seen
    // through every object of the class.
    clsA::counter = 1000;

    A1.Print();

    return (0);
}
```

### Program output

```text
Var     = 10
Counter = 4

Var     = 10
Counter = 1000
```

---

# 1. What Is a Static Data Member?

A **static data member** is a variable declared inside a class using the keyword `static`.

```cpp
static int counter;
```

It is connected to the class, but it is **not copied into every object**.

Only **one shared variable** named `counter` exists, regardless of how many `clsA` objects are created.

```text
clsA objects:

A1 ─────┐
A2 ─────┼────> one shared clsA::counter
A3 ─────┤
A4 ─────┘
```

By contrast, the normal member `Var` exists separately inside every object.

```text
A1 owns its own Var = 10
A2 owns its own Var = 20
A3 owns its own Var = 30
A4 owns its own Var = 40

The class owns one shared counter = 4
```

---

# 2. The Simplest Analogy: Students and a Classroom Whiteboard

Imagine that `clsA` represents students in one classroom.

Each student has a **private notebook**, but the classroom has only **one shared whiteboard**.

```text
Student A1 notebook: Var = 10
Student A2 notebook: Var = 20
Student A3 notebook: Var = 30
Student A4 notebook: Var = 40

Classroom whiteboard: counter = 4
```

- `Var` is like each student's notebook.
- `counter` is like the classroom's shared whiteboard.

When A1 changes its notebook, A2's notebook does not change.

```cpp
A1.Var = 100;
```

Only `A1.Var` changes.

However, when the shared whiteboard is changed:

```cpp
clsA::counter = 1000;
```

all students see the same new value because there is only one whiteboard.

> It is not that four copies of `counter` are all updated. There are **no four copies**. There is only **one shared variable**.

---

# 3. Normal Member vs Static Member

| Feature                         | Normal data member (`Var`)       | Static data member (`counter`)         |
|---------------------------------|----------------------------------|----------------------------------------|
| Belongs to                      | Each object                      | The class                              |
| Number of copies                | One copy per object              | One copy for the entire class          |
| Accessed through an object      | Yes                              | Yes, if access allows it               |
| Accessed through class name     | No                               | Yes                                    |
| Included inside each object     | Yes                              | No                                     |
| Exists without an object        | No                               | Yes                                    |
| Shared between objects          | No                               | Yes                                    |
| Typical use                     | Object-specific state            | Class-wide state or object counting    |

---

# 4. What Happens When the Objects Are Created?

This line creates four different objects:

```cpp
clsA A1, A2, A3, A4;
```

The constructor runs once for every object.

```cpp
clsA()
{
    counter++;
}
```

Because four objects are constructed, the constructor runs four times.

```text
Initial value: counter = 0

Create A1  → constructor runs → counter = 1
Create A2  → constructor runs → counter = 2
Create A3  → constructor runs → counter = 3
Create A4  → constructor runs → counter = 4
```

Therefore, after this line:

```cpp
clsA A1, A2, A3, A4;
```

we have:

```text
clsA::counter == 4
```

---

# 5. Why Does `A1.Print()` Show `Counter = 4`?

The function is called through `A1`:

```cpp
A1.Print();
```

Inside `Print()`:

```cpp
cout << "\nVar     = " << Var << endl;
cout << "Counter = " << counter << endl;
```

The two names do not refer to the same kind of storage.

```text
Var      → A1's own normal member
counter  → the one shared clsA member
```

So the first call prints:

```text
Var     = 10
Counter = 4
```

It prints `10` because `A1.Var` is `10`.

It prints `4` because four `clsA` objects have been created.

---

# 6. Every Object Has Its Own `Var`

These assignments modify four different variables:

```cpp
A1.Var = 10;
A2.Var = 20;
A3.Var = 30;
A4.Var = 40;
```

A visual representation is:

```text
A1 object
└── Var = 10

A2 object
└── Var = 20

A3 object
└── Var = 30

A4 object
└── Var = 40
```

Changing one normal member does not affect the others.

```cpp
A1.Var = 500;
```

The result would be:

```text
A1.Var = 500
A2.Var = 20
A3.Var = 30
A4.Var = 40
```

## ⚠️ `Var` Must Be Given a Value Before It Is Read

In the original class, `Var` is declared without an initial value:

```cpp
int Var;
```

For a normal local object such as `A1`, that integer does not automatically receive a reliable value. Your program is safe because every object's `Var` is assigned before `Print()` reads it:

```cpp
A1.Var = 10;
A2.Var = 20;
A3.Var = 30;
A4.Var = 40;
```

Without an assignment, this would be incorrect:

```cpp
clsA A1;
A1.Print(); // Var is read before receiving a value.
```

A simple improvement is default member initialization:

```cpp
int Var{}; // Initializes Var to 0.
```

Or initialize it through the constructor:

```cpp
clsA(int Value)
    : Var(Value)
{
    counter++;
}
```

---

# 7. Every Object Shares the Same `counter`

The static member is declared here:

```cpp
static int counter;
```

Only one `counter` exists:

```text
clsA::counter = 4
```

You can access it through different objects when it is public:

```cpp
cout << A1.counter << endl;
cout << A2.counter << endl;
cout << A3.counter << endl;
cout << A4.counter << endl;
```

All four expressions refer to the same variable.

```text
A1.counter ──┐
A2.counter ──┼──> clsA::counter
A3.counter ──┤
A4.counter ──┘
```

Therefore:

```cpp
A1.counter = 50;
```

would make all of these print `50`:

```cpp
cout << A1.counter;
cout << A2.counter;
cout << A3.counter;
cout << A4.counter;
cout << clsA::counter;
```

Again, five separate variables are not being changed. All five expressions access the **same single variable**.

---

# 8. Why Are Static Members Called Shared Members?

Some explanations call static data members **shared members** because every object uses the same class-level storage.

```text
Normal member:

A1.Var        A2.Var        A3.Var        A4.Var
  10            20            30            40

Static member:

A1 ─┐
A2 ─┼──> counter = 4
A3 ─┤
A4 ─┘
```

The official C++ term is **static data member**. “Shared member” describes its behavior but is not the C++ keyword.

---

# 9. Why Use `clsA::counter`?

The recommended way to access a public static member is through the class name:

```cpp
clsA::counter = 1000;
```

The syntax is:

```text
ClassName::StaticMemberName
```

The `::` operator is called the **scope-resolution operator**.

It tells C++:

```text
Find counter inside the scope of clsA.
```

This style clearly communicates that `counter` belongs to the class, not to a particular object.

### Less clear

```cpp
A1.counter = 1000;
```

### Clearer and preferred

```cpp
clsA::counter = 1000;
```

Both work in the current example because `counter` is public, but the second form better expresses the design.

---

# 10. Why Does Changing `clsA::counter` Affect Every Object?

The line:

```cpp
clsA::counter = 1000;
```

replaces the shared value `4` with `1000`.

Before the assignment:

```text
clsA::counter = 4
```

After the assignment:

```text
clsA::counter = 1000
```

Now any object that reads `counter` sees `1000`.

```cpp
A1.Print();
A2.Print();
A3.Print();
A4.Print();
```

Each object would print its own `Var`, but every object would print the same counter:

```text
A1: Var = 10, Counter = 1000
A2: Var = 20, Counter = 1000
A3: Var = 30, Counter = 1000
A4: Var = 40, Counter = 1000
```

---

# 11. Does a Static Member Have to Be Public?

## ❌ No

A static data member does **not** have to be public.

It can be:

```cpp
private
protected
public
```

The normal access-control rules still apply.

| Access level | Who can access the static member directly?                         |
|--------------|--------------------------------------------------------------------|
| `private`    | Only the class and its friends                                     |
| `protected`  | The class, its friends, and derived classes                        |
| `public`     | Any code with access to the class                                  |

The word `static` controls **ownership and storage**.

The words `private`, `protected`, and `public` control **accessibility**.

These are two separate ideas.

```text
static  → Who owns this member?
public  → Who is allowed to access it?
```

---

# 12. Public Static Member: Easy but Less Protected

Your current example declares `counter` as public:

```cpp
public:
    static int counter;
```

This allows code outside the class to change it directly:

```cpp
clsA::counter = 1000;
```

That is useful for learning, but it allows any part of the program to assign any value:

```cpp
clsA::counter = -500;
```

That could destroy the meaning of an object counter.

---

# 13. Better Design: Keep the Counter Private

A safer version keeps the static variable private and provides a public function for reading it.

```cpp
#include <iostream>

using namespace std;

class clsA
{
private:
    int Var;
    static int counter;

public:
    clsA(int Value)
        : Var(Value)
    {
        counter++;
    }

    static int GetCounter()
    {
        return counter;
    }

    void Print() const
    {
        cout << "Var     = " << Var << endl;
        cout << "Counter = " << counter << endl;
    }
};

int clsA::counter = 0;

int main(void)
{
    clsA A1(10);
    clsA A2(20);
    clsA A3(30);
    clsA A4(40);

    A1.Print();

    cout << "Number of objects = "
         << clsA::GetCounter() << endl;

    return (0);
}
```

Now outside code can read the number of constructed objects:

```cpp
clsA::GetCounter();
```

but cannot directly write:

```cpp
clsA::counter = 1000; // Error: counter is private.
```

> **Encapsulation principle:** Keep internal data private unless outside code genuinely needs direct access to it.

---

# 14. Declaration vs Definition of a Static Data Member

Inside the class, this line is normally a **declaration**:

```cpp
static int counter;
```

It tells the compiler:

```text
clsA has a static integer member named counter.
```

However, the program still needs one actual definition that creates storage for the variable.

That definition is written outside the class:

```cpp
int clsA::counter = 0;
```

This line does three jobs:

1. It identifies the type: `int`.
2. It identifies the owner: `clsA::`.
3. It gives the initial value: `0`.

```text
int        clsA::        counter       = 0;
│          │             │               │
Type       Owner         Member name     Initial value
```

---

# 15. Why Define It Outside the Class?

Before C++17's inline variables, the usual design separated two responsibilities:

### Inside the class

Describe that the member exists:

```cpp
static int counter;
```

### Outside the class

Create exactly one storage location:

```cpp
int clsA::counter = 0;
```

This prevents each object from creating its own copy and gives the linker one concrete definition of the class-wide variable.

A useful analogy is a company blueprint:

```text
Inside the class:
“The company has one employee counter.”

Outside the class:
“Here is the real employee counter, beginning at zero.”
```

---

# 16. What Happens If the Outside Definition Is Missing?

Consider:

```cpp
class clsA
{
public:
    static int counter;
};

int main()
{
    clsA::counter = 10;
}
```

The class declares `counter`, but no storage definition is supplied.

The compiler may accept the declaration, but the linker will usually report an error similar to:

```text
undefined reference to clsA::counter
```

The missing line is:

```cpp
int clsA::counter = 0;
```

---

# 17. C++17 Alternative: `inline static`

Since C++17, a static data member can be declared and defined directly inside the class with `inline static`.

```cpp
class clsA
{
public:
    inline static int counter = 0;
};
```

Now this outside definition is not needed:

```cpp
int clsA::counter = 0; // Do not add this as well.
```

## Traditional form

```cpp
class clsA
{
public:
    static int counter;
};

int clsA::counter = 0;
```

## C++17 form

```cpp
class clsA
{
public:
    inline static int counter = 0;
};
```

| Form                          | Definition location | Requires C++17? |
|-------------------------------|---------------------|-----------------|
| `static int counter;`         | Outside class       | No              |
| `inline static int counter=0` | Inside class        | Yes             |

Your original example uses the traditional and fully valid form.

---

# 18. Static Data Exists Even When Accessed Without an Object

A static member belongs to the class, so no object is required to access it when it is public.

```cpp
cout << clsA::counter << endl;
```

This can be done even before creating an object:

```cpp
int main()
{
    cout << clsA::counter << endl; // 0

    clsA A1;

    cout << clsA::counter << endl; // 1
}
```

The normal member `Var` is different.

This is invalid:

```cpp
cout << clsA::Var; // Error
```

Why?

Because `Var` does not belong to the class as one shared variable. It belongs to a specific object.

You must choose an object:

```cpp
cout << A1.Var;
```

---

# 19. Static Members Are Not Stored Inside Every Object

Conceptually, each object contains its normal non-static data members:

```text
A1 object: [ Var ]
A2 object: [ Var ]
A3 object: [ Var ]
A4 object: [ Var ]
```

The static member is stored separately:

```text
Class-wide storage: [ clsA::counter ]
```

Therefore, adding a static data member does not create one additional `counter` inside every object.

> Exact object size can also include padding and alignment, but the static data member itself is not part of each object's stored state.

---

# 20. Lifetime of a Static Data Member

A local variable normally begins its life when execution enters its block and ends when execution leaves that block.

A static data member has **static storage duration**.

In a normal program, it exists for the entire program execution:

```text
Program starts
     ↓
clsA::counter exists
     ↓
Objects are created and destroyed
     ↓
Program ends
     ↓
clsA::counter stops existing
```

The member can therefore keep class-wide information across many object creations.

---

# 21. Important Limitation in the Original Counter

Your constructor increases the counter:

```cpp
clsA()
{
    counter++;
}
```

This counts how many objects have been **constructed so far**.

It does not automatically count how many objects are **currently alive**, because it is never decreased.

Example:

```cpp
{
    clsA A1;
    clsA A2;
} // A1 and A2 are destroyed here.
```

After the block, both objects are gone, but the counter remains `2` unless the destructor decreases it.

---

# 22. Counting Objects That Are Currently Alive

To track currently living objects, increment in the constructor and decrement in the destructor.

```cpp
class clsA
{
private:
    inline static int liveObjects = 0;

public:
    clsA()
    {
        liveObjects++;
    }

    ~clsA()
    {
        liveObjects--;
    }

    static int GetLiveObjects()
    {
        return liveObjects;
    }
};
```

Execution example:

```cpp
cout << clsA::GetLiveObjects() << endl; // 0

{
    clsA A1;
    clsA A2;

    cout << clsA::GetLiveObjects() << endl; // 2
}

cout << clsA::GetLiveObjects() << endl; // 0
```

## Visual flow

```text
Start                 liveObjects = 0
Construct A1          liveObjects = 1
Construct A2          liveObjects = 2
Destroy A2            liveObjects = 1
Destroy A1            liveObjects = 0
```

---

# 23. Copy Construction Can Also Affect an Object Counter

Suppose an object is copied:

```cpp
clsA A1;
clsA A2 = A1;
```

`A2` is a new object, so a true live-object counter should also increase when the copy constructor runs.

A more complete teaching example is:

```cpp
class clsA
{
private:
    inline static int liveObjects = 0;

public:
    clsA()
    {
        liveObjects++;
    }

    clsA(const clsA& Other)
    {
        (void)Other;
        liveObjects++;
    }

    ~clsA()
    {
        liveObjects--;
    }

    static int GetLiveObjects()
    {
        return liveObjects;
    }
};
```

This matters because constructors include more than only the default constructor.

## What the Compiler-Generated Copy Constructor Does Here

In the original class, C++ can generate a copy constructor automatically:

```cpp
clsA A1;
A1.Var = 10;

clsA A2 = A1;
```

The compiler-generated copy constructor copies the normal member `Var` from `A1` into `A2`. It does **not** copy `counter` into the object because `counter` is static and is not stored inside either object.

It also does not execute your default constructor body:

```cpp
clsA()
{
    counter++;
}
```

Therefore, the original counter would not increase for `A2` when `A2` is copy-constructed. If the purpose is to count every object construction, define an appropriate copy constructor and increment the counter there as shown above.

> **Important:** A default constructor and a copy constructor are different constructors. Copy construction does not first run the default constructor and then copy the object.

---

# 24. What Is a Static Member Function?

A class can also have a **static member function**.

```cpp
static int GetCounter()
{
    return counter;
}
```

A static member function belongs to the class and can be called without an object:

```cpp
cout << clsA::GetCounter() << endl;
```

This is useful when a function works only with class-wide information.

---

# 25. Static Member Functions Have No `this` Pointer

A normal non-static member function is called for a particular object:

```cpp
A1.Print();
```

Inside `Print()`, C++ knows which object is being used through an implicit pointer called `this`.

A static member function is not called for one particular object:

```cpp
clsA::GetCounter();
```

Therefore, it has no `this` pointer.

It can directly access static members:

```cpp
static int GetCounter()
{
    return counter; // Valid
}
```

But it cannot directly access a normal member such as `Var`:

```cpp
static void WrongFunction()
{
    cout << Var; // Error
}
```

Why?

Because the class may have many objects, each with a different `Var`.

```text
A1.Var = 10
A2.Var = 20
A3.Var = 30
A4.Var = 40

Which Var should the static function use?
```

No object was specified, so C++ cannot choose one.

---

# 26. Correct Ways for a Static Function to Work With Object Data

A static function can receive an object explicitly:

```cpp
class clsA
{
public:
    int Var;

    static void PrintObjectVar(const clsA& Object)
    {
        cout << Object.Var << endl;
    }
};
```

Call:

```cpp
clsA A1;
A1.Var = 10;

clsA::PrintObjectVar(A1);
```

Now the function knows exactly which object's `Var` to use.

---

# 27. Common Uses of Static Members

Static members are useful for information or behavior that belongs to the class as a whole.

| Use case                         | Example                                             |
|----------------------------------|-----------------------------------------------------|
| Count constructed objects        | `static int totalCreated;`                          |
| Count currently alive objects    | `static int liveObjects;`                           |
| Give every object a unique ID    | `static int nextId;`                                |
| Store a class-wide limit         | `static int maxUsers;`                              |
| Hold shared configuration        | `static bool loggingEnabled;`                       |
| Provide class utilities          | `static bool IsValid(...);`                         |
| Create shared constants          | `inline static constexpr int MaxSize = 100;`        |

---

# 28. Example: Giving Every Object a Unique ID

A static member can provide the next available ID.

```cpp
#include <iostream>

using namespace std;

class clsUser
{
private:
    inline static int nextId = 1;
    int id;

public:
    clsUser()
        : id(nextId)
    {
        nextId++;
    }

    int GetId() const
    {
        return id;
    }
};

int main()
{
    clsUser User1;
    clsUser User2;
    clsUser User3;

    cout << User1.GetId() << endl; // 1
    cout << User2.GetId() << endl; // 2
    cout << User3.GetId() << endl; // 3
}
```

Each object has its own `id`, but all objects share `nextId`.

```text
Shared nextId begins at 1

Create User1 → User1.id = 1 → nextId becomes 2
Create User2 → User2.id = 2 → nextId becomes 3
Create User3 → User3.id = 3 → nextId becomes 4
```

---

# 29. Common Mistake: Thinking Each Object Has Its Own Static Copy

## ❌ Wrong understanding

```text
A1.counter = 1
A2.counter = 1
A3.counter = 1
A4.counter = 1
```

This would describe four separate counters, but that is not what `static` creates.

## ✅ Correct understanding

```text
A1 ─┐
A2 ─┼──> one counter = 4
A3 ─┤
A4 ─┘
```

---

# 30. Common Mistake: Believing `A1.counter` Belongs to A1

This syntax is allowed when the static member is public:

```cpp
A1.counter
```

But it can create the false impression that `counter` belongs to `A1`.

It does not.

The clearer syntax is:

```cpp
clsA::counter
```

Use the class name for static members whenever possible.

---

# 31. Common Mistake: Making Shared State Public Without a Reason

## Less safe

```cpp
class clsA
{
public:
    static int counter;
};
```

Any code can modify the counter:

```cpp
clsA::counter = -900;
```

## Safer

```cpp
class clsA
{
private:
    inline static int counter = 0;

public:
    static int GetCounter()
    {
        return counter;
    }
};
```

Outside code can inspect the value without freely corrupting it.

---

# 32. Common Mistake: Defining the Static Member More Than Once

With the traditional form, the static member should have one definition in the program:

```cpp
int clsA::counter = 0;
```

If the same non-inline definition appears in multiple `.cpp` files, the linker can report a multiple-definition error.

A common multi-file structure is:

## `clsA.h`

```cpp
#ifndef CLSA_H
#define CLSA_H

class clsA
{
public:
    static int counter;
};

#endif
```

## `clsA.cpp`

```cpp
#include "clsA.h"

int clsA::counter = 0;
```

## `main.cpp`

```cpp
#include <iostream>
#include "clsA.h"

int main()
{
    std::cout << clsA::counter << '\n';
}
```

The declaration belongs in the header, while the one traditional definition belongs in one `.cpp` file.

---

# 33. An Improved Version of Your Original Example

This version keeps the same learning goal but uses encapsulation, initialization lists, `const`, and a static getter.

```cpp
#include <iostream>

using namespace std;

class clsA
{
private:
    int Var;
    inline static int counter = 0;

public:
    clsA(int Value)
        : Var(Value)
    {
        counter++;
    }

    int GetVar() const
    {
        return Var;
    }

    static int GetCounter()
    {
        return counter;
    }

    void Print() const
    {
        cout << "\nVar     = " << Var << endl;
        cout << "Counter = " << counter << endl;
    }
};

int main(void)
{
    clsA A1(10);
    clsA A2(20);
    clsA A3(30);
    clsA A4(40);

    A1.Print();

    cout << "\nTotal objects constructed = "
         << clsA::GetCounter() << endl;

    return (0);
}
```

### Why this version is stronger

| Improvement                       | Benefit                                              |
|-----------------------------------|------------------------------------------------------|
| `Var` is private                  | Protects object state                                |
| Constructor receives the value    | Object begins in a valid initialized state           |
| Initialization list is used       | Initializes `Var` directly                           |
| `counter` is private              | Outside code cannot corrupt it                       |
| `GetCounter()` is static          | Reads class-wide data without requiring an object    |
| `Print()` is `const`              | Promises not to modify the object                     |
| `inline static` is used           | C++17 definition can remain inside the class         |

---

# 34. Full Execution Flow of Your Original Program

## Step 1 — Program starts

The static member has already been initialized:

```text
clsA::counter = 0
```

## Step 2 — Four objects are created

```cpp
clsA A1, A2, A3, A4;
```

The constructor executes four times:

```text
After A1: counter = 1
After A2: counter = 2
After A3: counter = 3
After A4: counter = 4
```

## Step 3 — Each object's own `Var` is assigned

```text
A1.Var = 10
A2.Var = 20
A3.Var = 30
A4.Var = 40
```

## Step 4 — `A1.Print()` runs

```text
A1.Var          = 10
clsA::counter   = 4
```

Output:

```text
Var     = 10
Counter = 4
```

## Step 5 — The shared member is changed

```cpp
clsA::counter = 1000;
```

Now:

```text
clsA::counter = 1000
```

## Step 6 — `A1.Print()` runs again

`A1.Var` was not changed, so it remains `10`.

The shared counter is now `1000`.

Output:

```text
Var     = 10
Counter = 1000
```

---

# 35. Final Memory Picture

```text
                     CLASS-WIDE STORAGE
                ┌────────────────────────┐
                │ clsA::counter = 1000   │
                └────────────────────────┘
                    ▲       ▲       ▲       ▲
                    │       │       │       │

┌────────────────┐  │  ┌────────────────┐  │
│ A1             │──┘  │ A2             │──┘
│ Var = 10       │     │ Var = 20       │
└────────────────┘     └────────────────┘

┌────────────────┐     ┌────────────────┐
│ A3             │     │ A4             │
│ Var = 30       │     │ Var = 40       │
└────────────────┘     └────────────────┘
        │                       │
        └──── access the same ──┘
              shared counter
```

---

# Advanced Note: `counter++` and Multiple Threads

In a program where multiple threads create objects at the same time, a plain operation such as:

```cpp
counter++;
```

is not automatically safe because it performs a read, a modification, and a write. For a beginner single-threaded program, the current code is fine. A multithreaded design may require synchronization or an atomic counter.

This is an advanced concern and does not change the basic static-member rules explained above.

---

# Do Not Confuse Class Static Members With Local Static Variables

The keyword `static` can be used in other contexts. This lesson focuses on members declared inside a class:

```cpp
class clsA
{
    static int counter;
};
```

A local static variable is different:

```cpp
void Function()
{
    static int calls = 0;
    calls++;
}
```

The local variable `calls` belongs to the function scope and keeps its value between calls. It is not a class member.

---

# 36. Key Rules to Remember

1. A normal data member belongs to each individual object.
2. A static data member belongs to the class.
3. Only one copy of a static data member exists for the class.
4. All objects access the same static value.
5. Prefer `ClassName::member` when accessing a static member.
6. A static member does not have to be public.
7. Traditional static members need one outside definition.
8. Since C++17, `inline static` can define the member inside the class.
9. A static member function has no `this` pointer.
10. A static member function cannot directly use non-static object data.
11. Incrementing only in the constructor counts constructions, not necessarily currently living objects.
12. Shared mutable data should usually be private and controlled through class functions.

---

# 37. Quick Questions

## Question 1

How many copies of `Var` exist after creating `A1`, `A2`, `A3`, and `A4`?

<details>
<summary>Answer</summary>

Four copies exist—one inside each object.

</details>

## Question 2

How many copies of `counter` exist?

<details>
<summary>Answer</summary>

Only one class-wide copy exists.

</details>

## Question 3

Why does `counter` become `4`?

<details>
<summary>Answer</summary>

Four objects are constructed, and each constructor call executes `counter++`.

</details>

## Question 4

Does `A1.counter = 50;` change only A1's counter?

<details>
<summary>Answer</summary>

No. `counter` is static, so there is only one shared variable. Every object will observe `50`.

</details>

## Question 5

Must a static data member be public?

<details>
<summary>Answer</summary>

No. It can be private, protected, or public.

</details>

## Question 6

What does this line do?

```cpp
int clsA::counter = 0;
```

<details>
<summary>Answer</summary>

It defines the class's static integer member, creates its storage, and initializes it to zero.

</details>

## Question 7

Can a static member function directly print `Var`?

<details>
<summary>Answer</summary>

No. `Var` belongs to a particular object, and a static function has no `this` pointer identifying an object.

</details>

## Question 8

What is the clearest way to access the shared counter?

<details>
<summary>Answer</summary>

```cpp
clsA::counter
```

Using the class name shows that the member belongs to the class.

</details>

---

# 38. One-Sentence Summary

> A static member creates one class-owned value shared by all objects, while a normal member creates a separate value inside every object.
