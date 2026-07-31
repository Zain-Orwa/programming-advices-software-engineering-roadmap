#include <iostream>

using namespace std;


class  clsPerson
{
private:

public:
    string  FullName;

    clsPerson()
    {
        cout << "Hi, I'm Constructor!\n";
    }


    ~clsPerson()
    {
        cout << "Hi, I'm Destructor\n";
    } 
};

void    Func1()
{
    std::cout << "Func1():\n";
    clsPerson Person;
}

void    Func2()
{
    std::cout << "\nFunc2():\n";
    clsPerson * Person = new clsPerson;
    //this destructor here will not destroyed till we have to destroyed manually:
   // delete(Person); // uncomment the delete line here and the destructor will appear //
}

int main(void)
{
    Func1();
    Func2();

    // if we use the destructor here pefore the pause it will not appear till we finish the
    // the program, but we can see it in "Func1()" after "Func1()" finishes.
    system("bash -c 'read -rsn1'");
    return (0);
}