/**
 * *********************************************************
 * @file person.cpp
 * @author 5EA596
 * @date 2026-02-15
 * @brief lab_4
 * *********************************************************
 */



#include "person.h"

Person::Person(const std::string& name, const std::string& address)
    : name(name), address(address)
{
}

std::string Person::getName() const
{
    return name;
}

std::string Person::getAddress() const
{
    return address;
}

void Person::printInfo() const
{
    std::cout << "Name: " << name << '\n';
    std::cout << "Address: " << address << '\n';
}
