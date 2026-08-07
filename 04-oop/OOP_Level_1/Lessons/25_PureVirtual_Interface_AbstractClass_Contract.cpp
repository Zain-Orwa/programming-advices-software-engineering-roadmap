/*
    Pure Virtual Function, Interface, Abstract Class, and Contract
    --------------------------------------------------------------

    1. Pure Virtual Function
       A pure virtual function is a virtual function that ends with = 0.

       Example from this file:

           virtual void Dial(string PhoneNumber) = 0;

       The "= 0" does NOT mean the function returns 0.
       It means the base class does not provide the normal implementation here,
       and derived classes are expected to implement this function.


    2. Abstract Class
       If a class contains at least one pure virtual function, that class becomes
       an abstract class.

       In this example:

           class clsMobile

       is an abstract class because Dial(), SendSMS(), and TakePiture()
       are pure virtual functions.

       Because clsMobile is abstract, we CANNOT create an object directly from it:

           clsMobile Mobile1;   // ERROR


    3. Interface
       C++ does not have an "interface" keyword like some other languages.
       Instead, a class that is mainly made of pure virtual functions is commonly
       used as an interface.

       Here clsMobile acts like an interface because it describes what every
       mobile class must be able to do:

           Dial()
           SendSMS()
           TakePiture()

       clsMobile says WHAT a mobile must be able to do, while the derived
       classes decide HOW they will do it.


    4. Contract
       The pure virtual functions create a contract between the base class
       and every derived class.

                          clsMobile
                              |
                    -------------------
                    |                 |
                 clsiPhone        clsSamsung

       Contract from clsMobile:

           You MUST implement Dial().
           You MUST implement SendSMS().
           You MUST implement TakePiture().

       Therefore both clsiPhone and clsSamsung must provide implementations
       for all three functions.

       If a derived class does NOT implement all pure virtual functions,
       that derived class also remains abstract and we cannot create an object
       from it.


    5. After fulfilling the contract
       clsiPhone implements all three required functions, so we can create:

           clsiPhone iPhone1;

       clsSamsung also implements all three required functions, so we can create:

           clsSamsung Note10;


    Simple idea to remember:

       clsMobile = the CONTRACT / RULES
       clsiPhone = one IMPLEMENTATION of those rules
       clsSamsung = another IMPLEMENTATION of those rules


    NOTE ABOUT THIS EXACT EXAMPLE:
    Because there is no "public:" inside these classes, the functions are private
    by default in C++ classes. They can still be overridden by the derived classes,
    but in a typical interface design these functions are normally placed under
    public: so they can be called through the interface.
*/

#include <iostream>

using namespace std;

class clsMobile
{
    virtual void    Dial(string PhoneNumber) = 0;
    virtual void    SendSMS(string PhoneNumber, string Text) = 0;
    virtual void    TakePiture() = 0;
};

class clsiPhone : public clsMobile
{
    virtual void    Dial(string PhoneNumber)
    {
        (void)PhoneNumber;
    }

    virtual void    SendSMS(string PhoneNumber, string Text)
    {
        (void)PhoneNumber;
        (void)Text;
    }

    virtual void    TakePiture()
    {

    }
};

class clsSamsung : public clsMobile
{
    virtual void    Dial(string PhoneNumber)
    {
        (void)PhoneNumber;
    }

    virtual void    SendSMS(string PhoneNumber, string Text)
    {
        (void)PhoneNumber;
        (void)Text;
    }

    virtual void    TakePiture()
    {

    }
};


int main(void)
{
    // clsMobile Mobile1; // ERROR: clsMobile is an abstract class.

    // These classes fulfilled the clsMobile contract by implementing
    // all of its pure virtual functions, so objects can be created.
    clsiPhone iPhone1;
    clsSamsung Note10;

    return (0);
}
