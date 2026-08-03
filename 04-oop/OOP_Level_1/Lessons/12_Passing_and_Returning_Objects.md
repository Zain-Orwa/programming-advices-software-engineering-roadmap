# C++ Method Design: Passing and Returning Objects

> **Topic:** Passing objects to class methods and returning a new object  
> **Example class:** `Distance`  
> **Main idea:** One `Distance` object can receive another `Distance` object, combine their values, and return a third `Distance` object.

---

## 🎯 What We Want to Build

We have two objects:

```text
d1
├── Feet   = 5
└── Inches = 3.5

d2
├── Feet   = 3
└── Inches = 4.25
```

We want to add them:

```text
d1 + d2
```

The result should be another `Distance` object:

```text
result
├── Feet   = 8
└── Inches = 7.75
```

The method call will look like this:

```cpp
Distance result = d1.AddDistance(d2);
```

---

# 1. Understanding the Method Declaration

```cpp
Distance AddDistance(const Distance& other) const;
```

Let us separate every part:

```text
Distance        AddDistance        (const Distance& other)        const
   │                 │                        │                       │
   │                 │                        │                       └── Does not modify d1
   │                 │                        │
   │                 │                        └── Receives another Distance object
   │                 │
   │                 └── Function name
   │
   └── Returns a Distance object
```

| Part                    | Meaning                                                        |
|-------------------------|----------------------------------------------------------------|
| `Distance`              | The function returns a complete `Distance` object.             |
| `AddDistance`           | The name of the member function.                               |
| `const Distance& other` | Receives another object without copying or changing it.        |
| Final `const`           | Promises not to modify the object that called the function.    |

---

# 2. Which Object Is Which?

Consider this call:

```cpp
Distance result = d1.AddDistance(d2);
```

Inside `AddDistance()`:

```text
d1     → the current/calling object
d2     → the argument object
result → the new object returned by the method
```

The method can access `d1` directly:

```cpp
_Feet
_Inches
```

It accesses the passed object through its parameter name:

```cpp
other._Feet
other._Inches
```

Therefore:

```cpp
_Feet + other._Feet
```

means:

```text
d1._Feet + d2._Feet
```

---

# 3. Visual Execution Flow

The call:

```cpp
Distance result = d1.AddDistance(d2);
```

works like this:

```text
┌──────────────────────┐
│ d1                   │
│ _Feet   = 5          │
│ _Inches = 3.5        │
└──────────┬───────────┘
           │ calls AddDistance()
           │ passes d2 as "other"
           ▼
┌─────────────────────────────────────────────┐
│ AddDistance(const Distance& other)          │
│                                             │
│ current object: d1                          │
│ other object:   d2                          │
│                                             │
│ newFeet   = 5   + 3    = 8                  │
│ newInches = 3.5 + 4.25 = 7.75               │
└───────────────────┬─────────────────────────┘
                    │ returns a Distance object
                    ▼
┌──────────────────────┐
│ result               │
│ _Feet   = 8          │
│ _Inches = 7.75       │
└──────────────────────┘
```

---

# 4. Important Correction About Passing Objects in C++

The screenshot says that when an object is passed, only a reference or address is passed and no copy is made.

That is **not automatically true in C++**.

It depends on how the parameter is written.

## Passing by value

```cpp
Distance AddDistance(Distance other);
```

This creates a copy of the argument object.

```text
d2 ──copy──▶ other
```

Changes made to `other` do not affect the original `d2`.

---

## Passing by reference

```cpp
Distance AddDistance(Distance& other);
```

No copy is made.

```text
other ──references──▶ original d2
```

The function can modify the original `d2`.

---

## Passing by const reference

```cpp
Distance AddDistance(const Distance& other) const;
```

No copy is made, and the function cannot modify `d2`.

```text
other ──read-only reference──▶ original d2
```

For this method, this is usually the best design.

---

## Comparison

