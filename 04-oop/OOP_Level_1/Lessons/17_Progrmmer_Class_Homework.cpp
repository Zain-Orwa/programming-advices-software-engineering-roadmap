/*
    Use here the Print() function to show how function-override happened:
    Point_1: funtion override is different from the function-overwrite, function override is to cancel the old
    function with a new function that has the same name and same signature and that is complently different
    from the function overwrite that is going to have the same name but different signature.

    Point_2: Function override is occurs in a base clase and sub-class, the sub-calss has the new function
    and the base class has the old function and after we calling the sub-class is going to geve us what in
    the previous function with and more data from the new function as we can in the example in the print
    function here. in the case of we have a sub-class and we didn't define any new function on it and we
    call the old function from the base class is going to call this old function with it's old data.

    Point_3: how function override works? we just call the old function from the old-class inside the new
    function in the new class. and after we continue to fill out the new data in the new function that is
    in the sub-class. another we can just reimplement the old element of the function that in the base calss
    into the new sub-class function and this also another we just to implement the function override.
    But if we have to reimplement the old function we have to know that if the data member of the base class
    are private we have to call the the data emelment though the getter function for each data memeber that
    is the only only we can access these data members.



*/

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
