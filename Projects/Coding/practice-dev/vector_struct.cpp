#include <iostream>
#include <vector>
using namespace std;

struct stEmployee
{
    string FirstName = "";
    string LastName = "";
    float Salary = 0.0;
};



int main(){
    vector <stEmployee> vEmployee;
    stEmployee tempEmployee;

    tempEmployee.FirstName = "Ahmed";
    tempEmployee.LastName = "Adeel";
    tempEmployee.Salary = 5000;
    vEmployee.push_back(tempEmployee);

    tempEmployee.FirstName = "Alzzohor";
    tempEmployee.LastName = "Adnan";
    tempEmployee.Salary = 3000.70;
    vEmployee.push_back(tempEmployee);

    tempEmployee.FirstName = "Gasim";
    tempEmployee.LastName = "Algasim";
    tempEmployee.Salary = 2500.50;
    vEmployee.push_back(tempEmployee);

    cout << "Employee Vector:\n\n";

    for (stEmployee& Employee : vEmployee)
    {
        cout << "First Name: " << Employee.FirstName << endl;
        cout << "Last Name : " << Employee.LastName << endl;
        cout << "Salary    : " << Employee.Salary << endl << endl;
    }
    cout << "\n";

    return (0);
}


