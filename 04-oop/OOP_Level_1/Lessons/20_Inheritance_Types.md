# 20 — Inheritance Types in C++

Inheritance allows a **derived class** to reuse and extend the accessible members of a **base class**.

```cpp
class Derived : public Base
{
};
```

> In the diagrams below, the arrow goes from the **base class** to the **derived class**.

---

## Quick Comparison

| Type | Structure | Main idea |
|---|---|---|
| Single | `A → B` | One derived class inherits from one base class. |
| Multilevel | `A → B → C` | Inheritance continues through several levels. |
| Hierarchical | `A → B`, `A → C` | Several derived classes inherit directly from one base class. |
| Multiple | `A + B → C` | One derived class inherits from two or more base classes. |
| Hybrid | Combination of types | Two or more inheritance structures are combined. |

---

# 1. Single Inheritance

One derived class inherits from one base class.

```text
┌──────────────┐
│    Animal    │  Base class
└──────┬───────┘
       │
       ▼
┌──────────────┐
│     Dog      │  Derived class
└──────────────┘
```

```cpp
class Animal
{
public:
    void Eat()
    {
        cout << "The animal is eating.\n";
    }
};

class Dog : public Animal
{
public:
    void Bark()
    {
        cout << "The dog is barking.\n";
    }
};
```

```cpp
Dog dog;
dog.Eat();   // Inherited from Animal
dog.Bark();  // Defined inside Dog
```

### Meaning

A `Dog` **is an** `Animal`, so it can use the accessible behavior of `Animal` and add its own behavior.

---

# 2. Multilevel Inheritance

A derived class becomes the base class of another class.

```text
┌──────────────┐
│    Person    │
└──────┬───────┘
       │
       ▼
┌──────────────┐
│   Employee   │
└──────┬───────┘
       │
       ▼
┌──────────────┐
│  Programmer  │
└──────────────┘
```

```cpp
class Person
{
public:
    void Introduce()
    {
        cout << "I am a person.\n";
    }
};

class Employee : public Person
{
public:
    void Work()
    {
        cout << "I am working.\n";
    }
};

class Programmer : public Employee
{
public:
    void Code()
    {
        cout << "I am writing C++ code.\n";
    }
};
```

```cpp
Programmer programmer;
programmer.Introduce(); // From Person
programmer.Work();      // From Employee
programmer.Code();      // From Programmer
```

### Important construction order

When a `Programmer` object is created, constructors run from the oldest base class to the final derived class:

```text
Person → Employee → Programmer
```

Destructors run in the opposite direction:

```text
Programmer → Employee → Person
```

---

# 3. Hierarchical Inheritance

Two or more classes inherit directly from the same base class.

```text
                  ┌──────────────┐
                  │    Shape     │
                  └──────┬───────┘
                         │
             ┌───────────┴───────────┐
             │                       │
             ▼                       ▼
      ┌──────────────┐        ┌──────────────┐
      │    Circle    │        │  Rectangle   │
      └──────────────┘        └──────────────┘
```

```cpp
class Shape
{
public:
    void DisplayType()
    {
        cout << "I am a shape.\n";
    }
};

class Circle : public Shape
{
public:
    void DrawCircle()
    {
        cout << "Drawing a circle.\n";
    }
};

class Rectangle : public Shape
{
public:
    void DrawRectangle()
    {
        cout << "Drawing a rectangle.\n";
    }
};
```

Both `Circle` and `Rectangle` receive the accessible members of `Shape`, but they do not inherit from each other.

---

# 4. Multiple Inheritance

One derived class inherits from two or more base classes.

```text
┌──────────────┐        ┌──────────────┐
│   Printer    │        │   Scanner    │
└──────┬───────┘        └──────┬───────┘
       │                       │
       └───────────┬───────────┘
                   ▼
          ┌────────────────┐
          │    AllInOne    │
          └────────────────┘
```

```cpp
class Printer
{
public:
    void Print()
    {
        cout << "Printing a document.\n";
    }
};

class Scanner
{
public:
    void Scan()
    {
        cout << "Scanning a document.\n";
    }
};

class AllInOne : public Printer, public Scanner
{
};
```

```cpp
AllInOne machine;
machine.Print();
machine.Scan();
```

## Main issue: ambiguous member names

A conflict occurs when both base classes contain a member with the same name.

```cpp
class Printer
{
public:
    void Status()
    {
        cout << "Printer status.\n";
    }
};

class Scanner
{
public:
    void Status()
    {
        cout << "Scanner status.\n";
    }
};

class AllInOne : public Printer, public Scanner
{
};
```

### Wrong

```cpp
AllInOne machine;
machine.Status(); // ERROR: Which Status() should be called?
```

The compiler sees two possible functions:

```text
AllInOne
├── Printer::Status()
└── Scanner::Status()
```

### Correct: specify the base class

```cpp
machine.Printer::Status();
machine.Scanner::Status();
```

The derived class can also provide one clear interface:

```cpp
class AllInOne : public Printer, public Scanner
{
public:
    void ShowStatus()
    {
        Printer::Status();
        Scanner::Status();
    }
};
```

## Other things to remember

