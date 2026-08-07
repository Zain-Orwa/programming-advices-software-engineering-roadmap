/*
    STRUCTURE INSIDE A CLASS
    ========================

    A struct can be declared inside a class when the data represented by the
    struct logically belongs to that class.

    This is useful when several related variables should be grouped together.

    Example:

        struct stAddress
        {
            string AddressLine1;
            string AddressLine2;
            string City;
            string Country;
        };

    Instead of putting all address variables directly inside clsPerson:

        string AddressLine1;
        string AddressLine2;
        string City;
        string Country;

    we group them into one object:

        stAddress Address;

    Then we access the values like this:

        Address.City
        Address.Country


    ------------------------------------------------------------
    WAYS TO USE A STRUCT INSIDE A CLASS
    ------------------------------------------------------------

    1. PRIVATE NESTED STRUCT + PUBLIC OBJECT
       --------------------------------------
       The struct TYPE itself is private, but the class exposes an object of it.

           class clsPerson
           {
               struct stAddress
               {
                   string City;
                   string Country;
               };

           public:
               stAddress Address;
           };

       We can use:

           Person1.Address.City = "London";

       This is the same idea used in the first example below.


    2. PUBLIC NESTED STRUCT TYPE
       --------------------------
       If the struct is public, code outside the class can create objects
       directly from that nested type.

           class clsPerson
           {
           public:
               struct stAddress
               {
                   string City;
                   string Country;
               };
           };

       Then:

           clsPerson::stAddress HomeAddress;

       Notice the scope operator:

           clsPerson::stAddress


    3. STRUCT AS A PRIVATE DATA MEMBER
       --------------------------------
       The class can completely hide the struct object and give access through
       setters/getters or other member functions.

           private:
               stAddress _Address;

       This gives the class more control over its data.


    4. STRUCT AS A FUNCTION PARAMETER
       -------------------------------
       A function can receive the whole struct instead of receiving many
       separate variables.

           void SetAddress(stAddress Address);

       This is cleaner than:

           void SetAddress(string Line1,
                           string Line2,
                           string City,
                           string Country);


    5. STRUCT AS A FUNCTION RETURN TYPE
       ---------------------------------
       A function can return a complete group of related data.

           stAddress GetAddress()
           {
               return _Address;
           }


    6. MANY STRUCT OBJECTS INSIDE ONE CLASS
       -------------------------------------
       Real programs often store a collection of small records inside a class.

       Example:

           vector<stItem> Items;

       This is common in:
           - shopping carts
           - orders
           - invoices
           - game inventories
           - database records
           - network headers


    ------------------------------------------------------------
    IMPORTANT IDEA
    ------------------------------------------------------------

    A nested struct belongs to the scope of the class.

        clsPerson
            |
            +-- stAddress
                    |
                    +-- AddressLine1
                    +-- AddressLine2
                    +-- City
                    +-- Country

    If stAddress is public, its full type name outside clsPerson is:

        clsPerson::stAddress

    A struct inside a class is especially useful when the struct only makes
    sense as part of that class.
*/


#include <iostream>
#include <string>
#include <vector>

using namespace std;


// ============================================================================
// EXAMPLE 1:
// Your original example:
// Private nested struct type + public struct object.
// ============================================================================

class clsPerson
{
    struct stAddress
    {
        string AddressLine1;
        string AddressLine2;
        string City;
        string Country;
    };

public:
    string FullName;
    stAddress Address;

    clsPerson()
    {
        FullName = "Koko ibn Fofo";

        Address.AddressLine1 = "Building 10";
        Address.AddressLine2 = "Queen Street";
        Address.City = "London";
        Address.Country = "United Kingdom";
    }

    void PrintAddress()
    {
        cout << "\nAddress:\n";
        cout << Address.AddressLine1 << endl;
        cout << Address.AddressLine2 << endl;
        cout << Address.City << endl;
        cout << Address.Country << endl;
    }
};


