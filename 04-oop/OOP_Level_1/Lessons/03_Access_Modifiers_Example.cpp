#include <iostream>

using namespace std;

class Rectangle
{
private:
    float   Length;
    float   Width;

public:
    void    GetLength(float Len = 0)
    {
        cout << "Please Enter Rectangle Length: ";
        cin >> Len;

        while (Len < 0)
        {
            cout << "\nThe Length of the Rectangle can not be negative. Enter Positive Length: ";
            cin >> Len;
        }

        Length = Len;
    }

    void    GetWidth(float Wid = 0)
    {
        cout << "Please Enter Rectangle Width: ";
        cin >> Wid;

        while (Wid < 0)
        {
            cout << "\nThe Width of the Rectangle can not be negative. Enter Positive Width: ";
            cin >> Wid;
        }

        Width = Wid;
    }

    float    GetRectangleArea()
    {
       return (Length * Width); 
    }
};

int main(void)
{
    Rectangle CalculateRect;

    CalculateRect.GetLength();
    CalculateRect.GetWidth();

    cout << "\nThe Area of the Rectangle = " << CalculateRect.GetRectangleArea() << endl;


    return (0);
}