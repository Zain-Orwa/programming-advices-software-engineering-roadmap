# What's the destructor and why is exist?


# What are the benefits of the Destructor?


# Destroctor and Dynamically allocated memory:
> When we create an object using pointers and allocate memory for it the destructor will
> not automaticlly destroyed as when we creat the object normally in this case we have to go
> and delete the destructor as we have allocated: example:

```cpp
clsPerson * Person = new clsPerson;

```
> in this case as we have allocate the 'Destructor using' "new" we have to also use "delete"
> to destroy the Destructor.