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
    string  _Title;
    int     _Salary;
    string  _Department;

public:
    clsPerson(int ID, string FirstName, string LastName, string Email, string Phone, string Title, int Salary,
              string Department)
    {
        _ID        = ID;
        _FirstName = FirstName;
        _LastName  = LastName;
        _FullName  = FirstName + LastName; 
        _Email     = Email;
        _Phone     = Phone;
        _Title     = Title;
        _Salary    = Salary;
        _Department= Department;
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

    void    SetTitle(string Title)
    {
        _Title = Title;
    }

    void    SetSalary(int Salary)
    {
        _Salary = Salary;
    }

    void    SetDepartment(string Department)
    {
        _Department = Department;
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

    string    GetTitle()
    {
       return  (_Title);
    }

    int    GetSalary()
    {
        return (_Salary);
    }

    string    GetDepartment()
    {
        return (_Department);
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
        cout << "\nTitle     : " << _Title; 
        cout << "\nSalary    : " << _Salary; 
        cout << "\nDepartment: " << _Department; 
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

int main(void)
{
    clsPerson Person1(100, "Alex", "Hormozi", "my@email.com", "0911242512", "Manager", 100000, "Marketing");
    Person1.Print();

    Person1.SendEmail("Hi", "How are you?");
    Person1.SendMessage("How are you?");

    return (0);
}



