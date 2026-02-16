/**
 * *********************************************************
 * @file travelAgent.h
 * @author 5EA596
 * @date 2026-02-15
 * @brief lab_4
 * *********************************************************
 */



#ifndef TRAVELAGENT_H
#define TRAVELAGENT_H

#include "person.h"

/**
 * @class TravelAgent
 * @brief Derived class representing a Global Roam employee travel agent.
 *
 * Inherits Person (is-a relationship) and adds employee ID and
 * current sales total.
 */
class TravelAgent : public Person
{
private:
    int employeeID;      ///< Agent's employee ID number
    double salesTotal;   ///< Agent's current sales total

public:
    /**
     * @brief Constructs a TravelAgent with person + employee data.
     * @param name Agent's name.
     * @param address Agent's address.
     * @param employeeID Agent's employee ID.
     * @param salesTotal Agent's current sales total.
     *
     * Calls Person(name, address) using a member initialization list.
     */
    TravelAgent(const std::string& name,
                const std::string& address,
                int employeeID,
                double salesTotal);

    /**
     * @brief Gets the employee ID.
     * @return Employee ID.
     */
    int getEmployeeID() const;

    /**
     * @brief Gets the sales total.
     * @return Sales total.
     */
    double getSalesTotal() const;

    /**
     * @brief Prints person info, then travel-agent-specific info.
     *
     * Calls Person::printInfo() first, then prints:
     * Employee ID and Current Sales.
     */
    void printInfo() const override;
};

#endif
