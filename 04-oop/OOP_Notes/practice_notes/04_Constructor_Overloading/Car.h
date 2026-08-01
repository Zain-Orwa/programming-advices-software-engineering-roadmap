#include <string>
#include <iostream>

using namespace std;


class Car
{
private:
    string _Maker;
    int    _Model;
    string _Color;

public:
    void    SetMaker(string make);
    string  GetMaker();
    void    SetModel(int mod);
    int     GetModel();

    Car();
    Car(string m, int mo, string c);
    ~Car();
};