| Parameter                    | Makes a copy? | Can modify original? | Typical use                         |
|------------------------------|---------------|----------------------|-------------------------------------|
| `Distance other`             | Yes           | No                   | When a separate copy is required.   |
| `Distance& other`            | No            | Yes                  | When the original must be changed.  |
| `const Distance& other`      | No            | No                   | Read-only access without copying.   |

---

# 5. Complete Program Using Three Files

## 📄 `Distance.h`

The header contains the class declaration.

```cpp
#ifndef DISTANCE_H
#define DISTANCE_H

class Distance
{
private:
    int   _Feet;
    float _Inches;

public:
    Distance();
    Distance(int feet, float inches);

    void SetDistance(int feet, float inches);

    Distance AddDistance(const Distance& other) const;

    void Print() const;
};

#endif
```

### Important declaration

```cpp
Distance AddDistance(const Distance& other) const;
```

This says:

> `AddDistance()` receives another `Distance` object and returns a new `Distance` object.

---

## 📄 `Distance.cpp`

The implementation file contains the function definitions.

```cpp
#include "Distance.h"
#include <iostream>

Distance::Distance()
    : _Feet(0), _Inches(0.0f)
{
}

Distance::Distance(int feet, float inches)
    : _Feet(feet), _Inches(inches)
{
}

void Distance::SetDistance(int feet, float inches)
{
    _Feet = feet;
    _Inches = inches;
}

Distance Distance::AddDistance(const Distance& other) const
{
    int newFeet = _Feet + other._Feet;
    float newInches = _Inches + other._Inches;

    Distance result(newFeet, newInches);

    return result;
}

void Distance::Print() const
{
    std::cout << "Feet = " << _Feet
              << "\tInches = " << _Inches
              << '\n';
}
```

---

# 6. Understanding the Definition

```cpp
Distance Distance::AddDistance(const Distance& other) const
```

There are two appearances of `Distance`, but they have different jobs:

```text
Distance        Distance::AddDistance(...)
   │                │
   │                └── AddDistance belongs to the Distance class
   │
   └── The function returns a Distance object
```

### The first `Distance`

```cpp
Distance
```

This is the return type.

It means:

```text
The function returns an object of class Distance.
```

### `Distance::`

```cpp
Distance::
```

This tells C++:

```text
AddDistance belongs to the Distance class.
```

### The parameter

```cpp
const Distance& other
```

This gives the function read-only access to another `Distance` object without making a copy.

### The final `const`

```cpp
const
```

This promises that `AddDistance()` will not modify the calling object.

For this call:

```cpp
d1.AddDistance(d2);
```

The final `const` protects `d1`.

The parameter's `const` protects `d2`.

```text
const Distance& other
│
└── protects d2

... AddDistance(...) const
                       │
                       └── protects d1
```

---

## 📄 `main.cpp`

```cpp
#include "Distance.h"
#include <iostream>

int main()
{
    Distance d1(5, 3.5f);
    Distance d2(3, 4.25f);

    std::cout << "d1: ";
    d1.Print();

    std::cout << "d2: ";
    d2.Print();

    Distance result = d1.AddDistance(d2);

    std::cout << "Result: ";
    result.Print();

    return 0;
}
```

### Output

```text
d1: Feet = 5    Inches = 3.5
d2: Feet = 3    Inches = 4.25
Result: Feet = 8    Inches = 7.75
```

---

# 7. Step-by-Step Execution

## Step 1: Create `d1`

```cpp
Distance d1(5, 3.5f);
```

Result:

```text
d1
├── _Feet   = 5
└── _Inches = 3.5
```

## Step 2: Create `d2`

```cpp
Distance d2(3, 4.25f);
```

Result:

```text
d2
├── _Feet   = 3
└── _Inches = 4.25
```

## Step 3: Call the method

```cpp
d1.AddDistance(d2);
```

Here:

```text
d1 is the calling object
d2 is passed into the parameter named other
```

Inside the function:

```cpp
int newFeet = _Feet + other._Feet;
```

C++ understands this as:

```text
newFeet = d1._Feet + d2._Feet
newFeet = 5 + 3
newFeet = 8
```

Then:

```cpp
float newInches = _Inches + other._Inches;
```

