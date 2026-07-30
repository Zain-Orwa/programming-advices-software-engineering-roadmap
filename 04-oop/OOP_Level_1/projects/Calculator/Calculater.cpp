#include <iostream>

using namespace std;

class clsCalculator
{
private:
    float   _Result = 0;
    float   _LastNumber = 0;
    string  _LastOperation = "Clear";
    float   _PreviousResult = 0;

    bool    IsZero(float Number)
    {
        return (Number == 0);
    }
    
public:
    void    Add(float Number)
    {
        _LastNumber = Number;
        _PreviousResult = _Result;
        _LastOperation = "Adding";
        _Result += Number;
    }

    void    Subtract(float Number)
    {
        _LastNumber = Number;
        _PreviousResult = _Result;
        _LastOperation = "Subtracting";
        _Result -= Number;   
    }
    void    Divide(float Number)
    {
        _LastNumber = Number;
        if (IsZero(Number))
        {
            Number = 1;
        }
        _PreviousResult = _Result;
        _LastOperation = "Divide";
        _Result /= Number;   
    }

    void    Multiply(float Number)
    {
        _LastNumber = Number;
        _PreviousResult = _Result;
        _LastOperation = "Multiply";
        _Result *= Number;   
    }

    void    PrintResult()
    {
        if (_LastOperation == "Clear")
        {
            Clear();
        }
        else
        {
            std::cout << "\nResult ";
            std::cout << "After " << _LastOperation << " " << _LastNumber << " is " << _Result << "\n";
        }
    }

    void    Clear()
    {
        #ifdef _WIN32
            system("pause>nul");
        #else
            system("clear");   // -s: silent, -n1: one key, no Enter
        #endif 
    }

};


int main(void)
{
    clsCalculator Calculator1;
    
    Calculator1.Clear();
    Calculator1.PrintResult();
    Calculator1.Add(110);
    Calculator1.PrintResult();

    return (0);
}