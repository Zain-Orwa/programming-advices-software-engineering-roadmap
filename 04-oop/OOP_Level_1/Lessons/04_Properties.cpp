#include <iostream>

using namespace std;

class clsPerson
{
private:
   string   _FirstName;
   string   _LastName;
   
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
};


int main(void)
{
    clsPerson Person1;

    Person1.SetFirstName("John");
    Person1.SetLastName("Deo");

    cout << Person1.FullName() << endl;

    return (0);
}