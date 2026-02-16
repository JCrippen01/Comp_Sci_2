/**
 * *********************************************************
 * @file travelAgent.cpp
 * @author 5EA596
 * @date 2026-02-15
 * @brief lab_4
 * *********************************************************
 */



#include "travelAgent.h"
#include <iomanip>

TravelAgent::TravelAgent(const std::string& name,
                         const std::string& address,
                         int employeeID,
                         double salesTotal)
    : Person(name, address), employeeID(employeeID), salesTotal(salesTotal)
{
}

int TravelAgent::getEmployeeID() const
{
    return employeeID;
}

double TravelAgent::getSalesTotal() const
{
    return salesTotal;
}

void TravelAgent::printInfo() const
{
    // Print shared info first (Global Roam standard)
    Person::printInfo();

    // Then print agent-specific info
    std::cout << "Employee ID: " << employeeID << '\n';
    std::cout << "Current Sales: $" << std::fixed << std::setprecision(2) << salesTotal << '\n';
}
