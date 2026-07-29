# 🔐 Access Specifiers in C++: `private`, `protected`, and `public`

> 💡 **Access specifiers**, also called **access modifiers**, control where the members of a class can be accessed.

A class member can be:

* A **data member** such as a variable
* A **member function** such as a method

C++ provides three main access specifiers:

1. `private`
2. `protected`
3. `public`

---

# 🧱 Complete Code Example

```cpp
#include <iostream>

using namespace std;

class clsPerson
{
private:
    int Variable1 = 5;

    int function1()
    {
        return (40);
    }

protected:
    int Variable2 = 100;

    int function2()
    {
        return (50);
    }

public:
    string FirstName;
    string LastName;

    string FullName()
    {
        return (FirstName + " " + LastName);
    }

    float Function3()
    {
        return (function1() + Variable1 + function2() + Variable2);
    }
};

int main()
{
    clsPerson Person1;

    Person1.FirstName = "Alex";
    Person1.LastName = "Hormozi";

    cout << Person1.FullName() << endl;
    cout << Person1.Function3() << endl;

    return (0);
}
```

---

# 🖥️ Program Output

```text
Alex Hormozi
195
```

The first output is:

```text
Alex Hormozi
```

because `FullName()` combines:

```cpp
FirstName + " " + LastName
```

The second output is:

```text
195
```

because `Function3()` calculates:

```text
function1() + Variable1 + function2() + Variable2
     40     +     5     +     50    +    100
```

```text
40 + 5 + 50 + 100 = 195
```

---

# 📚 What Is an Access Specifier?

> 🔑 An access specifier determines which parts of the program are allowed to access a class member.

For example, this member is under `private`:

```cpp
private:
    int Variable1 = 5;
```

This means that `Variable1` can be accessed directly from inside `clsPerson`, but it cannot be accessed directly from `main()` through an object.

This member is under `public`:

```cpp
public:
    string FirstName;
```

This means that `FirstName` can be accessed from outside the class through an object:

```cpp
Person1.FirstName = "Alex";
```

---

# 🔒 1. The `private` Access Specifier

> 🔒 A `private` member can be accessed directly only from inside the same class.

In the example:

```cpp
private:
    int Variable1 = 5;

    int function1()
    {
        return (40);
    }
```

The following members are private:

* `Variable1`
* `function1()`

They can be used inside the class:

```cpp
float Function3()
{
    return (function1() + Variable1 + function2() + Variable2);
}
```

However, they cannot be accessed directly from `main()`:

```cpp
Person1.Variable1 = 20;   // ❌ Error
Person1.function1();      // ❌ Error
```

The compiler rejects these statements because `Variable1` and `function1()` are private.

> ✅ A public member function can access private members because that function is still defined inside the same class.

---

# 🛡️ 2. The `protected` Access Specifier

> 🛡️ A `protected` member can be accessed inside the same class and inside classes that inherit from it.

In the example:

```cpp
protected:
    int Variable2 = 100;

    int function2()
    {
        return (50);
    }
```

The following members are protected:

* `Variable2`
* `function2()`

They can be used inside `clsPerson`:

```cpp
float Function3()
{
    return (function1() + Variable1 + function2() + Variable2);
}
```

However, they cannot be accessed directly from `main()` through an object:

```cpp
Person1.Variable2 = 200;  // ❌ Error
Person1.function2();      // ❌ Error
```

The main difference between `private` and `protected` appears when inheritance is used.

A derived class can access protected members:

```cpp
class clsEmployee : public clsPerson
{
public:
    void PrintProtectedData()
    {
        cout << Variable2 << endl;   // ✅ Allowed
        cout << function2() << endl; // ✅ Allowed
    }
};
```

A derived class cannot directly access private members:

```cpp
class clsEmployee : public clsPerson
{
public:
    void PrintPrivateData()
    {
        cout << Variable1 << endl;   // ❌ Error
        cout << function1() << endl; // ❌ Error
    }
};
```

---

# 🔓 3. The `public` Access Specifier

> 🔓 A `public` member can be accessed from inside the class and from outside the class through an object.

In the example:

```cpp
public:
    string FirstName;
    string LastName;
```

These members can be accessed from `main()`:

```cpp
Person1.FirstName = "Alex";
Person1.LastName = "Hormozi";
```

