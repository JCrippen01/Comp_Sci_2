#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include <string>

/**
 * @file Employee.h
 * @author 5EA596
 * @date 2026-04-04
 * @brief Employee class used as the template type for the BST directory.
 */
class Employee
{
private:
    int id;
    std::string name;

public:
    /**
     * @brief Default constructor.
     */
    Employee() : id(0), name("") {}

    /**
     * @brief Parameterized constructor.
     * @param employeeId The employee ID.
     * @param employeeName The employee name.
     */
    Employee(int employeeId, const std::string& employeeName)
        : id(employeeId), name(employeeName) {}

    /**
     * @brief Returns the employee ID.
     * @return int The employee ID.
     */
    int getId() const
    {
        return id;
    }

    /**
     * @brief Returns the employee name.
     * @return std::string The employee name.
     */
    std::string getName() const
    {
        return name;
    }

    /**
     * @brief Compares employees alphabetically by name.
     * @param other The other Employee object.
     * @return bool True if this employee name comes before the other.
     */
    bool operator<(const Employee& other) const
    {
        return name < other.name;
    }

    /**
     * @brief Compares employees alphabetically by name.
     * @param other The other Employee object.
     * @return bool True if this employee name comes after the other.
     */
    bool operator>(const Employee& other) const
    {
        return name > other.name;
    }

    /**
     * @brief Prints employee data.
     * @param os The output stream.
     * @param emp The employee being printed.
     * @return std::ostream& The updated output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Employee& emp)
    {
        os << emp.id << ", " << emp.name;
        return os;
    }
};

#endif