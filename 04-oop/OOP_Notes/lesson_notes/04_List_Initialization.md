# C++ List Initialization with `public`, `private`, and `protected`

## 1. Starting example

```cpp
#include <iostream>

class IntPair
{
public:
    int _IntA{};
    int _IntB{};

    void print() const
    {
        std::cout << "Pair(" << _IntA << ", " << _IntB << ")\n";
    }

    bool isEqual(const IntPair& other) const
    {
        return _IntA == other._IntA
            && _IntB == other._IntB;
    }
};

int main()
{
    IntPair p1{1, 2};
    IntPair p2{3, 4};

    p1.print();
    p2.print();

    std::cout << std::boolalpha;
    std::cout << "p1 equals p1: " << p1.isEqual(p1) << '\n';
    std::cout << "p1 equals p2: " << p1.isEqual(p2) << '\n';

    return 0;
}
```

Output:

```text
Pair(1, 2)
Pair(3, 4)
p1 equals p1: true
p1 equals p2: false
```

---

## 2. What does `IntPair p1{1, 2};` mean?

This line uses **list initialization**:

```cpp
IntPair p1{1, 2};
```

The values are placed into the data members in their declaration order:

```cpp
class IntPair
{
public:
    int _IntA{}; // receives 1
    int _IntB{}; // receives 2
};
```

So after initialization:

```text
p1
+----------------+
| _IntA = 1      |
| _IntB = 2      |
+----------------+
```

And:

```cpp
IntPair p2{3, 4};
```

produces:

```text
p2
+----------------+
| _IntA = 3      |
| _IntB = 4      |
+----------------+
```

The first value goes to the first member, and the second value goes to the second member.

This works because `IntPair` is an **aggregate type** in this version of the class.

---

## 3. What is an aggregate?

An aggregate is a class or structure that can be initialized directly from its members.

A simplified rule for this example is:

- It has no user-declared constructor.
- Its data members used by aggregate initialization are public.
- It does not use features such as virtual functions that would prevent aggregate initialization.

Because the members are public, this works:

```cpp
IntPair p1{1, 2};
```

C++ initializes the members in declaration order.

---

## 4. List initialization is not an array

This:

```cpp
IntPair p1{1, 2};
```

does not mean that `p1` is an array.

`p1` is one object containing two separately named members:

```cpp
p1._IntA
p1._IntB
```

An array would use positions:

```cpp
int values[2]{1, 2};

values[0]; // 1
values[1]; // 2
```

The class uses names instead of indexes:

```cpp
p1._IntA; // 1
p1._IntB; // 2
```

| Class object                  | Array                         |
|:------------------------------|:------------------------------|
| `IntPair p1{1, 2};`           | `int values[2]{1, 2};`        |
| Access with `p1._IntA`        | Access with `values[0]`       |
| Access with `p1._IntB`        | Access with `values[1]`       |
| Members can have clear names  | Elements are identified by index |
| Members may have different types | All array elements have one type |

---

## 5. What do `{}` after the member declarations mean?

The members are declared like this:

```cpp
int _IntA{};
int _IntB{};
```

The empty braces give each integer a default value of zero when no other value is supplied.

For example:

```cpp
IntPair p{};
```

produces:

```text
p._IntA = 0
p._IntB = 0
```

This also works:

```cpp
IntPair p{5};
```

The result is:

```text
p._IntA = 5
p._IntB = 0
```

The first member receives `5`, and the remaining member uses its default initialization.

---

## 6. How `isEqual()` works

The function is:

```cpp
bool isEqual(const IntPair& other) const
{
    return _IntA == other._IntA
        && _IntB == other._IntB;
}
```

When this is called:

```cpp
p1.isEqual(p2);
```

the objects have these roles:

```text
Calling object:  p1
Argument object: p2
```

Inside the function:

```cpp
_IntA
```

means:

```cpp
p1._IntA
```

and:

```cpp
other._IntA
```

means:

```cpp
p2._IntA
```

Therefore:

```cpp
p1.isEqual(p2);
```

performs:

```cpp
p1._IntA == p2._IntA
&&
p1._IntB == p2._IntB
```

With the current values:

```cpp
1 == 3  // false
2 == 4  // false
```

The final result is:

```cpp
false && false // false
```

For:

```cpp
p1.isEqual(p1);
```

the comparisons are:

```cpp
1 == 1 // true
2 == 2 // true
```

The result is:

```cpp
true && true // true
```

---

## 7. Why use `const IntPair& other`?

```cpp
const IntPair& other
```

has three important parts:

| Part       | Meaning |
|:-----------|:--------|
| `IntPair`  | The function expects another `IntPair` object. |
| `&`        | The object is passed by reference, so it is not copied. |
| `const`    | The function is not allowed to modify the argument object through `other`. |

The reference does not mean that the function compares addresses.

This expression compares integer values:

```cpp
_IntA == other._IntA
```

