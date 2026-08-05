#include <iostream>

using namespace std;

class clsPerson
{
private:
    int _ID;
    string _FirstName;
    string _LastName;
    string _FullName;
    string _Email;
    string _Phone;

public:
    clsPerson()
    {
    }

    clsPerson(int ID, string FirstName, string LastName, string Email, string Phone)
    {
        _ID = ID;
        _FirstName = FirstName;
        _LastName = LastName;
        _FullName = FirstName + LastName;
        _Email = Email;
        _Phone = Phone;
    }

    // Read-Only member;
    int GetID()
    {
        return (_ID);
    }

    void SetFirstName(string FirstName)
    {
        _FirstName = FirstName;
    }

    void SetLastName(string LastName)
    {
        _LastName = LastName;
    }

    void SetEmail(string Email)
    {
        _Email = Email;
    }

    void SetPhone(string Phone)
    {
        _Phone = Phone;
    }

    string GetFirstName()
    {
        return (_FirstName);
    }

    string GetLastName()
    {
        return (_LastName);
    }

    string GetFullName()
    {
        return (_FirstName + " " + _LastName);
    }

    string GetEmail()
    {
        return (_Email);
    }

    string GetPhone()
    {
        return (_Phone);
    }

    void Print()
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

    void SendEmail(string Subject, string Body)
    {
        cout << "\nThe following message sent successfully to email: " << _Email;
        cout << "\nSubject: " << Subject;
        cout << "\nBody   : " << Body << endl;
    }

    void SendMessage(string TextMessage)
    {
        cout << "\nThe following SMS sent successfully to phone: " << _Phone << endl;
        cout << "\n"
             << TextMessage << endl;
    }
};

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


class clsProgrammer : public clsEmployee
{
private:
    string  _MainProgrammingLanguage;

public:
    clsProgrammer(int ID, string FirstName, string LastName, string Email, string Phone, string Title, string Department, int Salary, string MainProgrammingLanguage) 
    : clsEmployee(ID, FirstName, LastName, Email, Phone, Title, Department, Salary)
    {
        _MainProgrammingLanguage = MainProgrammingLanguage;
    }


    void  SetProgrammingLanguage(string MainProgrammingLanguage)
    {
        _MainProgrammingLanguage = MainProgrammingLanguage;
    }

    string GetMainProgrammingLanguage()
    {
        return (_MainProgrammingLanguage);
    }

    void    Print()
    {
        cout << "Info:\n";
        cout << "______________________________________\n";
        cout << "ID                   : " << GetID();
        cout << "\nFirst Name           : " << GetFirstName();
        cout << "\nLast Name            : " << GetLastName();
        cout << "\nFull Name            : " << GetFullName();
        cout << "\nEmail                : " << GetEmail();
        cout << "\nPhone                : " << GetPhone();
        cout << "\nTitle                : " << GetTitle();
        cout << "\nDepartment           : " << GetDepartment();
        cout << "\nSalary               : " << GetSalary();
        cout << "\nProgramming Language : " << _MainProgrammingLanguage;
        cout << "\n______________________________________\n";
     
    }

};

int main(void)
{
    clsProgrammer Programmer1(10, "Alex", "John", "aj@j.com", "098765432", "CEO", "ProgrammingAdvices", 5000,
        "C++ Language");

    Programmer1.Print();
    

    return (0);
}
