#include <iostream>
#include <string>
using namespace std;

// ============================================================
// 1. SINGLE INHERITANCE
// Animal -> Dog
// ============================================================
namespace SingleInheritance
{
    class Animal
    {
    public:
        void Eat()
        {
            cout << "The animal is eating.\n";
        }
    };

    class Dog : public Animal
    {
    public:
        void Bark()
        {
            cout << "The dog is barking.\n";
        }
    };

    void RunExample()
    {
        cout << "\n1. Single Inheritance\n";

        Dog dog;
        dog.Eat();
        dog.Bark();
    }
}

// ============================================================
// 2. MULTILEVEL INHERITANCE
// Person -> Employee -> Programmer
// ============================================================
namespace MultilevelInheritance
{
    class Person
    {
    public:
        void Introduce()
        {
            cout << "I am a person.\n";
        }
    };

    class Employee : public Person
    {
    public:
        void Work()
        {
            cout << "I am working.\n";
        }
    };

    class Programmer : public Employee
    {
    public:
        void Code()
        {
            cout << "I am writing C++ code.\n";
        }
    };

    void RunExample()
    {
        cout << "\n2. Multilevel Inheritance\n";

        Programmer programmer;
        programmer.Introduce();
        programmer.Work();
        programmer.Code();
    }
}

// ============================================================
// 3. HIERARCHICAL INHERITANCE
//             Shape
//          Shape branches to Circle and Rectangle
// ============================================================
namespace HierarchicalInheritance
{
    class Shape
    {
    public:
        void DisplayType()
        {
            cout << "I am a shape.\n";
        }
    };

    class Circle : public Shape
    {
    public:
        void DrawCircle()
        {
            cout << "Drawing a circle.\n";
        }
    };

    class Rectangle : public Shape
    {
    public:
        void DrawRectangle()
        {
            cout << "Drawing a rectangle.\n";
        }
    };

    void RunExample()
    {
        cout << "\n3. Hierarchical Inheritance\n";

        Circle circle;
        Rectangle rectangle;

        circle.DisplayType();
        circle.DrawCircle();

        rectangle.DisplayType();
        rectangle.DrawRectangle();
    }
}

// ============================================================
// 4. MULTIPLE INHERITANCE
// Printer + Scanner -> AllInOne
// ============================================================
namespace MultipleInheritance
{
    class Printer
    {
    public:
        Printer()
        {
            cout << "Printer constructor\n";
        }

        void Print()
        {
            cout << "Printing a document.\n";
        }

        void Status()
        {
            cout << "Printer status: ready.\n";
        }
    };

    class Scanner
    {
    public:
        Scanner()
        {
            cout << "Scanner constructor\n";
        }

        void Scan()
        {
            cout << "Scanning a document.\n";
        }

        void Status()
        {
            cout << "Scanner status: ready.\n";
        }
    };

    class AllInOne : public Printer, public Scanner
    {
    public:
        AllInOne()
        {
            cout << "AllInOne constructor\n";
        }

        void ShowStatus()
        {
            // Both base classes have Status(), so we specify the class.
            Printer::Status();
            Scanner::Status();
        }
    };

    void RunExample()
    {
        cout << "\n4. Multiple Inheritance\n";

        AllInOne machine;
        machine.Print();
        machine.Scan();

        // Wrong because Status() exists in both base classes:
        // machine.Status();

        // Correct: resolve the ambiguity explicitly.
        machine.Printer::Status();
        machine.Scanner::Status();

        // Or call one clear function defined by the derived class.
        machine.ShowStatus();
    }
}

// ============================================================
// 5. HYBRID INHERITANCE AND THE DIAMOND PROBLEM
//
//              Person
//       Person branches to Student and Employee
//       Student and Employee join in TeachingAssistant
//          TeachingAssistant
// ============================================================
namespace HybridInheritance
{
    class Person
    {
    private:
        string _Name;

    public:
        Person(const string& Name) : _Name(Name)
        {
            cout << "Person constructor\n";
        }

        void SetName(const string& Name)
        {
            _Name = Name;
        }

        string GetName() const
        {
            return _Name;
        }
    };

    // "virtual" makes Student and Employee share one Person base
    // inside the final TeachingAssistant object.
    class Student : virtual public Person
    {
    public:
        Student() : Person("Temporary student")
        {
            cout << "Student constructor\n";
        }

        void Study()
        {
            cout << "Studying.\n";
        }
    };

    class Employee : virtual public Person
    {
    public:
        Employee() : Person("Temporary employee")
        {
            cout << "Employee constructor\n";
        }

        void Work()
        {
            cout << "Working.\n";
        }
    };

    class TeachingAssistant : public Student, public Employee
    {
    public:
        // Because Person is a virtual base, the most-derived class
        // TeachingAssistant is responsible for constructing it.
        TeachingAssistant(const string& Name)
            : Person(Name), Student(), Employee()
        {
            cout << "TeachingAssistant constructor\n";
        }

        void Assist()
        {
            cout << GetName() << " is assisting students.\n";
        }
    };

    void RunExample()
    {
        cout << "\n5. Hybrid Inheritance\n";

        TeachingAssistant assistant("Alex");
        assistant.Study();
        assistant.Work();
        assistant.Assist();

        // Correct: only one shared Person object exists.
        assistant.SetName("John");
        cout << "Updated name: " << assistant.GetName() << '\n';
    }
}

int main()
{
    SingleInheritance::RunExample();
    MultilevelInheritance::RunExample();
    HierarchicalInheritance::RunExample();
    MultipleInheritance::RunExample();
    HybridInheritance::RunExample();

    return 0;
}
