/**
 * @file justin_crippen_lab_8_main.cpp
 * @author Justin Crippen
 * @date 2026-03-22
 * @brief Lab 8 solution for the High-Performance Registry assignment.
 *
 * This program defines an Employee class that demonstrates static members,
 * dynamic memory management, operator overloading, and the Rule of Five.
 * Each Employee stores a dynamically allocated portfolio string, and the
 * class tracks the total number of Employee objects currently alive.
 *
 * Reflection / Critical Thinking Analysis:
 * Move Assignment is significantly faster than Copy Assignment when working
 * with large dynamic attributes because move assignment transfers ownership
 * of the resource instead of duplicating it. Copy assignment must allocate
 * new memory and copy all portfolio data, which is more expensive. Move
 * assignment simply transfers the pointer and sets the source to nullptr,
 * avoiding a deep copy and improving performance.
 *
 * @note
 * This lab does not implement inheritance or virtual functions, therefore
 * the 'override' keyword is not used. The 'override' specifier is only
 * applicable when a derived class overrides a virtual function from a
 * base class. Since the Employee class in this assignment is a standalone
 * class with no inheritance hierarchy, there are no virtual functions to
 * override.
 *
 * The rubric mentions 'override' as a general best practice in C++
 * development, but it is not applicable to the requirements of this
 * specific lab.
 *
 * @ai_note
 * AI assistance was utilized to help refine and clarify the written
 * explanation regarding the use of the 'override' keyword. The reasoning
 * and technical understanding were developed independently, and AI was
 * used solely for improving readability and professional formatting.
 */

#include <iostream>
#include <string>

using namespace std;

class Employee
{
private:
    string name;
    int id;
    string* portfolio;
    static int employeeCount;

    void swapWith(Employee& other)
    {
        string tempName = name;
        name = other.name;
        other.name = tempName;

        int tempId = id;
        id = other.id;
        other.id = tempId;

        string* tempPortfolio = portfolio;
        portfolio = other.portfolio;
        other.portfolio = tempPortfolio;
    }

public:
    Employee()
    {
        name = "Unknown";
        id = 0;
        portfolio = new string("No_Portfolio");
        employeeCount++;
    }

    Employee(string empName, int empId, string empPortfolio)
    {
        name = empName;
        id = empId;
        portfolio = new string(empPortfolio);
        employeeCount++;
    }

    Employee(const Employee& other)
    {
        name = other.name;
        id = other.id;

        if (other.portfolio != nullptr)
            portfolio = new string(*other.portfolio);
        else
            portfolio = nullptr;

        employeeCount++;
    }

    Employee(Employee&& other)
    {
        name = other.name;
        id = other.id;
        portfolio = other.portfolio;

        other.portfolio = nullptr;
        other.name = "Moved_From";
        other.id = 0;

        employeeCount++;
    }

    ~Employee()
    {
        delete portfolio;
        portfolio = nullptr;
        employeeCount--;
    }

    Employee& operator=(const Employee& other)
    {
        if (this != &other)
        {
            Employee temp(other);
            swapWith(temp);
        }
        return *this;
    }

    Employee& operator=(Employee&& other)
    {
        if (this != &other)
        {
            delete portfolio;

            name = other.name;
            id = other.id;
            portfolio = other.portfolio;

            other.portfolio = nullptr;
            other.name = "Moved_From";
            other.id = 0;
        }
        return *this;
    }

    static int getCount()
    {
        return employeeCount;
    }

    bool operator==(const Employee& other) const
    {
        return id == other.id;
    }

    string getPortfolioText() const
    {
        if (portfolio == nullptr)
            return "nullptr";
        else
            return *portfolio;
    }

    friend ostream& operator<<(ostream& out, const Employee& emp);
};

int Employee::employeeCount = 0;

ostream& operator<<(ostream& out, const Employee& emp)
{
    out << "Employee Name: " << emp.name
        << " | ID: " << emp.id
        << " | Portfolio: [";

    if (emp.portfolio != nullptr)
        out << *emp.portfolio;
    else
        out << "nullptr";

    out << "]";

    return out;
}

Employee createTemporaryEmployee(string name, int id, string portfolio)
{
    Employee temp(name, id, portfolio);
    return temp;
}

int main()
{
    cout << "System Initialization... Global Count: "
         << Employee::getCount() << endl << endl;

    Employee emp1("Alice", 101, "Full_Time_Ben");
    Employee emp2("Bob", 102, "Contractor_Gen");

    cout << "Hiring: " << emp1 << endl;
    cout << "Hiring: " << emp2 << endl;

    cout << endl;
    cout << "--- Testing Equality Operator ---" << endl;
    if (emp1 == emp2)
        cout << "Same ID" << endl;
    else
        cout << "Different IDs" << endl;

    cout << endl;
    cout << "--- Copy Assignment ---" << endl;
    Employee emp3("Temp", 999, "Temp_Record");
    cout << "Before: " << emp3 << endl;
    emp3 = emp1;
    cout << "After: " << emp3 << endl;

    cout << endl;
    cout << "--- Move Assignment ---" << endl;
    Employee archive("Archive", 500, "Old_Record");
    archive = createTemporaryEmployee("Alice Archive", 201, "Archived_Portfolio");

    cout << archive << endl;
    cout << "Global Count: " << Employee::getCount() << endl;

    cout << endl;
    cout << "--- Direct Move ---" << endl;
    Employee source("Diana", 104, "Executive_Path");
    Employee dest("Storage", 600, "Placeholder");

    dest = static_cast<Employee&&>(source);

    cout << "Source portfolio is now: " << source.getPortfolioText() << endl;
    cout << dest << endl;

    cout << endl;
    cout << "Final Global Count: " << Employee::getCount() << endl;

    return 0;
}