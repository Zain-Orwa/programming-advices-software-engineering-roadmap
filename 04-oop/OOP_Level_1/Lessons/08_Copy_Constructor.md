# Copy Constructors in C++

> A copy constructor creates a **new object** by copying the values from an **already existing object** of the same class.

---

## 1. Checking the Original Code

The main idea in the original code is correct:

```cpp
clsAddress Address2 = Address1;
```

This creates a new object named `Address2` and gives it the same address values stored inside `Address1`.

However, two important details need to be corrected.

### Correction 1: Your manual copy constructor is being called

Your original comment says:

```cpp
// copied by constructor with compiler //
clsAddress Address2 = Address1;
```

That comment is not correct because you already wrote your own copy constructor:

```cpp
clsAddress(clsAddress& old_obj)
{
    // ...
}
```

Therefore, this line:

```cpp
clsAddress Address2 = Address1;
```

calls **your manually defined copy constructor**, not the compiler-generated one.

### Correction 2: The parameter should be `const clsAddress&`

The preferred copy-constructor form is:

```cpp
clsAddress(const clsAddress& old_obj)
```

instead of:

```cpp
clsAddress(clsAddress& old_obj)
```

The complete meaning is:

```text
const clsAddress& old_obj
│     │          │
│     │          └── Name of the existing object
│     └───────────── Reference: do not create another copy
└─────────────────── The source object cannot be modified
```

---

## 2. What Is a Copy Constructor?

A **copy constructor** is a special constructor that creates a new object from another existing object of the same class.

Example:

```cpp
clsAddress Address1("Koko Street", "Fofo Street", "2221", "4500");

clsAddress Address2 = Address1;
```

Here:

- `Address1` already exists.
- `Address2` is a new object.
- The copy constructor copies the data from `Address1` into `Address2`.

After the copying is complete:

```text
Address1                              Address2
------------------------              ------------------------
_AddressLine1 = "Koko Street"         _AddressLine1 = "Koko Street"
_AddressLine2 = "Fofo Street"         _AddressLine2 = "Fofo Street"
_POBox        = "2221"                _POBox        = "2221"
_ZipCode      = "4500"                _ZipCode      = "4500"
```

The two objects contain the same values, but they are still **two separate objects**.

---

## 3. General Copy-Constructor Syntax

```cpp
ClassName(const ClassName& old_obj)
{
    // Copy the values from old_obj
}
```

For the `clsAddress` class:

```cpp
clsAddress(const clsAddress& old_obj)
{
    _AddressLine1 = old_obj._AddressLine1;
    _AddressLine2 = old_obj._AddressLine2;
    _POBox = old_obj._POBox;
    _ZipCode = old_obj._ZipCode;
}
```

### Meaning of every part

| Part                        | Meaning                                                              |
|-----------------------------|----------------------------------------------------------------------|
| `clsAddress`                | The constructor name; it must match the class name.                   |
| `const`                     | The existing object cannot be modified while it is being copied.      |
| `clsAddress`                | The parameter must be an object of the same class.                    |
| `&`                         | Passes the existing object by reference instead of copying it again.  |
| `old_obj`                   | A local name for the existing object being copied.                    |

---

## 4. Why Must We Use `&`?

Consider this incorrect form:

```cpp
clsAddress(clsAddress old_obj) // Wrong
{
}
```

Passing `old_obj` by value would require C++ to copy the object before entering the constructor.

But copying that parameter would require calling the copy constructor again:

```text
Call copy constructor
        ↓
Copy the parameter old_obj
        ↓
Call copy constructor again
        ↓
Copy the parameter again
        ↓
Continue forever
```

Therefore, a copy constructor takes the source object by **reference**:

```cpp
clsAddress(const clsAddress& old_obj)
```

The reference allows the constructor to examine the original object directly without trying to create another copy first.

> The `&` is essential in a normal copy constructor.

---

## 5. Why Should We Use `const`?

Preferred:

```cpp
clsAddress(const clsAddress& old_obj)
```

Without `const`:

```cpp
clsAddress(clsAddress& old_obj)
```

