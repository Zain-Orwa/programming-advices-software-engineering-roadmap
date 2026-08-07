#pragma once

#include <iostream>
#include "30_clsPerson.h"

using namespace std;

class clsEmployee : public clsPerson
{
private:
    string _Title;
    string _Department;
    int _Salary;

public:
    clsEmployee(int ID, string FirstName, string LastName, string Email, string Phone, string Title, string Department, int Salary)
        : clsPerson(ID, FirstName, LastName, Email, Phone)
    {
        _Title = Title;
        _Department = Department;
        _Salary = Salary;
    }

    void SetTitle(string Title)
    {
        _Title = Title;
    }

    string GetTitle()
    {
        return (_Title);
    }

    void SetDepartment(string Department)
    {
        _Department = Department;
    }

    string GetDepartment()
    {
        return (_Department);
    }

    void SetSalary(int Salary)
    {
        _Salary = Salary;
    }

    int GetSalary()
    {
        return (_Salary);
    }

    void Print()
    {
        cout << "Info:\n";
        cout << "______________________________________\n";
        cout << "ID         : " << GetID();
        cout << "\nFirst Name : " << GetFirstName();
        cout << "\nLast Name  : " << GetLastName();
        cout << "\nFull Name  : " << GetFullName();
        cout << "\nEmail      : " << GetEmail();
        cout << "\nPhone      : " << GetPhone();
        cout << "\nTitle      : " << _Title;
        cout << "\nDepartment : " << _Department;
        cout << "\nSalary     : " << _Salary;
        cout << "\n______________________________________\n";
    }
};
