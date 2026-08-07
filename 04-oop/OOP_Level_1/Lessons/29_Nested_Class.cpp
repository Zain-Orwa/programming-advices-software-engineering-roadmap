#include <iostream>
#include <string>
#include <vector>

using namespace std;

class clsPerson
{
    class clsAddress
    {
    public:
        string AddressLine1;
        string AddressLine2;
        string City;
        string Country;

        void    Print()
        {
            cout << "Address:\n";
            cout << AddressLine1 << endl;
            cout << AddressLine2 << endl;
            cout << City << endl;
            cout << Country << endl; 
        }
    };
public:
    string FullName;
    clsAddress Address;

    clsPerson()
    {
        FullName = "Koko Fofo";

        Address.AddressLine1 = "Building 10";
        Address.AddressLine2 = "Queen Street";
        Address.City = "London";
        Address.Country = "United Kingdom";
    }

};


int main(void)
{
    clsPerson   Person1;
    Person1.Address.Print();

    return (0);
}

