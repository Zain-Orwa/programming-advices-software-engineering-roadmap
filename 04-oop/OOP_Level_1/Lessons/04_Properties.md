# Properties pattern (getters and setters):
    In C++ these are just member functions, but they play the same role as properties in C# or Python:

**1. Encapsulation — the data is off the street**

```cpp
private:
   string _FirstName;
   string _LastName;
```

`_FirstName` and `_LastName` are private, so no outside code can touch them directly. `Person1._FirstName = "x";` won't even compile. The *only* doorways in are the public functions. This is the exact fix for the invariant problem you studied — with a plain struct, anyone could reach in; here, they can't.

**2. Controlled write access — setters are guarded checkpoints**

```cpp
void SetFirstName(string FirstName)
{
    _FirstName = FirstName;
}
```

Right now this setter just assigns. But because *every* write must pass through it, you have one single place to add validation later:

```cpp
void SetFirstName(string FirstName)
{
    if (FirstName.empty())
        return;              // reject invalid input — invariant protected
    _FirstName = FirstName;
}
```

You add the rule once, and every caller in your whole program is instantly protected. With public data, you'd have to hunt down every assignment everywhere.

**3. Controlled read access — getters can shape what goes out**

```cpp
string GetFirstName()
{
    return (_FirstName);
}
```

The getter decides *how* data leaves the object. Today it returns the raw value; tomorrow it could trim whitespace, capitalize the first letter, or log the access — without any caller changing a line.

**4. Read-only properties — like your `id`**

```cpp
const string id = "A150";

const string GetID()
{
    return (id);
}
```

This is a big one: `id` has a getter but **no setter**. So the outside world can read the ID but can never change it. You've created a read-only property. Public data can't do this — it's either fully open or fully hidden.

**5. Computed properties — like `FullName()`**

```cpp
string FullName()
{
    return (_FirstName + " " + _LastName);
}
```

`FullName` isn't stored anywhere — it's *computed* on demand from the real data. To the caller it feels like a property, but it can never go stale or out of sync. Notice this is precisely the `Employee` problem from your lesson solved: instead of storing `firstInitial` separately and hoping the user keeps it synced with `name`, you'd just compute it: `char FirstInitial() { return _FirstName[0]; }`. The invariant can't break because there's no second copy to drift.

**6. Freedom to change the inside without breaking the outside**

`main` only knows about `SetFirstName`, `GetFirstName`, `FullName`, `GetID`. If you later rename `_FirstName`, store the name differently, or fetch it from a database, `main` doesn't change at all. The public interface is a stable contract; the private implementation is yours to rework.

**Quick summary table:**

| Benefit                  | Where in your example                          |
|--------------------------|------------------------------------------------|
| Encapsulation            | `private:` members, blocked direct access      |
| Validation in one place  | `SetFirstName` / `SetLastName`                 |
| Controlled output        | `GetFirstName` / `GetLastName`                 |
| Read-only property       | `id` + `GetID()` with no setter                |
| Computed property        | `FullName()` — derived, never out of sync      |
| Implementation freedom   | `main` only sees the public interface          |

One bonus observation: all these functions are defined *inside* the class body — so as you now know, they're implicitly `inline` and this class is safe to put in a header and include anywhere. It all connects! Want me to turn this into a `.md` note for your collection?