# Constructors in C++

> A constructor is one of the first important ideas in object-oriented programming because it controls how an object begins its life.

---

## 1. Checking My Original Understanding

My first understanding was:

> A constructor is a default function created automatically inside an object. It has the same type as the object, and it is hidden unless we define it explicitly.

This is **partly correct**, but some details need to be fixed.

### Correct definition

A **constructor** is a special member function of a class that runs automatically when an object of that class is created.

```cpp
clsAddress Address1("Queen Alia Street", "B 303", "11192", "5555");
```

When this line executes, the constructor of `clsAddress` runs automatically and gives the new object its starting values.

### Important correction

The constructor:

- belongs to the **class**;
- has exactly the **same name as the class**;
- has **no return type**, not even `void`;
- runs automatically during object creation;
- initializes the object's data members;
- may require values before an object is allowed to be created.

The compiler may generate a default constructor automatically, but only when we have not declared certain constructors ourselves.

---

## 2. The Constructor in `clsAddress`

```cpp
clsAddress(string AddressLine1,
           string AddressLine2,
           string POBox,
           string ZipCode)
{
    _AddressLine1 = AddressLine1;
    _AddressLine2 = AddressLine2;
    _POBox = POBox;
    _ZipCode = ZipCode;
}
```

This is a **parameterized constructor** because it receives parameters.

Its purpose is to require the four address values when a `clsAddress` object is created.

```cpp
clsAddress Address1("Queen Alia Street", "B 303", "11192", "5555");
```

The arguments are matched with the constructor parameters in the same order:

| Argument value          | Constructor parameter | Data member initialized |
|-------------------------|-----------------------|-------------------------|
| `"Queen Alia Street"`   | `AddressLine1`        | `_AddressLine1`         |
| `"B 303"`               | `AddressLine2`        | `_AddressLine2`         |
| `"11192"`               | `POBox`               | `_POBox`                |
| `"5555"`                | `ZipCode`             | `_ZipCode`              |

---

## 3. Main Constructor Rules

| Rule                              | Meaning                                                        |
|-----------------------------------|----------------------------------------------------------------|
| Same name as the class            | `clsAddress` is both the class name and constructor name.       |
| No return type                    | Do not write `void`, `int`, or any other return type.           |
| Runs automatically                | It runs when an object is created.                              |
| Usually placed under `public`     | Code outside the class must be able to create objects.          |
| Can receive parameters            | Parameters provide the object's starting values.               |
| Can be overloaded                 | A class may have several constructors with different parameters.|
| Does not normally return a value  | Its job is to initialize the object.                            |
| Runs once for each new object     | Every newly created object runs a constructor.                  |

---

## 4. Complete Corrected Example

```cpp
#include <iostream>
#include <string>

using namespace std;

class clsAddress
{
private:
    string _AddressLine1;
    string _AddressLine2;
    string _POBox;
    string _ZipCode;

public:
    clsAddress(const string& AddressLine1,
               const string& AddressLine2,
               const string& POBox,
               const string& ZipCode)
        : _AddressLine1(AddressLine1),
          _AddressLine2(AddressLine2),
          _POBox(POBox),
          _ZipCode(ZipCode)
    {
    }

    void SetAddressLine1(const string& AddressLine1)
    {
        _AddressLine1 = AddressLine1;
    }

    string AddressLine1() const
    {
        return _AddressLine1;
    }

    void SetAddressLine2(const string& AddressLine2)
    {
        _AddressLine2 = AddressLine2;
    }

    string AddressLine2() const
    {
        return _AddressLine2;
    }

    void SetPOBox(const string& POBox)
    {
        _POBox = POBox;
    }

    string POBox() const
    {
        return _POBox;
    }

    void SetZipCode(const string& ZipCode)
    {
        _ZipCode = ZipCode;
    }

    string ZipCode() const
    {
        return _ZipCode;
    }

    void Print() const
    {
        cout << "\nAddress Details:\n";
        cout << "------------------------\n";
        cout << "AddressLine1: " << _AddressLine1 << endl;
        cout << "AddressLine2: " << _AddressLine2 << endl;
        cout << "POBox       : " << _POBox << endl;
        cout << "ZipCode     : " << _ZipCode << endl;
    }
};

int main()
{
    clsAddress Address1(
        "Queen Alia Street",
        "B 303",
        "11192",
        "5555"
    );

    Address1.Print();

    return 0;
}
```

