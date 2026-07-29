# The Class Invariant Problem (C++)

## What is a class invariant?

- An **invariant** = a condition that must be true while some component is executing.
- A **class invariant** = a condition that must stay true **throughout the lifetime of an object** for it to remain in a valid state.
- Important: the *data* can change freely — the invariant is the **rule** that must always hold (e.g., a bank balance moves up and down, but must never go below zero).
- If the invariant is broken, the object is in an **invalid state** → using it may cause **unexpected or undefined behavior**.

> **Key insight:** Using an object whose class invariant has been violated may result in unexpected or undefined behavior.

## Why structs have this problem

- Struct members are wide open — anyone can set them to any value directly.
- Example with no invariant:

```cpp
struct Pair
{
    int first {};
    int second {};
}; // any values are fine → no invariant
```

- Example **with** an invariant:

```cpp
struct Fraction
{
    int numerator { 0 };
    int denominator { 1 }; // invariant: should never be 0
};
```

- A denominator of `0` is mathematically undefined. But nothing stops a user from writing `Fraction f { 5, 0 };` — the object is now invalid, and using it (e.g., dividing) causes a divide-by-zero error later.
- A comment + default member initializer (`{ 1 }`) helps *document* the invariant, but does **not enforce** it.

## Where assert fits in

- `assert(condition)` = a runtime sanity check. If the condition is false, the program stops immediately and points to the problem.
- Improvement: `assert(f.denominator != 0);` at the top of functions that use the Fraction.
- Limitations:
  - It catches the problem **downstream** (where the bad value is *used*), not at the **source** (where it was *set*).
  - With open structs, you'd have to sprinkle asserts everywhere, and nothing forces every access path to go through them.
- (Related: `static_assert` checks conditions at **compile time**, e.g., type sizes; regular `assert` checks at **runtime**.)

## A harder case: correlated members

```cpp
struct Employee
{
    std::string name { };
    char firstInitial { }; // should always match first character of name
};
```

- Invariant: `firstInitial` must always equal `name[0]`.
- The **user** of the struct is responsible for keeping them in sync — and they may not even know about the rule, or may forget when updating `name`.

> **Key insight:** Relying on the user of an object to maintain class invariants is likely to result in problems.

## The real fix: classes

- Goal: bulletproof the type so an object either **can't** be put into an invalid state, or **signals immediately** if it is.
- Structs (as aggregates) lack the mechanics to do this elegantly.
- **Classes** (introduced by Bjarne Stroustrup, inspired by Simula) allow:
  - Making data members **private** — outside code can't touch them directly.
  - Providing **public member functions** (e.g., `deposit`, `withdraw`) as the *only* doorways to the data.
  - Putting checks/asserts **inside** those functions, so every path that changes the data passes through the guard.
- This is **encapsulation** — the solution to the invariant problem.

> **Key insight:** Technically, structs and classes are almost identical; the difference is practical/conventional in how we use them.

## Quick mental model

| Concept              | Analogy                                                     |
|----------------------|-------------------------------------------------------------|
| Class invariant      | The rule: "balance ≥ 0"                                     |
| Invalid state        | Balance set to −1000                                        |
| Assert               | Tripwire that halts when the rule breaks                    |
| Struct problem       | Data on the street — anyone can change it                   |
| Class + private data | Data locked away; public functions are guarded checkpoints  |
