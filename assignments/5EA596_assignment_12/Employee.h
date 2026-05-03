#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include <string>

class Employee {
private:
    int id;
    std::string name;

public:
    Employee() : id(0), name("") {}
    Employee(int id, std::string name) : id(id), name(name) {}

    std::string getName() const {
        return name;
    }

    bool operator<(const Employee& other) const {
        return name < other.name;
    }

    bool operator>(const Employee& other) const {
        return name > other.name;
    }

    friend std::ostream& operator<<(std::ostream& os, const Employee& e) {
        os << e.id << ", " << e.name;
        return os;
    }
};

#endif