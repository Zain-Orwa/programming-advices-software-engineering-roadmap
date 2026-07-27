# 🧩 What Is the Difference Between a Class and an Object in OOP?

> 💡 A **class** is a user-defined data type, similar to a `struct` or an `enum`.

A class defines the **structure** and **behaviour** that its objects will have. It can contain:

* 📦 Variables, called **data members** or **attributes**
* ⚙️ Functions, called **member functions** or **methods**

> 💡 An **object** is an *instance* of a class.

This means that before we can declare an object, we first need to define a class. The class works like a **blueprint**, while the object is an actual **variable** created from that blueprint.

> ✅ Therefore, a variable whose type is a class is called an **object**.

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

int main()
{
    clsPerson Person1;
    Person1.FirstName = "Mohammed";
}
```

**In this example:**

* `clsPerson` is the **class**.
* `Person1` is an **object**.
* `Person1` is an object because it is a variable whose data type is the class `clsPerson`.
* `FirstName` and `LastName` are **data members** of the class.
* `FullName()` is a **member function** of the class.

---

# ❌ Why Did `Person1.FirstName = "Mohammed";` Not Work?

> ⚠️ When members are defined inside a class **without** using an access modifier, they are **private by default**.

```cpp
class clsPerson
{
    string FirstName;
    string LastName;
};
```

Here, `FirstName` and `LastName` are **private members**. Private members **cannot** be accessed directly from outside the class. They can only be accessed from *inside* the class through its member functions.

Therefore, this would cause an **error**:

```cpp
clsPerson Person1;
Person1.FirstName = "Mohammed"; // ❌ Error: FirstName is private
```

> 🔍 The problem is **not** that `Person1` is private. `Person1` is an object declared inside `main()`.
> The problem is that `FirstName` is a **private member** of the class.

To access `FirstName` from outside the class, we must place it under the `public` access modifier:

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

✅ Anything declared under `public` can be accessed from **outside** the class through an object:

```cpp
clsPerson Person1;
Person1.FirstName = "Mohammed"; // ✅ Works now
```

🔒 Anything declared under `private` can only be accessed from **inside** the class.

---

## ⚖️ Important Difference Between a Class and a Struct

| | Default Access |
|---|---|
| `class` | 🔒 **private** |
| `struct` | 🔓 **public** |

In a `class`, members are **private by default**.

```cpp
class clsPerson
{
    string FirstName; // 🔒 Private by default
};
```

In a `struct`, members are **public by default**.

```cpp
struct stPerson
{
    string FirstName; // 🔓 Public by default
};
```

---

## 📌 Note: the `string` data type we have been using it is also a class data type:

```cpp
string str;
str. // and we can access all the methods that under string class
```

> 💡 This means that every `string` variable we declare is actually an **object** of the `string` class. That's why we can use the dot operator `.` on it to call its **member functions (methods)** — exactly like we did with `Person1.FullName()`.

### ⚙️ Common `string` Methods with Examples

#### 🔹 `length()` / `size()` — returns the number of characters

```cpp
string str = "Mohammed";
cout << str.length(); // 8
cout << str.size();   // 8 (same as length)
```

#### 🔹 `empty()` — checks if the string is empty

```cpp
string str = "";
cout << str.empty(); // 1 (true)
```

#### 🔹 `at(index)` — returns the character at a position

```cpp
string str = "Mohammed";
cout << str.at(0); // M
cout << str.at(3); // a
```

#### 🔹 `append()` — adds text to the end of the string

```cpp
string str = "Mohammed";
str.append(" Abu-Hadhoud");
cout << str; // Mohammed Abu-Hadhoud
```

#### 🔹 `substr(start, length)` — extracts a part of the string

```cpp
string str = "Mohammed";
cout << str.substr(0, 3); // Moh
cout << str.substr(4);    // mmed
```

#### 🔹 `find()` — searches for text and returns its position

```cpp
string str = "Mohammed";
cout << str.find("ham"); // 2
// returns string::npos if not found
```

#### 🔹 `replace(start, length, newText)` — replaces part of the string

```cpp
string str = "Mohammed";
str.replace(0, 3, "Moh---");
cout << str; // Moh---ammed
```

#### 🔹 `insert(position, text)` — inserts text at a position

```cpp
string str = "Mohammed";
str.insert(0, "Mr. ");
cout << str; // Mr. Mohammed
```

#### 🔹 `erase(start, length)` — removes part of the string

```cpp
string str = "Mohammed";
str.erase(0, 3);
cout << str; // ammed
```

#### 🔹 `clear()` — removes all characters

```cpp
string str = "Mohammed";
str.clear();
cout << str.empty(); // 1 (true)
```

#### 🔹 `compare()` — compares two strings

```cpp
string str1 = "Mohammed";
string str2 = "Mohammed";
cout << str1.compare(str2); // 0 (equal)
```

#### 🔹 `front()` and `back()` — first and last characters

```cpp
string str = "Mohammed";
cout << str.front(); // M
cout << str.back();  // d
```

> ✅ So just like `clsPerson` has the method `FullName()`, the `string` class comes with all these **built-in methods** — because `string` is a **class**, and every string variable is an **object**.