An address or identity comparison would look like this:

```cpp
this == &other
```

That asks whether both names refer to the exact same object in memory.

---

## 8. The second `const`

The function ends with another `const`:

```cpp
bool isEqual(const IntPair& other) const
                                      // ^ this const
```

This final `const` means that `isEqual()` promises not to modify the calling object.

Inside a `const` member function, code such as this is not allowed:

```cpp
_IntA = 100;
```

The same idea applies to `print()`:

```cpp
void print() const
{
    std::cout << "Pair(" << _IntA << ", " << _IntB << ")\n";
}
```

Printing does not need to change the object, so `print()` should normally be `const`.

---

# Access specifiers

C++ provides three main access levels:

- `public`
- `private`
- `protected`

## 9. Comparison table

| Access level | Accessible inside the class | Accessible outside through an object | Accessible in derived classes |
|:-------------|:---------------------------:|:------------------------------------:|:-----------------------------:|
| `public`     | Yes                         | Yes                                  | Yes                           |
| `private`    | Yes                         | No                                   | No directly                   |
| `protected`  | Yes                         | No                                   | Yes                           |

---

## 10. `public`

A public member can be accessed from anywhere that has access to the object.

```cpp
class IntPair
{
public:
    int _IntA{};
    int _IntB{};
};
```

This is allowed:

```cpp
IntPair p{1, 2};

std::cout << p._IntA;
p._IntB = 50;
```

Because both members are public, the class can also be aggregate-initialized:

```cpp
IntPair p{1, 2};
```

### Public version

```cpp
class IntPair
{
public:
    int _IntA{};
    int _IntB{};
};
```

| Operation                  | Allowed? |
|:---------------------------|:--------:|
| `IntPair p{1, 2};`         | Yes      |
| `p._IntA = 10;`            | Yes      |
| `std::cout << p._IntB;`    | Yes      |

---

## 11. `private`

A private member can only be accessed by member functions of the class and by explicitly authorized friends.

```cpp
class IntPair
{
private:
    int _IntA{};
    int _IntB{};
};
```

This is not allowed outside the class:

```cpp
IntPair p;
p._IntA = 10; // error: _IntA is private
```

Also, this no longer works as aggregate initialization:

```cpp
IntPair p{1, 2}; // error without a suitable constructor
```

The usual solution is to provide a public constructor.

### Private version with a constructor

```cpp
#include <iostream>

class IntPair
{
private:
    int _IntA{};
    int _IntB{};

public:
    IntPair(int a, int b)
        : _IntA{a}, _IntB{b}
    {
    }

    void print() const
    {
        std::cout << "Pair(" << _IntA << ", " << _IntB << ")\n";
    }

    bool isEqual(const IntPair& other) const
    {
        return _IntA == other._IntA
            && _IntB == other._IntB;
    }
};
```

Now this syntax works again:

```cpp
IntPair p1{1, 2};
IntPair p2{3, 4};
```

But its meaning is different.

With public aggregate members:

```cpp
IntPair p1{1, 2};
```

initializes the public members directly.

With a constructor:

```cpp
IntPair p1{1, 2};
```

calls:

```cpp
IntPair(int a, int b)
```

The constructor then initializes the private members:

```cpp
_IntA{a}
_IntB{b}
```

### Initialization flow

```text
IntPair p1{1, 2}
        |
        v
IntPair(int a, int b)
        |
        +---- a = 1 ----> _IntA
        |
        +---- b = 2 ----> _IntB
```

---

## 12. Why private members are commonly preferred

Making data private prevents outside code from changing the object in uncontrolled ways.

Public version:

```cpp
p1._IntA = -999;
```

Private version:

```cpp
p1._IntA = -999; // error
```

The class can provide controlled functions instead:

```cpp
class IntPair
{
private:
    int _IntA{};
    int _IntB{};

public:
    IntPair(int a, int b)
        : _IntA{a}, _IntB{b}
    {
    }

    int getA() const
    {
        return _IntA;
    }

    int getB() const
    {
        return _IntB;
    }

    void setA(int value)
    {
        _IntA = value;
    }

    void setB(int value)
    {
        _IntB = value;
    }
};
```

This gives the class control over how its data is read or changed.

---

## 13. `protected`

A protected member cannot normally be accessed from outside the class.

However, it can be accessed by the class itself and by derived classes.

```cpp
class IntPair
{
protected:
    int _IntA{};
    int _IntB{};
};
```

This is not allowed:

```cpp
IntPair p;
p._IntA = 5; // error: protected member
```

A derived class can access it:

```cpp
class PrintableIntPair : public IntPair
{
public:
    void setValues(int a, int b)
    {
        _IntA = a; // allowed
        _IntB = b; // allowed
    }
};
```

Like private members, protected data members prevent the class from being initialized as the simple public aggregate shown at the beginning.

A constructor should be used when values must be supplied.

