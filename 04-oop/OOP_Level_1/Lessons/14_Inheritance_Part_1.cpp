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
    clsEmployee Employee1;

    Employee1.SetFirstName("Mohammed");
    Employee1.SetLastName("Abu-Hadoud");
    Employee1.SetEmail("a@a.com");
    Employee1.Print();
    Employee1.SendEmail("Hi", "How are you boy?");
    Employee1.SendMessage("This message from koko");
    Employee1.SetTitle("CEO");
    Employee1.SetDepartment("management");
    Employee1.SetSalary(5000);

    cout << Employee1.GetTitle() << endl;
    cout << Employee1.GetDepartment() << endl;
    cout << Employee1.GetSalary() << endl;
    
    return (0);
}