The public member functions can also be called from `main()`:

```cpp
cout << Person1.FullName() << endl;
cout << Person1.Function3() << endl;
```

The following members are public:

* `FirstName`
* `LastName`
* `FullName()`
* `Function3()`

---

# ⚖️ Access-Specifier Comparison

| Access Specifier | Same Class | Derived Class | Outside Through Object |
|------------------|------------|---------------|------------------------|
| `private`        | Yes        | No            | No                     |
| `protected`      | Yes        | Yes           | No                     |
| `public`         | Yes        | Yes           | Yes                    |

## Simple Meaning

| Access Specifier | Simple Description                                      |
|------------------|---------------------------------------------------------|
| `private`        | Accessible only inside the same class                   |
| `protected`      | Accessible inside the class and its derived classes     |
| `public`         | Accessible from anywhere the object itself is available |

---

# 🧭 Visual Access Diagram

```text
                      +-----------------------------+
                      |         clsPerson           |
                      |                             |
                      |  private                    |
                      |  - Variable1                |
                      |  - function1()              |
                      |                             |
                      |  protected                  |
                      |  - Variable2                |
                      |  - function2()              |
                      |                             |
                      |  public                     |
                      |  - FirstName                |
                      |  - LastName                 |
                      |  - FullName()               |
                      |  - Function3()              |
                      +-----------------------------+
                              |              |
                              |              |
                   Derived classes       Outside code
                   can access:           can access:
                   protected             public
                   public
```

---

# 🔍 Explanation of Every Member in the Example

| Member         | Member Type     | Access Level | Accessible from `main()`? |
|----------------|-----------------|--------------|---------------------------|
| `Variable1`    | Data member     | `private`    | No                        |
| `function1()`  | Member function | `private`    | No                        |
| `Variable2`    | Data member     | `protected`  | No                        |
| `function2()`  | Member function | `protected`  | No                        |
| `FirstName`    | Data member     | `public`     | Yes                       |
| `LastName`     | Data member     | `public`     | Yes                       |
| `FullName()`   | Member function | `public`     | Yes                       |
| `Function3()`  | Member function | `public`     | Yes                       |

---

# ❓ Why Can `Function3()` Access All the Members?

`Function3()` is declared under `public`:

```cpp
public:
    float Function3()
    {
        return (function1() + Variable1 + function2() + Variable2);
    }
```

Inside `Function3()`, the program uses:

* The private function `function1()`
* The private variable `Variable1`
* The protected function `function2()`
* The protected variable `Variable2`

This is allowed because `Function3()` itself is defined inside the same class.

> ✅ The access level of `Function3()` controls who can call it. It does not prevent it from accessing other members of its own class.

A class member function can access all members of the same class, including:

* `private` members
* `protected` members
* `public` members

---

# 🚪 Public Functions as Controlled Entry Points

A public member function can provide controlled access to private or protected data.

In the example:

```cpp
float Function3()
{
    return (function1() + Variable1 + function2() + Variable2);
}
```

Outside code cannot directly access:

```cpp
Variable1
function1()
Variable2
function2()
```

However, outside code can call:

```cpp
Person1.Function3();
```

This allows the class to control how its internal members are used.

```text
Outside Code
     |
     | calls
     v
+------------------+
| Public Function  |
|   Function3()    |
+------------------+
     |
     | safely uses
     v
private and protected members
```

> 🔑 This is one of the main ideas behind **encapsulation**: hide internal details and provide controlled public operations.

---

# ❌ Examples That Will Not Compile

The following code cannot be used inside `main()`:

```cpp
clsPerson Person1;

Person1.Variable1 = 20;  // ❌ private
Person1.function1();     // ❌ private

Person1.Variable2 = 200; // ❌ protected
Person1.function2();     // ❌ protected
```

The compiler will report that these members are inaccessible.

The following code works:

```cpp
Person1.FirstName = "Alex";
Person1.LastName = "Hormozi";

cout << Person1.FullName() << endl;
cout << Person1.Function3() << endl;
```

This works because these members are public.

---

# 🏗️ Default Access in a Class

When no access specifier is written inside a `class`, the members are `private` by default.

```cpp
class clsPerson
{
    int Age;
};
```

This is equivalent to:

```cpp
class clsPerson
{
private:
    int Age;
};
```

