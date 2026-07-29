#include <iostream>

using namespace std;

class clsPerson
{
private:
   string   _FirstName;
   string   _LastName;
   const string id = "A150";
   
public:
    // Set first name //
    void    SetFirstName(string FirstName)
    {
        _FirstName = FirstName;
    }

    string    GetFirstName()
    {
        return (_FirstName);
    }

    // Set last name //
    void    SetLastName(string LastName)
    {
        _LastName = LastName;
    }

    string    GetLastName()
    {
        return (_LastName);
    }

    string  FullName()
    {
        return (_FirstName + " " + _LastName);
    }

    const string GetID()
    {
        return (id);
    }
};


int main(void)
{
    clsPerson Person1;

    Person1.SetFirstName("John");
    Person1.SetLastName("Deo");

    cout << "First Name: " << Person1.GetFirstName() << endl;
    cout << "Last Name : " << Person1.GetLastName() << endl;
    cout << "Full Name : " << Person1.FullName() << endl;
    cout << "ID        : " << Person1.GetID() << endl;

    return (0);
}