// ============================================================================
// EXAMPLE 2:
// Public nested struct.
//
// Real-life style use:
// A user profile class can expose a small data type that callers are allowed
// to create and pass into the class.
// ============================================================================

class clsCustomer
{
public:

    struct stContactInfo
    {
        string Email;
        string Phone;
    };

private:
    string _Name;
    stContactInfo _ContactInfo;

public:

    clsCustomer(string Name, stContactInfo ContactInfo)
        : _Name(Name), _ContactInfo(ContactInfo)
    {
    }

    void Print()
    {
        cout << "\nCustomer:\n";
        cout << "Name  : " << _Name << endl;
        cout << "Email : " << _ContactInfo.Email << endl;
        cout << "Phone : " << _ContactInfo.Phone << endl;
    }
};


// ============================================================================
// EXAMPLE 3:
// Private struct member + setter/getter.
//
// Real-life style use:
// The class hides its internal address representation and controls access
// through member functions.
// ============================================================================

class clsEmployee
{
public:

    struct stAddress
    {
        string Street;
        string City;
        string Country;
    };

private:
    string _Name;
    stAddress _Address;

public:

    clsEmployee(string Name)
        : _Name(Name)
    {
    }

    void SetAddress(stAddress Address)
    {
        _Address = Address;
    }

    stAddress GetAddress()
    {
        return _Address;
    }

    void Print()
    {
        cout << "\nEmployee:\n";
        cout << "Name    : " << _Name << endl;
        cout << "Street  : " << _Address.Street << endl;
        cout << "City    : " << _Address.City << endl;
        cout << "Country : " << _Address.Country << endl;
    }
};


// ============================================================================
// EXAMPLE 4:
// Collection of structs inside a class.
//
// Real-life style use:
// An order contains many order items.
// Each item is a small record, so a struct is a natural choice.
// ============================================================================

class clsOrder
{
public:

    struct stItem
    {
        string ProductName;
        int Quantity;
        double Price;
    };

private:
    vector<stItem> _Items;

public:

    void AddItem(stItem Item)
    {
        _Items.push_back(Item);
    }

    double GetTotal()
    {
        double Total = 0;

        for (const stItem& Item : _Items)
        {
            Total += Item.Quantity * Item.Price;
        }

        return Total;
    }

    void Print()
    {
        cout << "\nOrder:\n";

        for (const stItem& Item : _Items)
        {
            cout << Item.ProductName
                 << " | Quantity: " << Item.Quantity
                 << " | Price: " << Item.Price
                 << endl;
        }

        cout << "Total: " << GetTotal() << endl;
    }
};


int main(void)
{
    // ------------------------------------------------------------------------
    // Example 1: original clsPerson example.
    // ------------------------------------------------------------------------
    clsPerson Person1;

    Person1.PrintAddress();


    // ------------------------------------------------------------------------
    // Example 2:
    // Because stContactInfo is public, we can create it outside clsCustomer.
    // ------------------------------------------------------------------------
    clsCustomer::stContactInfo Contact1;

    Contact1.Email = "adam@example.com";
    Contact1.Phone = "+44 123456789";

    clsCustomer Customer1("Adam Smith", Contact1);

    Customer1.Print();


    // ------------------------------------------------------------------------
    // Example 3:
    // Pass a complete struct to a class function.
    // ------------------------------------------------------------------------
    clsEmployee::stAddress EmployeeAddress;

    EmployeeAddress.Street = "Main Street 25";
    EmployeeAddress.City = "Vienna";
    EmployeeAddress.Country = "Austria";

    clsEmployee Employee1("John");

    Employee1.SetAddress(EmployeeAddress);
    Employee1.Print();


    // ------------------------------------------------------------------------
    // Example 4:
    // A class stores many objects of its nested struct.
    // ------------------------------------------------------------------------
    clsOrder Order1;

    Order1.AddItem({"Laptop", 1, 900.00});
    Order1.AddItem({"Mouse", 2, 25.00});
    Order1.AddItem({"Keyboard", 1, 60.00});

    Order1.Print();


    return (0);
}