Therefore, this will not compile:

```cpp
clsPerson Person1;
Person1.Age = 30; // ❌ Age is private
```

---

# 🧱 Default Access in a Struct

When no access specifier is written inside a `struct`, the members are `public` by default.

```cpp
struct stPerson
{
    int Age;
};
```

This is equivalent to:

```cpp
struct stPerson
{
public:
    int Age;
};
```

Therefore, this works:

```cpp
stPerson Person1;
Person1.Age = 30; // ✅ Public
```

---

# ⚖️ Default Access: Class vs Struct

| Type     | Default Member Access |
|----------|-----------------------|
| `class`  | `private`             |
| `struct` | `public`              |

> ⚠️ A `class` and a `struct` can both explicitly use `private`, `protected`, and `public`. The main difference here is their default access level.

---

# 🔁 Can Access Specifiers Appear More Than Once?

Yes. The same access specifier can appear multiple times inside a class.

```cpp
class clsExample
{
private:
    int Number1;

public:
    void Function1()
    {
    }

private:
    int Number2;

public:
    void Function2()
    {
    }
};
```

Every access specifier affects all members after it until another access specifier appears.

```cpp
class clsExample
{
private:
    int A;       // private
    int B;       // private

public:
    int C;       // public
    int D;       // public

protected:
    int E;       // protected
    int F;       // protected
};
```

---

# 🧠 Do Access Specifiers Change Object Memory?

> 💡 Access specifiers control **access**, not the amount of memory used by the data member.

For example:

```cpp
class clsExample
{
private:
    int Number1;

public:
    int Number2;
};
```

Both `Number1` and `Number2` normally occupy memory inside each object.

The fact that one is private and the other is public does not, by itself, remove either member from the object.

```text
clsExample Object
+------------------+
| Number1          |  private, but still stored
+------------------+
| Number2          |  public and stored
+------------------+
```

Access specifiers are mainly checked by the compiler.

> ⚠️ `private` does not encrypt or physically hide data in memory. It prevents normal source-code access that violates the class rules.

---

# 🧩 Access Specifiers and Encapsulation

Encapsulation means:

* Keeping important internal data hidden
* Preventing uncontrolled direct modification
* Providing public functions to safely read or change that data

A common design is:

```cpp
class clsBankAccount
{
private:
    float Balance = 0;

public:
    void Deposit(float Amount)
    {
        if (Amount > 0)
        {
            Balance += Amount;
        }
    }

    float GetBalance()
    {
        return Balance;
    }
};
```

Outside code cannot do this:

```cpp
Account.Balance = -1000; // ❌ Balance is private
```

Instead, it must use the public function:

```cpp
Account.Deposit(500); // ✅ Controlled operation
```

This allows the class to validate the value before changing its private data.

---

# ❓ Common Questions and Answers

## 1. What is an access specifier?

An access specifier is a C++ keyword that controls where class members can be accessed.

The three main access specifiers are:

```cpp
private
protected
public
```

---

## 2. Are access specifiers applied to objects?

No. Access specifiers are applied to members declared inside a class.

```cpp
class clsPerson
{
private:
    int Age;
};
```

`Age` is private. The object itself is not described as private merely because it contains private members.

---

## 3. Can an object access private members directly?

No.

```cpp
Person1.Variable1; // ❌ Not allowed
```

Private members must be accessed through an allowed member function when the class provides one.

---

## 4. Can a public function access a private variable?

Yes.

```cpp
public:
    int GetVariable1()
    {
        return Variable1;
    }
```

A member function defined inside the class can access all members of that class.

---

## 5. Can a private function call a public function?

Yes. Members inside the same class can access one another regardless of their access labels.

The access specifier controls access from different parts of the program, not communication between members of the same class.

---

## 6. What is the main difference between `private` and `protected`?

Both are inaccessible directly from outside code.

The difference appears with inheritance:

* A derived class cannot directly access private members.
* A derived class can directly access protected members.

---

## 7. Can `main()` access protected members?

No.

```cpp
Person1.Variable2; // ❌ Not allowed
```

Protected members are not public. They are mainly available to the class itself and its derived classes.

---

## 8. Why is `Function3()` public?

Because the program needs to call it from `main()`:

```cpp
cout << Person1.Function3() << endl;
```

