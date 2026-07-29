#include <string>
#include <iostream>

using namespace std;


class Car
{
private:
    string _Maker;
    int    _Model;

public:
    void    SetMaker(string make);
    string  GetMaker();

    void    SetModel(int mod);
    int     GetModel();
};