#include <iostream>

using namespace std;

class clsA
{
private:

public:
    static int Function1()
    {
        return (10);
    }

    int Function2()
    {
        return (20);
    }
};

int main(void)
{
    // we can call the static function without declaring an object //
    cout << "Using the class: " << clsA::Function1() << endl;

    // and we can access the static function via an object //
    clsA A1, A2, A3;
    cout << "\nUsing A1 object: " << A1.Function1() << endl; 
    cout << "Using A2 object: " << A2.Function1() << endl; 
    cout << "Using A3 object: " << A3.Function1() << endl; 

/*  
    We can't call the function2() from the class becaue function2() is int type not static.
*/

    return (0);
}