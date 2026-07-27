# 🧩 What Are Members of a Class or Object?

> 💡 Any **attribute** (variable) or **method** (function) declared inside a class is called a **member** of that class.

A class can contain both **data** and **behaviour**:

* 📦 **Data** is stored in variables.
* ⚙️ **Behaviour** is defined through functions.

These variables and functions are collectively called **class members**.

---

## 🏗️ Example Class

```cpp
class clsPerson
{
public:
    string FirstName;
    string LastName;

    string FullName()
    {
        return FirstName + " " + LastName;
    }
};
```

In this example, the class `clsPerson` contains:

* Two variables: `FirstName` and `LastName`
* One function: `FullName()`

All three are members of the class `clsPerson`.

---

# 📚 What Are the Types of Class Members?

There are two main types of class members:

1. **Data Members**
2. **Function Members**

---

## 1️⃣ Data Members

> 📦 A **data member** is any variable declared inside a class that stores data.

In this example:

```cpp
string FirstName;
string LastName;
```

`FirstName` and `LastName` are **data members** because they are variables declared inside the class and they hold information about a person.

For example:

```cpp
clsPerson Person1;

Person1.FirstName = "Mohammed";
Person1.LastName = "Abu-Hadhoud";
```

Here:

* `Person1` is an **object** of the class `clsPerson`.
* `Person1.FirstName` stores the first name of that object.
* `Person1.LastName` stores the last name of that object.

> ✅ Each object created from the class receives its own copy of the **non-static data members**.

---

## 2️⃣ Function Members

> ⚙️ A **function member**, also called a **member function** or **method**, is any function or procedure declared inside a class.

In our example:

```cpp
string FullName()
{
    return FirstName + " " + LastName;
}
```

`FullName()` is a **member function** because it is declared inside the class.

Its purpose is to combine the `FirstName` and `LastName` data members and return the person's full name.

Example:

```cpp
clsPerson Person1;

Person1.FirstName = "Mohammed";
Person1.LastName = "Abu-Hadhoud";

cout << Person1.FullName();
```

Output:

```text
Mohammed Abu-Hadhoud
```

The member function `FullName()` can directly access `FirstName` and `LastName` because all of them belong to the same class.

---

# 🧠 How Are Objects Stored in Memory?

> 💡 Each object, or instance, receives its **own space in memory** for its non-static data members.

Consider the following example:

```cpp
clsPerson Person1;
clsPerson Person2;

Person1.FirstName = "Mohammed";
Person1.LastName = "Abu-Hadhoud";

Person2.FirstName = "Ali";
Person2.LastName = "Maher";
```

Although `Person1` and `Person2` are created from the same class, each object stores its own values.

```text
+-----------------------------+
|       Member Functions      |
|                             |
|          FullName()         |
|       Shared function code  |
+-----------------------------+

+-----------------------------+       +-----------------------------+
|       Person1 Object        |       |       Person2 Object        |
|                             |       |                             |
| FirstName: "Mohammed"       |       | FirstName: "Ali"            |
| LastName:  "Abu-Hadhoud"    |       | LastName:  "Maher"          |
+-----------------------------+       +-----------------------------+
```

> ✅ Changing the data of `Person1` does not change the data of `Person2`.

For example:

```cpp
Person1.FirstName = "Ahmed";
```

This changes only the `FirstName` stored inside `Person1`.

The value stored inside `Person2.FirstName` remains `"Ali"`.

---

## 📦 What Does Each Object Store?

Each object normally contains its own copy of every **non-static data member**.

The object does **not** normally contain a separate copy of the machine code for `FullName()`.

| Part                         | Separate Copy for Each Object? | Explanation                                      |
|------------------------------|--------------------------------|--------------------------------------------------|
| Non-static data members      | ✅ Yes                          | Each object stores its own values                |
| Member-function code         | ❌ No                           | The function code is shared by all objects       |
| Static data members          | ❌ No                           | One shared value belongs to the whole class      |
| Virtual-function information | ⚠️ Sometimes                    | A hidden pointer may exist when `virtual` is used |

---

# ⚙️ How Can One Shared Function Work with Different Objects?

The member function `FullName()` is shared, but it must know which object's data to use.

When we write:

```cpp
Person1.FullName();
```

the function works with the data stored inside `Person1`.

When we write:

```cpp
Person2.FullName();
```