If `Function3()` were private or protected, this direct call from `main()` would not compile.

---

## 9. Why can `Function3()` call `function1()` and `function2()`?

Because all three functions belong to the same class.

A member function can access private, protected, and public members of its own class.

---

## 10. What happens if no access specifier is written?

Inside a `class`, the members are private by default.

Inside a `struct`, the members are public by default.

---

## 11. Do private members exist in every object?

Yes, non-static private data members still occupy space in each object.

Their access is restricted, but their data still exists in the object's memory.

---

## 12. Are public data members always a good design?

They are allowed, but important data is often kept private so the class can validate and control changes through public functions.

For example, a bank balance should usually not be freely writable from outside the class.

---

## 13. Is `private` a security system?

No. It is a language-level access-control rule checked mainly by the compiler.

It helps organise code and protect class invariants, but it is not encryption.

---

## 14. Can a class contain only private members?

Yes, but outside code would need at least one accessible public operation to use the class meaningfully, unless access is provided through another mechanism such as a friend.

---

## 15. Can data members and functions use different access levels?

Yes.

```cpp
class clsExample
{
private:
    int Number;

public:
    void SetNumber(int Value)
    {
        Number = Value;
    }
};
```

The data can be private while the operation that controls it is public.

---

# 🧪 Practice Questions

## Question 1

Which members can be accessed directly from `main()`?

```cpp
class clsTest
{
private:
    int A;

protected:
    int B;

public:
    int C;
};
```

### Answer

Only `C` can be accessed directly from `main()`.

```cpp
clsTest Test1;

Test1.C = 10; // ✅
Test1.A = 10; // ❌
Test1.B = 10; // ❌
```

---

## Question 2

Can this public function access the private variable?

```cpp
class clsTest
{
private:
    int Number = 10;

public:
    int GetNumber()
    {
        return Number;
    }
};
```

### Answer

Yes. `GetNumber()` belongs to the same class, so it can access `Number`.

---

## Question 3

What is the output of the original program?

### Answer

```text
Alex Hormozi
195
```

---

## Question 4

Why does this line cause an error?

```cpp
Person1.Variable1 = 20;
```

### Answer

Because `Variable1` is declared under `private`, so it cannot be accessed directly from `main()`.

---

## Question 5

Why does this line work?

```cpp
cout << Person1.Function3() << endl;
```

### Answer

Because `Function3()` is declared under `public`.

---

## Question 6

Can a derived class access `Variable2`?

### Answer

Yes. `Variable2` is protected, so a derived class can access it directly.

---

## Question 7

Can a derived class access `Variable1` directly?

### Answer

No. `Variable1` is private to `clsPerson`.

---

## Question 8

Does making `Variable1` private remove it from the object's memory?

### Answer

No. It is still stored as part of the object. The access specifier only restricts how source code can access it.

---

# 📋 Final Summary

| Access Specifier | Inside Same Class | Inside Derived Class | Directly from Outside |
|------------------|-------------------|----------------------|-----------------------|
| `private`        | Yes               | No                   | No                    |
| `protected`      | Yes               | Yes                  | No                    |
| `public`         | Yes               | Yes                  | Yes                   |

| Member         | Access Level | Can `main()` Access It Directly? |
|----------------|--------------|----------------------------------|
| `Variable1`    | `private`    | No                               |
| `function1()`  | `private`    | No                               |
| `Variable2`    | `protected`  | No                               |
| `function2()`  | `protected`  | No                               |
| `FirstName`    | `public`     | Yes                              |
| `LastName`     | `public`     | Yes                              |
| `FullName()`   | `public`     | Yes                              |
| `Function3()`  | `public`     | Yes                              |

## ✅ Most Important Points

1. `private` members are accessible only inside the same class.
2. `protected` members are accessible inside the class and its derived classes.
3. `public` members are accessible from outside through an object.
4. A member function can access all members of its own class.
5. `Function3()` can use private and protected members because it belongs to `clsPerson`.
6. A `class` uses `private` access by default.
7. A `struct` uses `public` access by default.
8. Access specifiers control source-code access; they do not normally determine whether a data member occupies memory.
9. Public functions can provide controlled access to hidden internal data.
10. Access control is one of the tools used to implement encapsulation.

> 💡 **Keep internal details private or protected, and expose only the public operations that outside code needs.**
