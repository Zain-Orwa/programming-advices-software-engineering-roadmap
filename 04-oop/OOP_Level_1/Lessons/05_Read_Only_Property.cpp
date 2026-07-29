#include <iostream>

using namespace std;

class clsPerson
{
private:
   string   _FirstName;
   string   _LastName;
   int      _ID = 10;
   
public:

    // Set first name //
    int GetID() // we have only get function (_ID) there is no set function and this read-only id//
    {
        return (_ID);
    } 
    
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

};


int main(void)
{
    clsPerson Person1;

    Person1.SetFirstName("John");
    Person1.SetLastName("Deo");

    cout << "ID        : " << Person1.GetID() << endl;
    cout << "First Name: " << Person1.GetFirstName() << endl;
    cout << "Last Name : " << Person1.GetLastName() << endl;
    cout << "Full Name : " << Person1.FullName() << endl;

    return (0);
}