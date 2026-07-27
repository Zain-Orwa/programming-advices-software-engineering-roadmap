# 🧩 What is members of the class or object?

> 💡 Any attribute **"variable"** or method **"function"** inside the class is a **member** of that class.

---

# 📋 What are the types of class members?

### 1️⃣ Data Members

> 📦 Any **variable** that is declared inside the class that holds **data**.

In this example:

```cpp
string FirstName;
string LastName;
```

* `FirstName` and `LastName` are **data members**.

### 2️⃣ Function Members [Member Methods]

> ⚙️ Any **function** or **procedure** declared inside the class.

In our case example:

```cpp
string FullName()
{
    return (FirstName + " " + LastName);
}
```

* `FullName()` is a **function member (member method)**.

---

### 🗂️ Summary

| Member Type            | What is it?                                       | Example                 |
|------------------------|---------------------------------------------------|-------------------------|
| 📦 **Data Member**     | A variable inside the class that holds data       | `FirstName`, `LastName` |
| ⚙️ **Function Member** | A function or procedure declared inside the class | `FullName()`            |

---

# 🧠 Objects in Memory

> 💡 **Each instance has its own space in memory. Only member functions are shared among all objects.**

When we create objects from a class, every object gets its **own separate copy** of the data members. But the member functions are **NOT copied** — there is only **one copy** of each function, shared by all objects.

```
┌─────────────────────────────────────────────────────┐
│   Member function 1   Member function 2             │
│            Member function 3                        │   ← ⚙️ ONE shared copy
├─────────────────────────────────────────────────────┤
│   Object 1        Object 2        Object 3          │
│  ┌───────────┐  ┌───────────┐  ┌───────────┐        │
│  │ data      │  │ data      │  │ data      │        │   ← 📦 Each object has
│  │ member 1  │  │ member 1  │  │ member 1  │        │      its OWN copy of
│  ├───────────┤  ├───────────┤  ├───────────┤        │      the data members
│  │ data      │  │ data      │  │ data      │        │
│  │ member 2  │  │ member 2  │  │ member 2  │        │
│  └───────────┘  └───────────┘  └───────────┘        │
└─────────────────────────────────────────────────────┘
```

### 📝 Example

```cpp
#include <iostream>
using namespace std;

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
    clsPerson Person1, Person2;

    Person1.FirstName = "Mohammed";
    Person1.LastName  = "Abu-Hadhoud";

    Person2.FirstName = "Ali";
    Person2.LastName  = "Maher";

    cout << "Person1: " << Person1.FullName() << endl;
    cout << "Person2: " << Person2.FullName() << endl;
}
```

**Output:**

```
Person1: Mohammed Abu-Hadhoud
Person2: Ali Maher
```

### 🔍 What happened in memory?

| 📦 `FirstName`      | 📦 `LastName`  | ⚙️ `FullName()`|
|-------------------- |----------------|---------------|-----------------|
| **Person1 Object**  | `Mohammed`     | `Abu-Hadhoud` | 🔗 shared       |
| **Person2 Object**  | `Ali`          | `Maher`       | 🔗 shared       |

* `Person1` and `Person2` are **two separate objects** — changing `Person1.FirstName` does **NOT** affect `Person2.FirstName`, because each object has its **own space in memory** for its data members.
* `FullName()` exists **only once** in memory. When we call `Person1.FullName()`, the shared function works on **Person1's data**. When we call `Person2.FullName()`, the same function works on **Person2's data**.

### ⭐ Important Points to Remember

> ✅ **Data members** → duplicated per object (each object = independent copy).
>
> ✅ **Member functions** → one shared copy for the whole class (saves memory — imagine 1000 objects: 1000 copies of the data, but still only 1 copy of the functions).
>
> ✅ How does the shared function know **which object's data** to use? Behind the scenes, C++ secretly passes a hidden pointer called **`this`** to every member function call. `Person1.FullName()` means: run `FullName()` with `this` pointing to `Person1`, so `FirstName` inside the function actually means `this->FirstName` → Person1's `FirstName`.
>
> ✅ That's why an object is an **instance** of the class: the class is written once (blueprint), but every instance gets its own independent data in memory.