### Protected example

```cpp
#include <iostream>

class IntPair
{
protected:
    int _IntA{};
    int _IntB{};

public:
    IntPair(int a, int b)
        : _IntA{a}, _IntB{b}
    {
    }

    bool isEqual(const IntPair& other) const
    {
        return _IntA == other._IntA
            && _IntB == other._IntB;
    }
};

class PrintableIntPair : public IntPair
{
public:
    PrintableIntPair(int a, int b)
        : IntPair{a, b}
    {
    }

    void print() const
    {
        std::cout << "Pair(" << _IntA << ", " << _IntB << ")\n";
    }
};
```

Usage:

```cpp
int main()
{
    PrintableIntPair p1{1, 2};
    PrintableIntPair p2{1, 2};

    p1.print();

    std::cout << std::boolalpha
              << p1.isEqual(p2)
              << '\n';
}
```

The derived class `PrintableIntPair` can access `_IntA` and `_IntB` because they are protected.

Outside code still cannot access them directly.

---

# `class` versus `struct`

## 14. Default access

The main access difference between `class` and `struct` is the default access level.

| Keyword  | Default member access |
|:---------|:----------------------|
| `class`  | `private`             |
| `struct` | `public`              |

These two definitions are equivalent:

```cpp
class IntPair
{
public:
    int _IntA{};
    int _IntB{};
};
```

```cpp
struct IntPair
{
    int _IntA{};
    int _IntB{};
};
```

But this class has private members by default:

```cpp
class IntPair
{
    int _IntA{};
    int _IntB{};
};
```

Therefore outside code cannot access the members directly, and simple aggregate initialization with `{1, 2}` is not available without a constructor.

---

# Different meanings of braces

## 15. Aggregate list initialization

```cpp
struct IntPair
{
    int a{};
    int b{};
};

IntPair p{1, 2};
```

Here the values initialize members directly in declaration order.

---

## 16. Constructor list initialization

```cpp
class IntPair
{
private:
    int a{};
    int b{};

public:
    IntPair(int first, int second)
        : a{first}, b{second}
    {
    }
};

IntPair p{1, 2};
```

Here `{1, 2}` selects and calls the constructor.

The syntax at the call site looks the same, but C++ is doing something different.

| Code at call site       | Class design                  | What C++ does |
|:------------------------|:------------------------------|:--------------|
| `IntPair p{1, 2};`      | Public aggregate members      | Initializes members directly in declaration order |
| `IntPair p{1, 2};`      | Private members plus constructor | Calls the matching constructor |

---

# Recommended complete version

## 17. Encapsulated `IntPair`

```cpp
#include <iostream>

class IntPair
{
private:
    int _IntA{};
    int _IntB{};

public:
    IntPair(int a, int b)
        : _IntA{a}, _IntB{b}
    {
    }

    void print() const
    {
        std::cout << "Pair(" << _IntA << ", " << _IntB << ")\n";
    }

    bool isEqual(const IntPair& other) const
    {
        return _IntA == other._IntA
            && _IntB == other._IntB;
    }
};

int main()
{
    IntPair p1{1, 2};
    IntPair p2{3, 4};
    IntPair p3{1, 2};

    std::cout << "p1: ";
    p1.print();

    std::cout << "p2: ";
    p2.print();

    std::cout << "p3: ";
    p3.print();

    std::cout << std::boolalpha;

    std::cout << "p1 equals p1: "
              << p1.isEqual(p1)
              << '\n';

    std::cout << "p1 equals p2: "
              << p1.isEqual(p2)
              << '\n';

    std::cout << "p1 equals p3: "
              << p1.isEqual(p3)
              << '\n';

    return 0;
}
```

Output:

```text
p1: Pair(1, 2)
p2: Pair(3, 4)
p3: Pair(1, 2)
p1 equals p1: true
p1 equals p2: false
p1 equals p3: true
```

---

# Final summary

| Concept | Meaning in this example |
|:--------|:------------------------|
| `IntPair p1{1, 2};` | Creates one `IntPair` object initialized with two values |
| Public aggregate version | `1` goes directly to `_IntA`; `2` goes directly to `_IntB` |
| Private version | `{1, 2}` calls a public constructor |
| `_IntA == other._IntA` | Compares the first integer in both objects |
| `_IntB == other._IntB` | Compares the second integer in both objects |
| `&&` | Both comparisons must be true |
| `const IntPair& other` | Receives another `IntPair` without copying it and does not modify it |
| Final `const` | Prevents the function from modifying the calling object |
| `public` | Accessible inside and outside the class |
| `private` | Accessible only inside the class and friends |
| `protected` | Accessible inside the class and derived classes |
| `class` | Members are private by default |
| `struct` | Members are public by default |

The most important distinction is:

```text
Public aggregate:
    braces initialize members directly

Private/protected data with constructor:
    braces call the constructor
```
