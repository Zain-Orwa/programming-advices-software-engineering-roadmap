
/*
                      CLASS
                      clsA
                        │
                describes objects
                        │
                        ▼

               ┌────────────────┐
               │ clsA object    │
               │ int x          │
               └────────────────┘

                        │
              many objects can be
              stored inside a vector
                        │
                        ▼

                vector<clsA> v1

 index      0          1          2          3          4
            │          │          │          │          │
            ▼          ▼          ▼          ▼          ▼
        ┌────────┬────────┬────────┬────────┬────────┐
        │ clsA   │ clsA   │ clsA   │ clsA   │ clsA   │
        │ x = 0  │ x = 1  │ x = 2  │ x = 3  │ x = 4  │
        └────────┴────────┴────────┴────────┴────────┘
            │
            │
            └── v1[0].Print()
                      │
                      ▼
                  this->x
                      │
                      ▼
                      0

 */


#include <iostream>

using namespace std;

class clsA
{
public:
    int _x;
    clsA(int value)
    {
        _x = value;
    }

    void    Print()
    {
        cout << "The value of x = " << _x << endl;
    }
};

int main(void)
{
    vector<clsA> v1;
    int NumberOfObjects = 5;

    // inserting object at the end of the vector 
    for (int i = 0; i < NumberOfObjects; i++)
    {
        v1.push_back(clsA(i));
    }

    // printing object content
    for (int i = 0; i < NumberOfObjects; i++)
    {
        v1[i].Print();
    }


    return (0);
}
