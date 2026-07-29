// Here we are going to use declaration specification properties that will helps instead of calling
// the function itself like (SetFirstName) and (GetFirstName), we just use when keyword name and depends
// on the parameters in the case of the set(assign) with the "=" equal sign is going to set the name.
// and is the case of get we just we use that key word again without assignning:


#include <iostream>
#include <string>

using namespace std;

class clsPerson
{
private:
    string _FirstName;

public:
   void   SetFirstName(string FirstName) 
   {
        _FirstName = FirstName;
   }

   string   GetFirstName()
   {
        return (_FirstName);
   }

   // this only works with MSVC, but we can use clang++ like this with this flag[-fdeclspec]:
   // clang++ -fdeclspec 06_Properties_Set_and_Get_through_=_.cpp
   // bare in mind at this point we can't use flags like: -Wall -Wextra -Werror

   __declspec(property(get = GetFirstName, put = SetFirstName)) string FirstName;
};


int main(void)
{
    clsPerson Person1;

    cout << "1. Without using __declspec: ";
    Person1.SetFirstName("Alex");
    cout << Person1.GetFirstName() << endl;

    /* to get this part working compile: clang++ -fdeclspec 06_Properties_Set_and_Get_through_=_.cpp */
    cout << "\n2. Using __declspec: ";
    Person1.FirstName = "Alex";
    cout << Person1.FirstName << endl;

    return (0);
}