- Base constructors run in the order in which the base classes appear after the colon.
- Multiple inheritance can make a design harder to understand and maintain.
- It is safest when the base classes have small, separate responsibilities.
- C++ supports multiple class inheritance, but it should be used only when the relationship is logical.

```cpp
class AllInOne : public Printer, public Scanner
{
};
```

Construction order:

```text
Printer → Scanner → AllInOne
```

---

# 5. Hybrid Inheritance

Hybrid inheritance is not one separate basic shape. It is a **combination of two or more inheritance types**.

A common example combines hierarchical inheritance and multiple inheritance:

```text
                   ┌──────────────┐
                   │    Person    │
                   └──────┬───────┘
                          │
             ┌────────────┴────────────┐
             │                         │
             ▼                         ▼
      ┌──────────────┐          ┌──────────────┐
      │   Student    │          │   Employee   │
      └──────┬───────┘          └──────┬───────┘
             │                         │
             └────────────┬────────────┘
                          ▼
                ┌──────────────────┐
                │ TeachingAssistant│
                └──────────────────┘
```

This shape is called the **diamond problem** because the inheritance diagram looks like a diamond.

## The diamond problem

Without virtual inheritance, `TeachingAssistant` receives **two separate `Person` parts**:

```text
TeachingAssistant
├── Student
│   └── Person   ← first Person object
└── Employee
    └── Person   ← second Person object
```

```cpp
class Person
{
public:
    string Name;
};

class Student : public Person
{
};

class Employee : public Person
{
};

class TeachingAssistant : public Student, public Employee
{
};
```

### Wrong or ambiguous use

```cpp
TeachingAssistant assistant;
assistant.Name = "Alex"; // ERROR: Which Person::Name?
```

The compiler cannot know whether you mean:

```text
Student::Person::Name
or
Employee::Person::Name
```

You could qualify the path, but the object would still contain two independent `Person` parts:

```cpp
assistant.Student::Name = "Alex";
assistant.Employee::Name = "John";
```

That is normally not what we want for one real person.

## Solution: virtual inheritance

Make the classes in the middle inherit the common base virtually:

```cpp
class Person
{
public:
    string Name;
};

class Student : virtual public Person
{
};

class Employee : virtual public Person
{
};

class TeachingAssistant : public Student, public Employee
{
};
```

Now the final object contains only one shared `Person` part:

```text
TeachingAssistant
├── Student ────┐
│               │
├── Employee ───┤
│               ▼
└────────── one shared Person object
```

```cpp
TeachingAssistant assistant;
assistant.Name = "Alex"; // Correct: only one Person::Name exists
```

### Important constructor rule

When virtual inheritance is used, the **most-derived class** constructs the virtual base class.

```cpp
class Person
{
public:
    Person(string name)
    {
        cout << "Person: " << name << '\n';
    }
};

class Student : virtual public Person
{
public:
    Student() : Person("temporary")
    {
    }
};

class Employee : virtual public Person
{
public:
    Employee() : Person("temporary")
    {
    }
};

class TeachingAssistant : public Student, public Employee
{
public:
    TeachingAssistant(string name)
        : Person(name), Student(), Employee()
    {
    }
};
```

For a `TeachingAssistant` object, `Person(name)` is constructed by `TeachingAssistant`, because it is the most-derived class.

---

# Why Multiple and Hybrid Inheritance Need More Care

The final two types are more complicated mainly because one object can receive members through several paths.

| Problem | What it means | Common solution |
|---|---|---|
| Name ambiguity | Two base classes contain the same member name. | Use scope resolution or provide one wrapper function. |
| Diamond duplication | The same common base is inherited twice. | Use virtual inheritance when one shared base is intended. |
| Constructor complexity | Several base constructors must run in a specific order. | Understand base declaration order and initialize every required base. |
| Tight coupling | The derived class depends on several class hierarchies. | Prefer small interfaces and composition when inheritance is not a true “is-a” relationship. |
| Harder maintenance | Changes in one base may affect many derived classes. | Keep the hierarchy simple and avoid unnecessary inheritance. |

---

# Inheritance or Composition?

Use inheritance when the relationship is truly **is-a**:

```text
Dog is an Animal
Programmer is an Employee
```

Use composition when the relationship is **has-a**:

```text
Car has an Engine
Computer has a Printer
```

Instead of inheriting many classes, composition is often simpler:

```cpp
class Computer
{
private:
    Printer _Printer;
    Scanner _Scanner;
};
```

This avoids many ambiguity and diamond-problem situations.

---

# Final Summary Diagram

```text
1. Single
   A
   │
   ▼
   B

2. Multilevel
   A
   │
   ▼
   B
   │
   ▼
   C

3. Hierarchical
       A
      / \
     ▼   ▼
     B   C

4. Multiple
   A   B
    \ /
     ▼
     C

5. Hybrid / Diamond
       A
      / \
     ▼   ▼
     B   C
      \ /
       ▼
       D
```

## One-sentence definitions

1. **Single inheritance:** one class inherits from one base class.
2. **Multilevel inheritance:** inheritance continues through a chain of classes.
3. **Hierarchical inheritance:** several classes inherit directly from one base class.
4. **Multiple inheritance:** one class inherits from several base classes.
5. **Hybrid inheritance:** two or more inheritance structures are combined.