### Expected output

```text
Address Details:
------------------------
AddressLine1: Queen Alia Street
AddressLine2: B 303
POBox       : 11192
ZipCode     : 5555
```

---

## 5. Execution Flow

When this statement is reached:

```cpp
clsAddress Address1("Queen Alia Street", "B 303", "11192", "5555");
```

C++ performs these steps:

```text
1. Reserve memory for Address1
              ↓
2. Match the four arguments with the constructor parameters
              ↓
3. Initialize the four private data members
              ↓
4. Execute the constructor body
              ↓
5. Address1 is ready to be used
```

The constructor runs automatically. We do not call it later using something like this:

```cpp
Address1.clsAddress(); // Wrong
```

---

## 6. Why the Constructor Is Useful

### Benefit 1: It gives the object starting values

Without a constructor, we may create an object and then forget to initialize part of it.

```cpp
clsAddress Address1;

Address1.SetAddressLine1("Queen Alia Street");
Address1.SetAddressLine2("B 303");
Address1.SetPOBox("11192");

// The programmer forgot to set the ZIP code.
```

A parameterized constructor requires all four values immediately:

```cpp
clsAddress Address1("Queen Alia Street", "B 303", "11192", "5555");
```

### Benefit 2: It can prevent incomplete objects

Because the current constructor requires four arguments, this is not allowed:

```cpp
clsAddress Address1; // Compilation error
```

There is no constructor in the class that accepts zero arguments.

### Benefit 3: It reduces repeated setter calls

Without a constructor:

```cpp
clsAddress Address1;
Address1.SetAddressLine1("Queen Alia Street");
Address1.SetAddressLine2("B 303");
Address1.SetPOBox("11192");
Address1.SetZipCode("5555");
```

With a constructor:

```cpp
clsAddress Address1("Queen Alia Street", "B 303", "11192", "5555");
```

### Benefit 4: It can protect the class rules

A constructor can check whether the provided values are acceptable before allowing the object to be used.

For example, the class could reject an empty first address line.

> Requiring parameters does not automatically guarantee valid data. The constructor must perform validation when validation is needed.

---

## 7. Constructor Body vs. Member Initializer List

The original constructor assigns values inside its body:

```cpp
clsAddress(string AddressLine1,
           string AddressLine2,
           string POBox,
           string ZipCode)
{
    _AddressLine1 = AddressLine1;
    _AddressLine2 = AddressLine2;
    _POBox = POBox;
    _ZipCode = ZipCode;
}
```

This works, but a **member initializer list** is preferred:

```cpp
clsAddress(const string& AddressLine1,
           const string& AddressLine2,
           const string& POBox,
           const string& ZipCode)
    : _AddressLine1(AddressLine1),
      _AddressLine2(AddressLine2),
      _POBox(POBox),
      _ZipCode(ZipCode)
{
}
```

### Visual difference

#### Assignment inside the constructor body

```text
Data member is created first
            ↓
Constructor body assigns another value to it
```

#### Member initializer list

```text
Data member is created directly with its required value
```

The initializer list is normally cleaner and more efficient. Some members, such as `const` data members and reference data members, must be initialized this way.

### Important order rule

Data members are initialized in the order in which they are declared inside the class, not in the visual order written in the initializer list.

In this class, the declaration order is:

```cpp
string _AddressLine1;
string _AddressLine2;
string _POBox;
string _ZipCode;
```

Therefore, C++ initializes them in exactly that order.

---

## 8. What Is a Default Constructor?

A **default constructor** is a constructor that can be called without arguments.

```cpp
clsAddress()
    : _AddressLine1("Unknown"),
      _AddressLine2("Unknown"),
      _POBox("Unknown"),
      _ZipCode("Unknown")
{
}
```

Now this would be allowed:

```cpp
clsAddress Address1;
```

The object would begin with the values `"Unknown"`.

### Important compiler rule

When no constructor is declared, the compiler may generate a default constructor for us.

However, after we declare this parameterized constructor:

```cpp
clsAddress(string AddressLine1,
           string AddressLine2,
           string POBox,
           string ZipCode);
```

C++ does not automatically provide the zero-argument constructor.

Therefore:

```cpp
clsAddress Address1; // Error unless we define a default constructor
```

---

## 9. Constructor Overloading

A class can have more than one constructor, as long as their parameter lists are different.

