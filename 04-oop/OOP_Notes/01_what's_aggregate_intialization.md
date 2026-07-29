**Aggregate initialization** means creating an object by giving values directly to its members, in the order they are declared:

```cpp
Date date{4, 10, 21};
```

This initializes:

```cpp
day   = 4;
month = 10;
year  = 21;
```

No constructor is called here; the values are assigned directly to the `struct` members.

### Without aggregate initialization

First create the `struct` object, then assign each member separately:

```cpp
struct Date
{
    int day;
    int month;
    int year;
};

int main()
{
    Date date;

    date.day = 4;
    date.month = 10;
    date.year = 2021;
}
```

### With aggregate initialization

Create the object and initialize all members immediately:

```cpp
struct Date
{
    int day;
    int month;
    int year;
};

int main()
{
    Date date{4, 10, 2021};
}
```

The values follow the order of the members:

```cpp
Date date{4, 10, 2021};
//         │   │    └── year
//         │   └─────── month
//         └─────────── day
```

So aggregate initialization is a shorter way to **create and initialize the object at the same time**.