the same function works with the data stored inside `Person2`.

Conceptually, C++ gives a non-static member function a hidden pointer named:

```cpp
this
```

Inside `FullName()`, this code:

```cpp
return FirstName + " " + LastName;
```

can be understood conceptually as:

```cpp
return this->FirstName + " " + this->LastName;
```

The `this` pointer points to the object that called the function.

| Function Call          | What `this` Refers To |
|------------------------|-----------------------|
| `Person1.FullName()`   | `Person1`             |
| `Person2.FullName()`   | `Person2`             |

> 🔑 The function code is shared, but `this` allows that function to operate on the correct object.

---

# 👥 Member Functions Are Shared Among Objects

All objects created from the same class use the same member-function code.

```cpp
cout << Person1.FullName() << endl;
cout << Person2.FullName() << endl;
```

Output:

```text
Mohammed Abu-Hadhoud
Ali Maher
```

Both calls use the same `FullName()` function, but each call works with a different object.

```text
Person1 ──────┐
              ├────> FullName()
Person2 ──────┘
```

The important difference is:

* 📦 The objects have separate data.
* ⚙️ The objects use the same member-function code.

---

# 🏷️ Static Data Members

A `static` data member is different from a normal data member.

> 💡 A static data member belongs to the **class itself**, not separately to every object.

```cpp
class clsPerson
{
public:
    string FirstName;
    string LastName;

    static int NumberOfPersons;
};
```

Here:

* Every object has its own `FirstName`.
* Every object has its own `LastName`.
* All objects share one `NumberOfPersons`.

| Member Type            | Belongs To          | Number of Copies                     |
|------------------------|---------------------|--------------------------------------|
| Non-static data member | Each object         | One copy inside every object         |
| Static data member     | The class           | One shared copy for the entire class |
| Member function        | The class behaviour | One shared section of function code  |

---

# 📏 Do Member Functions Increase the Size of an Object?

Normally, regular member functions do **not** increase the size of each object.

The object's size is mainly affected by:

* Its non-static data members
* Memory alignment and padding
* Possible hidden implementation details, such as a virtual-function pointer

```cpp
class clsExample
{
public:
    int Number;

    void Print()
    {
        cout << Number;
    }
};
```

Conceptually, each `clsExample` object stores `Number`, but it does not store a separate copy of `Print()`.

```cpp
cout << sizeof(clsExample);
```

The result is based mainly on the memory needed for `Number`, together with any required alignment or padding.

> ⚠️ The exact size can depend on the compiler, computer architecture, data-member types, alignment, and whether features such as virtual functions are used.

---

# 🔍 Class Members vs Object Members

The variables and functions are **defined inside the class**, so they are called **class members**.

However, when an object is created, we access those members through the object:

```cpp
clsPerson Person1;

Person1.FirstName = "Mohammed";
Person1.LastName = "Abu-Hadhoud";
Person1.FullName();
```

| Expression           | Meaning                                      |
|----------------------|----------------------------------------------|
| `Person1`            | The object                                   |
| `FirstName`          | A data member                                |
| `LastName`           | A data member                                |
| `FullName()`         | A member function                            |
| `Person1.FirstName`  | Accessing a data member through the object   |
| `Person1.FullName()` | Calling a member function through the object |

> 🔑 The members belong to the class definition, while each object uses those members to store its own data and perform its own operations.

---

# ⚖️ Final Summary

| Member Type            | What Is It?                                               | Example                   |
|------------------------|-----------------------------------------------------------|---------------------------|
| 📦 **Data Member**     | A variable inside the class that stores data              | `FirstName`, `LastName`   |
| ⚙️ **Function Member** | A function or procedure declared inside the class         | `FullName()`              |
| 👥 **Static Member**   | One member shared by all objects of the class             | `NumberOfPersons`         |
| 👉 **`this` Pointer**  | A hidden pointer referring to the object calling a method | `this->FirstName`         |

## ✅ Most Important Points

1. A variable or function declared inside a class is called a **class member**.
2. Each object receives its own copy of the **non-static data members**.
3. Different objects can store different values in the same data members.
4. Member-function code is normally shared among all objects of the class.
5. The hidden `this` pointer tells a member function which object called it.
6. Static data members are shared by all objects of the class.
7. Regular member functions normally do not increase the size of every object.

> 💡 **Objects have separate data, but they share the class's member-function code.**
