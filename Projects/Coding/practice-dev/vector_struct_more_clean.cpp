#include <iostream>
#include <vector>
using namespace std;

struct stEmployee
{
    string FristName = "";
    string LastName = "";
    int Salary = 0;
};

stEmployee CreateEmployee(string FristName, string LastName, int Salary){
    return {FristName, LastName, Salary};
}

int main(){
    vector <stEmployee> vEmployee;

    vEmployee.push_back(CreateEmployee("Orwa", "Zain", 10000));
    vEmployee.push_back(CreateEmployee("Aya", "Maher", 5000));
    vEmployee.push_back(CreateEmployee("Maria", "Vieru", 7000));

    for (stEmployee &Employee : vEmployee)
    {
        cout << Employee.FristName << " " << Employee.LastName << " - $" << Employee.Salary << endl;
    }

    return (0);
}
