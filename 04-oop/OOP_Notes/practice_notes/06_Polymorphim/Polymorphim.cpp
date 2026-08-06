#include <iostream>

using namespace std;

class clsShape
{
private:
    string  _Color;

public:
    clsShape(string C)
    {
        _Color = C;
    }

    virtual int area()
    {
        cout << "Parent class area: " << endl;
        return (0);
    }

    virtual void  draw()
    {
        cout << "\nDraw Parent Shape in " << _Color << " color" << endl;
    }


    virtual void    erase()
    {
        cout << "\nErase the parent shape" << endl;
    }

};


class clsRectangle : public clsShape
{
private:
    int _Length;
    int _Width;

public:
    clsRectangle(int l, int w, string c) : clsShape(c)
    {
        _Length = l;
        _Width = w;
    }

    int area()
    {
        cout << "Rectangle area: " << (_Length * _Width) << endl;
        return (_Length * _Width);
    }


    void    draw()
    {
        cout << "Draw Rectangle " << endl;
    }


    void    erase()
    {
        cout << "The rectangle erased " << endl;
    }

};


class clsCircle : public clsShape
{
private:
    int _Radius;

public:
    clsCircle(int r,  string c) : clsShape(c)
    {
       _Radius = r; 
    }

    int area()
    {
        cout << "\nCircle    area: " << (3.14) * (_Radius * _Radius) << endl;
        return (3.14 * _Radius * _Radius);
    }


    void    draw()
    {
        cout << "Draw Circle " << endl;
    }


    void    erase()
    {
        cout << "The Circle erased " << endl;
    }

};



int main(void)
{
    clsShape   *     Shape_ptr;
    clsRectangle    Rect(10, 7, "Red"); 
    clsCircle       Circ(5, "Yellow");

    //The Poly:
    Shape_ptr = &Rect;
    Shape_ptr->area();
    Shape_ptr->draw();


    // Second Poly
    Shape_ptr = &Circ;
    Shape_ptr->area();
    Shape_ptr->draw();



    return (0);
}