the copy constructor can copy only from non-constant objects.

Using `const` provides two benefits:

1. It promises that the source object will not be changed.
2. It allows copying from both constant and non-constant objects.

Example:

```cpp
const clsAddress Address1("Koko Street", "Fofo Street", "2221", "4500");

clsAddress Address2 = Address1;
```

This works only when the copy constructor accepts a `const` reference:

```cpp
clsAddress(const clsAddress& old_obj)
```

---

## 6. Corrected Manual Copy Constructor

The original constructor used getter functions:

```cpp
clsAddress(clsAddress& old_obj)
{
    _AddressLine1 = old_obj.AddressLine1();
    _AddressLine2 = old_obj.AddressLine2();
    _POBox = old_obj.POBox();
    _ZipCode = old_obj.ZipCode();
}
```

A better version is:

```cpp
clsAddress(const clsAddress& old_obj)
    : _AddressLine1(old_obj._AddressLine1),
      _AddressLine2(old_obj._AddressLine2),
      _POBox(old_obj._POBox),
      _ZipCode(old_obj._ZipCode)
{
}
```

### Why can it access private members?

The copy constructor is a member of `clsAddress`.

A member function of a class can access the private members of **any object of the same class**, not only the current object.

Therefore, this is allowed:

```cpp
old_obj._AddressLine1
```

even though `_AddressLine1` is private.

---

## 7. Assignment Inside the Body vs. Initializer List

### Works, but assigns after the members are created

```cpp
clsAddress(const clsAddress& old_obj)
{
    _AddressLine1 = old_obj._AddressLine1;
    _AddressLine2 = old_obj._AddressLine2;
    _POBox = old_obj._POBox;
    _ZipCode = old_obj._ZipCode;
}
```

### Preferred: directly initializes each member

```cpp
clsAddress(const clsAddress& old_obj)
    : _AddressLine1(old_obj._AddressLine1),
      _AddressLine2(old_obj._AddressLine2),
      _POBox(old_obj._POBox),
      _ZipCode(old_obj._ZipCode)
{
}
```

Visual difference:

```text
Assignment in constructor body:

Create each string first
          ↓
Assign a copied value afterward
```

```text
Member initializer list:

Create each string directly
with the copied value
```

The initializer list expresses the constructor's purpose more clearly and directly.

---

## 8. Complete Corrected Example

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

    // Manual copy constructor
    clsAddress(const clsAddress& old_obj)
        : _AddressLine1(old_obj._AddressLine1),
          _AddressLine2(old_obj._AddressLine2),
          _POBox(old_obj._POBox),
          _ZipCode(old_obj._ZipCode)
    {
        // This message is only for learning and testing.
        cout << "\n[Copy constructor called]\n";
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
        "Koko Street",
        "Fofo Street",
        "2221",
        "4500"
    );

    Address1.Print();

    // Calls the manually defined copy constructor
    clsAddress Address2 = Address1;

    Address2.Print();

    // Proves that Address1 and Address2 are separate objects
    Address2.SetAddressLine1("New Street");

    cout << "\nAfter changing Address2:\n";

    Address1.Print();
    Address2.Print();

    return 0;
}
```

---

## 9. Expected Output

```text
Address Details:
------------------------
AddressLine1: Koko Street
AddressLine2: Fofo Street
POBox       : 2221
ZipCode     : 4500

[Copy constructor called]

Address Details:
------------------------
AddressLine1: Koko Street
AddressLine2: Fofo Street
POBox       : 2221
ZipCode     : 4500

After changing Address2:

Address Details:
------------------------
AddressLine1: Koko Street
AddressLine2: Fofo Street
POBox       : 2221
ZipCode     : 4500

Address Details:
------------------------
AddressLine1: New Street
AddressLine2: Fofo Street
POBox       : 2221
ZipCode     : 4500
```

Changing `Address2` does not change `Address1`.

That proves they are separate objects.

---

## 10. Execution Flow

When this statement runs:

```cpp
clsAddress Address1("Koko Street", "Fofo Street", "2221", "4500");
```

the normal parameterized constructor is called:

```text
Create Address1
      ↓