```cpp
class clsAddress
{
private:
    string _AddressLine1;
    string _AddressLine2;
    string _POBox;
    string _ZipCode;

public:
    clsAddress()
        : _AddressLine1("Unknown"),
          _AddressLine2("Unknown"),
          _POBox("Unknown"),
          _ZipCode("Unknown")
    {
    }

    clsAddress(const string& AddressLine1,
               const string& AddressLine2,
               const string& POBox,
               const string& ZipCode)
        : _AddressLine1(AddressLine1),
          _AddressLine2(AddressLine2),
          _POBox(POBox),
          _ZipCode(ZipCode)
    {
    }
};
```

Now both forms are valid:

```cpp
clsAddress Address1;

clsAddress Address2(
    "Queen Alia Street",
    "B 303",
    "11192",
    "5555"
);
```

C++ selects the matching constructor according to the arguments.

| Object creation                                        | Constructor selected         |
|--------------------------------------------------------|------------------------------|
| `clsAddress Address1;`                                 | Default constructor          |
| `clsAddress Address2("A", "B", "C", "D");`          | Four-parameter constructor   |

---

## 10. Why Is the Constructor Under `public`?

The constructor is under `public` so that code in `main()` can create an object.

```cpp
public:
    clsAddress(...)
```

If the constructor were under `private`, this would normally fail:

```cpp
int main()
{
    clsAddress Address1("A", "B", "C", "D"); // Not accessible
}
```

A private constructor is useful in some advanced designs, but a normal beginner class usually has a public constructor.

---

## 11. Constructor vs. Normal Member Function

| Constructor                                  | Normal member function                       |
|----------------------------------------------|----------------------------------------------|
| Has the same name as the class               | Can have any valid function name             |
| Has no return type                           | Usually declares a return type               |
| Runs automatically during object creation    | Runs only when explicitly called             |
| Initializes the object                       | Performs an operation after creation         |
| Normally runs once for each object creation  | May be called many times                      |

Example:

```cpp
clsAddress Address1("A", "B", "C", "D"); // Constructor runs
Address1.Print();                              // Normal function is called
```

---

## 12. Problems Fixed from the Original Code

### Problem 1: Missing semicolon after the class

Wrong:

```cpp
}

int main()
```

Correct:

```cpp
};

int main()
```

A class definition must end with a semicolon.

### Problem 2: Broken string literal

Wrong:

```cpp
clsAddress Address1("Queen Alia Street", "B 303
", "11192", "5555");
```

Correct:

```cpp
clsAddress Address1("Queen Alia Street", "B 303", "11192", "5555");
```

A normal string literal cannot continue onto the next source-code line like that.

### Problem 3: Missing `<string>` header

Correct:

```cpp
#include <iostream>
#include <string>
```

### Problem 4: `system("pause>0")` is platform-specific

```cpp
system("pause>0");
```

This is mainly a Windows command and is unnecessary in a normal terminal program. The corrected example removes it.

### Problem 5: Prefer initializer lists

The original assignment-based constructor works, but this version initializes the members directly:

```cpp
clsAddress(...)
    : _AddressLine1(AddressLine1),
      _AddressLine2(AddressLine2),
      _POBox(POBox),
      _ZipCode(ZipCode)
{
}
```

---

## 13. Final Mental Model

Think of the class as a design for an address card.

```text
Class
  ↓
Describes which information every address object must contain
  ↓
Constructor
  ↓
Receives the starting information and prepares a valid object
  ↓
Object
  ↓
Can now be printed, read, or modified
```

The constructor is therefore the controlled entrance through which a new object begins.

---

## 14. Quick Summary

```cpp
clsAddress Address1("Queen Alia Street", "B 303", "11192", "5555");
```

- `clsAddress` on the left is the **class type**.
- `Address1` is the **object name**.
- The four strings are **arguments**.
- C++ finds a matching constructor.
- The constructor initializes the private data members.
- After construction finishes, `Address1` is ready to use.

> The most important idea: a constructor establishes the object's initial state automatically when the object is created.

---

## 15. Practice Questions

1. Why does a constructor not have a return type?
2. When does the `clsAddress` constructor run?
3. Why does `clsAddress Address1;` fail in the original class?
4. What is the difference between a default constructor and a parameterized constructor?
5. Why is a member initializer list preferred over assignment inside the constructor body?
6. What happens if the arguments are passed in the wrong order?
7. Why must the constructor normally be under `public`?
8. How many times does the constructor run when three different objects are created?
