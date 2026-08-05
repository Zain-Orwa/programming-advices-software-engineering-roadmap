#include <iostream>

using namespace std;

class   clsPerson
{
private:
    int     _ID;
    string  _FirstName;
    string  _LastName;
    string  _FullName;
    string  _Email;
    string  _Phone;
public:
    clsPerson()
    {

    }

    clsPerson(int ID, string FirstName, string LastName, string Email, string Phone)
    {
        _ID        = ID;
        _FirstName = FirstName;
        _LastName  = LastName;
        _FullName  = FirstName + LastName; 
        _Email     = Email;
        _Phone     = Phone;
    }

    // Read-Only member;
    int GetID()
    {
        return (_ID);
    }

    void    SetFirstName(string FirstName)
    {
        _FirstName = FirstName;
    }

    void    SetLastName(string LastName)
    {
        _LastName = LastName;
    }

    void    SetEmail(string Email)
    {
        _Email = Email;
    }

    void    SetPhone(string Phone)
    {
        _Phone = Phone;
    }

    string  GetFirstName()
    {
        return (_FirstName);
    }

    string  GetLastName()
    {
        return (_LastName);
    }
    
    string  GetFullName()
    {
        return (_FirstName + " " + _LastName);
    }

    string  GetEmail()
    {
        return (_Email);
    }

    string  GetPhone()
    {
        return (_Phone);
    }


   void     Print()
   {
        cout << "Info:\n";
        cout << "______________________________________\n";
        cout << "ID        : " << _ID;
        cout << "\nFirst Name: " << _FirstName; 
        cout << "\nLast Name : " << _LastName; 
        cout << "\nFull Name : " << GetFullName(); 
        cout << "\nEmail     : " << _Email; 
        cout << "\nPhone     : " << _Phone; 
        cout << "\n______________________________________\n";
   }      

   void     SendEmail(string Subject, string Body)
   {
        cout << "\nThe following message sent successfully to email: " << _Email;
        cout << "\nSubject: " << Subject;
        cout << "\nBody   : " << Body << endl;
   }

   void     SendMessage(string TextMessage)
   {
        cout << "\nThe following SMS sent successfully to phone: " << _Phone << endl;
        cout << "\n" << TextMessage << endl;
   }
};


class clsEmployee : public clsPerson
{
private:
    string  _Title;
    string  _Department;
    int     _Salary;

public:
    clsEmployee(int ID, string FirstName, string LastName, string Email, string Phone, string Title, string Department, int Salary)
    : clsPerson(ID, FirstName, LastName, Email, Phone)
    {
        _Title = Title;
        _Department = Department;
        _Salary = Salary;
    }

    void    SetTitle(string Title)
    {
        _Title = Title;
    }

    string  GetTitle()
    {
        return (_Title);
    }

    void    SetDepartment(string Department)
    {
        _Department = Department;
    }

    string  GetDepartment()
    {
        return (_Department);
    }

    void    SetSalary(int  Salary)
    {
        _Salary = Salary;
    }

    int GetSalary()
    {
        return (_Salary);
    }


};



int main(void)
{
    clsEmployee Employee1(300, "Joseph", "Jacop", "jj@j.com", "98989898", "CEO", "Accounting", 5000);

    Employee1.Print();

    cout << Employee1.GetTitle()  << endl;
    cout << Employee1.GetDepartment()  << endl;
    cout << Employee1.GetSalary()  << endl;

   
    return (0);
}

// Notes:
/*. If we have a base class and this base class has a parameterized constructor and we have inherited that class
    by another class we going to have an error and we can solve this error by two ways:
    A: we can define a default constructor in the base class but at this case we have to remeber that, we just
    get the error stop complaining but we can't assign any values to the base constructor through the sub 
    constructor.
    B:The ultimate solution is we can called the base constructor inside the sub-constructor and at this case
    we have to send the parameters to base constructor through our sub-constructor.
 */

