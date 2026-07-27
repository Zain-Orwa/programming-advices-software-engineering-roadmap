#include <iostream>

using namespace std;


class clsPerson 
{

public:
    string FirstName;
    string LastName;

    string FullName()
    {
        return (FirstName + " " + LastName);
    }
}; 

int main()
{
    clsPerson Person1;

    Person1.FirstName = "Mohammed";
    Person1.LastName  = "Abo-Hadhoud";

    cout << Person1.FullName() << endl;

    string s1;

    return (0);
}