C++ understands this as:

```text
newInches = d1._Inches + d2._Inches
newInches = 3.5 + 4.25
newInches = 7.75
```

## Step 4: Create a local result object

```cpp
Distance result(newFeet, newInches);
```

This creates:

```text
result
├── _Feet   = 8
└── _Inches = 7.75
```

## Step 5: Return the object

```cpp
return result;
```

The function returns the complete object.

Then this line receives it:

```cpp
Distance result = d1.AddDistance(d2);
```

> Modern C++ normally optimizes object returns, so returning an object by value is a normal design.

---

# 8. Can a Class Access Private Members of Another Object?

Yes, when both objects belong to the **same class**.

Inside this member function:

```cpp
Distance Distance::AddDistance(const Distance& other) const
{
    int newFeet = _Feet + other._Feet;
}
```

`other._Feet` is allowed even though `_Feet` is private.

Why?

Because C++ privacy is enforced at the **class level**, not separately for every object.

```text
Distance member functions
        │
        ├── can access d1._Feet
        ├── can access d2._Feet
        └── can access result._Feet
```

Code outside the class cannot do this:

```cpp
int main()
{
    Distance d1(5, 3.5f);

    std::cout << d1._Feet; // ❌ Error: _Feet is private
}
```

---

# 9. Shorter Version of `AddDistance()`

Longer learning version:

```cpp
Distance Distance::AddDistance(const Distance& other) const
{
    int newFeet = _Feet + other._Feet;
    float newInches = _Inches + other._Inches;

    Distance result(newFeet, newInches);

    return result;
}
```

Shorter version:

```cpp
Distance Distance::AddDistance(const Distance& other) const
{
    return Distance(
        _Feet + other._Feet,
        _Inches + other._Inches
    );
}
```

Both versions produce the same result.

---

# 10. Wrong and Correct Designs

## ❌ Wrong: Return only the feet

```cpp
int AddDistance(const Distance& other) const
{
    return _Feet + other._Feet;
}
```

Problem:

```text
Only the feet are returned.
The inches are lost.
```

## ✅ Correct: Return a complete object

```cpp
Distance AddDistance(const Distance& other) const;
```

Now the result contains both values:

```text
result._Feet
result._Inches
```

---

## ⚠️ Works, but makes a copy

```cpp
Distance AddDistance(Distance other) const;
```

This passes `d2` by value:

```text
original d2 ──copy──▶ other
```

## ✅ Better for read-only use

```cpp
Distance AddDistance(const Distance& other) const;
```

This means:

```text
No copy
No modification of d2
No modification of d1
Returns a new result object
```

---

## ❌ Wrong: Return a reference to a local object

```cpp
const Distance& Distance::AddDistance(const Distance& other) const
{
    Distance result(
        _Feet + other._Feet,
        _Inches + other._Inches
    );

    return result; // ❌ Wrong
}
```

The local `result` is destroyed when the function finishes.

```text
Function ends
    │
    └── local result is destroyed
            │
            └── returned reference becomes invalid
```

Return by value instead:

```cpp
Distance Distance::AddDistance(const Distance& other) const;
```

---

# 11. Why Return a New Object?

```cpp
Distance result = d1.AddDistance(d2);
```

The method does not need to modify `d1` or `d2`.

It creates a third independent object:

```text
Before:

d1 = 5 feet, 3.5 inches
d2 = 3 feet, 4.25 inches

After:

d1     = 5 feet, 3.5 inches
d2     = 3 feet, 4.25 inches
result = 8 feet, 7.75 inches
```

---

# 12. What Does the Final `const` Do?

This version:

```cpp
Distance AddDistance(const Distance& other);
```

can work, but it does not promise that `d1` remains unchanged.

This version:

```cpp
Distance AddDistance(const Distance& other) const;
```

promises that the method will not change `d1`.

This would cause an error inside the const method:

```cpp
Distance Distance::AddDistance(const Distance& other) const
{
    _Feet = 100; // ❌ Cannot modify d1

    return Distance(
        _Feet + other._Feet,
        _Inches + other._Inches
    );
}
```

