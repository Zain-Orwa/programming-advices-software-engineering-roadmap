#include <iostream>
#include <string>

using namespace std;

class clsPerson
{
private:
    string _FullName;

public:
    class clsAddress
    {
    private:
        string _AddressLine1;
        string _AddressLine2;
        string _City;
        string _Country;

    public:
        clsAddress(string Address1, string Address2, string City, string Country)
        {
            _AddressLine1 = Address1;
            _AddressLine2 = Address2;
            _City = City;
            _Country = Country;
        }

        void SetAddressLine1(string Address1)
        {
            _AddressLine1 = Address1;
        }

        string GetAddressLine1()
        {
            return (_AddressLine1);
        }

        void SetAddressLine2(string Address2)
        {
            _AddressLine2 = Address2;
        }

        string GetAddressLine2()
        {
            return (_AddressLine2);
        }

        void    SetCity(string City)
        {
            _City = City;
        }

        string  GetCity()
        {
            return (_City);
        }

        void    SetCountry(string Country)
        {
            _Country = Country;
        }

        string  GetCountry()
        {
            return (_Country);
        }

        void    Print()
        {
            cout << "Address:\n";
            cout << "Address Line1 : " << _AddressLine1 << endl;
            cout << "Address Line2 : " << _AddressLine2 << endl;
            cout << "City          : " << _City << endl;
            cout << "Country       : " << _Country << endl;
        }
    };

    void  SetFullName(string FullName)
    {
        _FullName = FullName;
    }

    string  GetFullName()
    {
        return (_FullName);
    }

    // rare way of using it:
   /*  clsAddress Address{"", "", "", ""};    
    clsPerson(string FullName, string Address1, string Address2, string City, string Country)
    {
        _FullName = FullName;
        Address = clsAddress(Address1, Address2, City, Country);
    } */

    // using initialization list //
    clsAddress Address;
    clsPerson(string FullName, string Address1, string Address2, string City, string Country)
         : _FullName(FullName), Address(Address1, Address2, City, Country)
    {

    }
};

int main(void)
{
    clsPerson Person1("Jacob Jonathan", "Street E", "Building03", "Ventom", "Veve");

    Person1.Address.Print();

    return (0);
}