Call the four-parameter constructor
      ↓
Initialize Address1's four data members
      ↓
Address1 is ready
```

Later:

```cpp
clsAddress Address2 = Address1;
```

the copy constructor is called:

```text
Reserve memory for Address2
            ↓
Pass Address1 as old_obj
            ↓
Copy Address1._AddressLine1 into Address2._AddressLine1
            ↓
Copy Address1._AddressLine2 into Address2._AddressLine2
            ↓
Copy Address1._POBox into Address2._POBox
            ↓
Copy Address1._ZipCode into Address2._ZipCode
            ↓
Address2 is ready
```

---

## 11. Two Ways to Call a Copy Constructor

Both of these forms create a new object and call the copy constructor:

```cpp
clsAddress Address2 = Address1;
```

```cpp
clsAddress Address3(Address1);
```

They mean the same thing in this situation.

| Syntax                                  | Meaning                                      |
|-----------------------------------------|----------------------------------------------|
| `clsAddress Address2 = Address1;`        | Copy-initialization of a new object.          |
| `clsAddress Address3(Address1);`         | Direct-initialization of a new object.        |

Despite the `=` symbol in the first form, it is still **initialization**, because `Address2` is being created on that line.

---

## 12. Copy Constructor vs. Copy Assignment

These two operations look similar, but they are not the same.

### Copy constructor

```cpp
clsAddress Address2 = Address1;
```

`Address2` does not exist before this line.

The copy constructor creates it.

### Copy assignment

```cpp
clsAddress Address2("A", "B", "C", "D");

Address2 = Address1;
```

`Address2` already exists before the assignment.

This uses the **copy-assignment operator**, not the copy constructor.

### Comparison

| Operation             | Example                                  | Is the destination new? | Function used              |
|-----------------------|------------------------------------------|-------------------------|----------------------------|
| Copy construction     | `clsAddress A2 = A1;`                    | Yes                     | Copy constructor           |
| Copy construction     | `clsAddress A2(A1);`                     | Yes                     | Copy constructor           |
| Copy assignment       | `A2 = A1;` after `A2` already exists     | No                      | Copy-assignment operator   |

> The key question is: **Is a new object being created?**  
> If yes, the copy constructor may be used. If no, it is assignment.

---

## 13. What Does the Compiler-Generated Copy Constructor Do?

If you do not write a copy constructor, C++ normally generates one for you.

For this class, the compiler-generated copy constructor conceptually performs this:

```cpp
Address2._AddressLine1 = Address1._AddressLine1;
Address2._AddressLine2 = Address1._AddressLine2;
Address2._POBox = Address1._POBox;
Address2._ZipCode = Address1._ZipCode;
```

This is called **member-wise copying** because each data member is copied individually.

You could remove the manual copy constructor completely:

```cpp
// No copy constructor written here
```

Then this would use the compiler-generated copy constructor:

```cpp
clsAddress Address2 = Address1;
```

You can also explicitly request the compiler-generated version:

```cpp
clsAddress(const clsAddress& old_obj) = default;
```

A shorter conventional spelling is:

```cpp
clsAddress(const clsAddress&) = default;
```

---

## 14. Does `clsAddress` Need a Manual Copy Constructor?

For this specific class, a manual copy constructor is **not necessary**.

All four members are `string` objects:

```cpp
string _AddressLine1;
string _AddressLine2;
string _POBox;
string _ZipCode;
```

`std::string` already knows how to copy itself safely.

Therefore, the compiler-generated copy constructor is enough:

```cpp
class clsAddress
{
    // ...

public:
    clsAddress(const clsAddress&) = default;
};
```

Or you can write no copy constructor at all.

### Recommended version for this class

```cpp
// Let the compiler generate the copy constructor automatically.
```

Writing one manually here is useful for **learning how copy constructors work**, but it does not add special behavior.

This follows an important C++ design idea called the **Rule of Zero**:

> When all data members manage themselves safely, prefer letting the compiler generate copying, assignment, and destruction behavior.

---

## 15. Manual vs. Compiler-Generated Copying

| Manual copy constructor                               | Compiler-generated copy constructor                       |
|-------------------------------------------------------|-----------------------------------------------------------|
| Written by the programmer.                            | Created automatically by the compiler when possible.      |
| Can perform custom copying logic.                     | Copies each data member automatically.                     |
| Useful when special resource handling is required.    | Usually enough for `string`, `vector`, and similar types.  |
| Can contain validation or diagnostic output.          | Has no custom messages or extra behavior.                  |
| Must be maintained if the class gains new members.    | Automatically includes newly added copyable members.       |

---

## 16. Shallow Copy and Deep Copy

This distinction becomes important when a class directly manages resources such as dynamically allocated memory.

### Shallow copy

A shallow copy copies a stored pointer address.

```text
Object1 pointer ──────┐
                      ├── Same memory
