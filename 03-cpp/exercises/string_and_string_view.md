# `std::string` vs `std::string_view`

## Core difference

- **`std::string`** → **owns** its data. Allocates its own memory, copies the
  characters in, can modify them, and frees the memory when destroyed.
- **`std::string_view`** → a **read-only window** onto data owned by someone
  else. Just a pointer + a length. No allocation, no copy, no ownership.

> **Analogy:** `std::string` = your own photocopy of a document (yours to keep
> and edit). `std::string_view` = looking at the original through a glass
> window (fast and free, but if the original is shredded, you're viewing
> garbage).

## Quick comparison

| Aspect               | `std::string`                     | `std::string_view`                     |
|----------------------|-----------------------------------|----------------------------------------|
| Ownership            | Owns its characters               | Views someone else's characters        |
| Memory allocation    | Yes (may allocate on heap)        | Never                                  |
| Cost to pass/copy    | Expensive (copies data)           | Cheap (just pointer + length)          |
| Can modify content   | Yes (append, insert, change)      | No (read-only)                         |
| Keeps data alive     | Yes                               | No — can dangle!                       |
| Typical use          | Storing / returning / modifying   | Read-only function parameters          |

## Example

```cpp
#include <string>
#include <string_view>

void printA(std::string s);       // makes a COPY of the argument
void printB(std::string_view s);  // just views it — no copy, no allocation

printA("hello");  // allocates a new string, copies "hello" into it
printB("hello");  // just points at the literal — essentially free
```

## When to use which

**Use `std::string_view` when:**
- The function only needs to **read** the text.
- You want one parameter type that accepts `std::string`, string literals,
  and C-style strings without conversions.

**Use `std::string` when:**
- You need to **own** the data (e.g., store it as a class member, return it).
- You need to **modify** the text.
- The source of the data might be destroyed before you're done with it.

## The danger: dangling views

A `string_view` does **not** keep the underlying string alive. If the viewed
string is destroyed, the view dangles, and using it is **undefined behavior**
(same flavor of problem as an object in an invalid state).

```cpp
std::string_view getView()
{
    std::string s{ "temporary" };
    return s;  // BAD: s dies here — the view now points at freed memory
}
```

## Rule of thumb

> Use `std::string_view` for read-only function parameters.
> Use `std::string` when you need to store or modify the text.