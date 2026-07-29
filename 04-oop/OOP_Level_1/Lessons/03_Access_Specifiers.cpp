#include <iostream>

using namespace std;


class clsPerson
{
private:
    int Variable1 = 5;

    int function1()
    {
        return (40);
    }

protected: 
    int Variable2 = 100;

    int function2()
    {
        return (50);
    }

public:
    string FirstName;
    string LastName;

    string FullName()
    {
        return (FirstName + " " + LastName);
    }

    float   Function3()
    {
        return (function1() + Variable1 + function2() + Variable2);
    }

};

int main()
{
    clsPerson Person1;

    Person1.FirstName = "Alex";
    Person1.LastName = "Hormozi";

    cout << Person1.FullName() << endl;

    cout << Person1.Function3() << endl;

    return (0);
}