Object2 pointer ──────┘
```

Both objects may then refer to the same resource, which can cause serious problems if the class was supposed to own that resource separately.

### Deep copy

A deep copy creates a separate resource and copies the value into it.

```text
Object1 pointer ──────── Own memory

Object2 pointer ──────── Different memory
```

### What happens in `clsAddress`?

The class uses `std::string`, not raw pointers.

Each copied `string` behaves as a separate string value:

```cpp
Address2.SetAddressLine1("New Street");
```

does not change:

```cpp
Address1.AddressLine1()
```

Therefore, the normal compiler-generated copying is safe for this class.

> At this stage, remember the idea: manual copy constructors are mainly needed when a class has special ownership or copying rules.

---

## 17. Common Mistakes

### Mistake 1: Passing the source object by value

Wrong:

```cpp
clsAddress(clsAddress old_obj)
{
}
```

Correct:

```cpp
clsAddress(const clsAddress& old_obj)
{
}
```

---

### Mistake 2: Forgetting `const`

Less flexible:

```cpp
clsAddress(clsAddress& old_obj)
```

Preferred:

```cpp
clsAddress(const clsAddress& old_obj)
```

---

### Mistake 3: Thinking `Address2 = Address1` always means assignment

This is copy construction:

```cpp
clsAddress Address2 = Address1;
```

because `Address2` is created on that line.

This is copy assignment:

```cpp
Address2 = Address1;
```

because `Address2` already exists.

---

### Mistake 4: Saying the compiler copy constructor runs when a manual one exists

Incorrect comment:

```cpp
// copied by constructor with compiler
clsAddress Address2 = Address1;
```

Correct comment:

```cpp
// Calls the manually defined copy constructor
clsAddress Address2 = Address1;
```

---

### Mistake 5: Thinking the two names refer to the same object

After copying:

```cpp
clsAddress Address2 = Address1;
```

`Address1` and `Address2` are different objects.

They begin with equal values, but changing one does not automatically change the other.

---

## 18. Errors and Improvements Fixed from the Original Example

### Improvement 1: Correct spelling

Original:

```cpp
//Copy Constructor Menually //
```

Correct:

```cpp
// Manual copy constructor
```

### Improvement 2: Add `const`

Original:

```cpp
clsAddress(clsAddress& old_obj)
```

Preferred:

```cpp
clsAddress(const clsAddress& old_obj)
```

### Improvement 3: Correct the comment in `main()`

Original:

```cpp
// copied by constructor with compiler //
```

Correct:

```cpp
// Calls the manually defined copy constructor
```

### Improvement 4: Use an initializer list

Original:

```cpp
clsAddress(const clsAddress& old_obj)
{
    _AddressLine1 = old_obj.AddressLine1();
    _AddressLine2 = old_obj.AddressLine2();
    _POBox = old_obj.POBox();
    _ZipCode = old_obj.ZipCode();
}
```

Preferred:

```cpp
clsAddress(const clsAddress& old_obj)
    : _AddressLine1(old_obj._AddressLine1),
      _AddressLine2(old_obj._AddressLine2),
      _POBox(old_obj._POBox),
      _ZipCode(old_obj._ZipCode)
{
}
```

### Improvement 5: Add `<string>`

```cpp
#include <iostream>
#include <string>
```

### Improvement 6: Mark read-only functions as `const`

```cpp
string AddressLine1() const;
string AddressLine2() const;
string POBox() const;
string ZipCode() const;
void Print() const;
```

These functions only read the object and do not change its data members.

---

## 19. Final Mental Model

Think of `Address1` as a completed address card:

```text
Address1
┌────────────────────────────┐
│ Koko Street                │
│ Fofo Street                │
│ PO Box: 2221               │
│ ZIP: 4500                  │
└────────────────────────────┘
```

Now create `Address2` using `Address1`:

```cpp
clsAddress Address2 = Address1;
```

The copy constructor creates another card with the same information:

```text
Address1                         Address2
┌──────────────────────┐         ┌──────────────────────┐
│ Koko Street          │         │ Koko Street          │
│ Fofo Street          │         │ Fofo Street          │
│ PO Box: 2221         │         │ PO Box: 2221         │
│ ZIP: 4500            │         │ ZIP: 4500            │
└──────────────────────┘         └──────────────────────┘
       Object 1                         Object 2