---

# 13. Optional Improvement: Normalize Inches

The screenshot produces:

```text
8 feet, 7.75 inches
```

That is valid because the inches are below `12`.

But consider:

```text
d1 = 5 feet, 9 inches
d2 = 3 feet, 8 inches
```

Simple addition gives:

```text
8 feet, 17 inches
```

Since:

```text
12 inches = 1 foot
```

we should normalize it to:

```text
9 feet, 5 inches
```

Improved method:

```cpp
Distance Distance::AddDistance(const Distance& other) const
{
    int newFeet = _Feet + other._Feet;
    float newInches = _Inches + other._Inches;

    while (newInches >= 12.0f)
    {
        newInches -= 12.0f;
        ++newFeet;
    }

    return Distance(newFeet, newInches);
}
```

---

# 14. Real-Life Analogy

Imagine two boxes containing measured rope:

```text
Box d1:
5 feet and 3.5 inches

Box d2:
3 feet and 4.25 inches
```

`AddDistance()` acts like a worker:

1. It looks inside `d1`.
2. It receives read-only access to `d2`.
3. It adds the feet.
4. It adds the inches.
5. It creates a new box called `result`.
6. It returns the new box.

```text
d1 ──┐
     ├──▶ AddDistance() ──▶ new result
d2 ──┘
```

---

# 15. Common Errors

## Missing class scope

### ❌ Wrong

```cpp
Distance AddDistance(const Distance& other) const
{
}
```

### ✅ Correct

```cpp
Distance Distance::AddDistance(const Distance& other) const
{
}
```

---

## Declaration and definition do not match

### Header

```cpp
Distance AddDistance(const Distance& other) const;
```

### ❌ Wrong implementation

```cpp
Distance Distance::AddDistance(Distance& other)
{
}
```

The parameter and final `const` do not match.

### ✅ Correct implementation

```cpp
Distance Distance::AddDistance(const Distance& other) const
{
}
```

---

## Forgetting the return statement

### ❌ Wrong

```cpp
Distance Distance::AddDistance(const Distance& other) const
{
    Distance result(
        _Feet + other._Feet,
        _Inches + other._Inches
    );

    // Missing return
}
```

### ✅ Correct

```cpp
return result;
```

---

## Calling the method without an object

### ❌ Wrong

```cpp
Distance result = AddDistance(d2);
```

### ✅ Correct

```cpp
Distance result = d1.AddDistance(d2);
```

---

# 16. Compilation

Compile both `.cpp` files together:

```bash
g++ -std=c++17 -Wall -Wextra -Werror Distance.cpp main.cpp -o distance
```

Run:

```bash
./distance
```

---

# 17. Final Mental Model

Remember this line:

```cpp
Distance result = d1.AddDistance(d2);
```

Read it from right to left:

```text
d2
│
└── is passed into AddDistance()

d1
│
└── is the object that runs AddDistance()

AddDistance()
│
└── creates and returns a new Distance object

result
│
└── receives the returned object
```

The calculations are:

```text
result._Feet   = d1._Feet   + d2._Feet
result._Inches = d1._Inches + d2._Inches
```

With the screenshot values:

```text
result._Feet   = 5   + 3    = 8
result._Inches = 3.5 + 4.25 = 7.75
```

---

# 18. Quick Rules

- An object can be passed as a function argument.
- Passing by value creates a copy.
- Passing by reference avoids the copy.
- `const Distance&` gives read-only access without copying.
- A member function can access private members of another object of the same class.
- A function can return a complete object.
- Return a local result object by value, not by reference.
- The first `Distance` is the return type.
- `Distance::` means the method belongs to the class.
- The final `const` protects the calling object.
- Keep the declaration in the `.h` file.
- Keep the definition in the `.cpp` file.
- Call the method through an object in `main.cpp`.

---

# 19. One-Line Summary

> `d1.AddDistance(d2)` reads the values from `d1` and `d2`, creates a new `Distance` object containing their sum, and returns that new object without changing the originals.