```

The information initially matches, but the two address cards are independent.

---

## 20. Quick Summary

```cpp
clsAddress Address2 = Address1;
```

- `Address1` is the existing source object.
- `Address2` is a new destination object.
- C++ calls the copy constructor.
- The copy constructor copies every address member.
- The two objects begin with equal values.
- They remain separate objects.
- Your manual copy constructor should normally accept `const clsAddress&`.
- In this class, the compiler-generated copy constructor is already sufficient.

The preferred copy-constructor form is:

```cpp
clsAddress(const clsAddress& old_obj)
    : _AddressLine1(old_obj._AddressLine1),
      _AddressLine2(old_obj._AddressLine2),
      _POBox(old_obj._POBox),
      _ZipCode(old_obj._ZipCode)
{
}
```

Or, because all members are safely copyable:

```cpp
clsAddress(const clsAddress&) = default;
```

---

## 21. Practice Questions

1. What is the purpose of a copy constructor?
>> is to create a new object using the value of the existing object.
2. Why does the copy constructor receive an object of the same class?
>> a copy constructor receives an object of the same class because it needs an existing object
>> as a source for initializing the new object.
3. Why is the parameter passed using `&`?
>> The copy-constructor parameter uses & to refer to the original object without copying
>> it which also prevents endless recursive copy-constructor calls.
4. Why should the reference normally be `const`?
>> The reference is normally const so the copy constructor can read the source 
>> object but cannot modify it.
5. Which constructor runs in `clsAddress Address2 = Address1;`?
>> The copy constructor of clsAddress runs. because Address1 is the source object,
>> not the constructor.
6. Does the `=` symbol in that statement mean copy assignment?
>> Address2 is being created and initialized from Address1, so this uses the copy constructor.
>> The = here does not mean copy assignment.
7. What is the difference between copy construction and copy assignment?
>> Copy construction creates a new object from an existing object. Copy assignment copies
>> values into an object that has already been created.
8. Can a copy constructor access private members of another object of the same class?
>> A member function of a class, including its copy constructor, can access private members
>> of any object of the same class.
9. Does `clsAddress` require a manual copy constructor?
>> A manual copy constructor is mainly needed when the class manages special resources, 
>> such as dynamically allocated memory.
10. What would happen if `Address2` were changed after being copied from `Address1`?
>> Changing Address2 does not normally affect Address1, because they are two separate
>> objects with their own copied data.
11. What does a compiler-generated copy constructor normally copy?
>> A compiler-generated copy constructor normally copies each data member from the source
>> object into the new object.Example:
```cpp
class clsAddress
{
private:
    string _City;
    int _ZipCode;
};

//When this happens:
clsAddress Address2 = Address1;

// C++ approximately does:
Address2._City = Address1._City;
Address2._ZipCode = Address1._ZipCode;

```
12. When might a class need custom deep-copy behavior?
>> A class needs custom deep-copy behavior when it owns resources such as dynamically 
>> allocated memory and each copied object must receive its own independent 
>> copy of that resource.
