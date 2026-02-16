/**
 * *********************************************************
 * @file main.cpp
 * @author 5EA596
 * @date 2026-02-15
 * @brief lab_4
 * *********************************************************
 */



#include "person.h"
#include "travelAgent.h"
#include <iostream>

int main()
{
    std::cout << "--- Testing Base Class (Person) ---\n";
    Person p("John Doe", "123 Maple St");
    p.printInfo();

    std::cout << "\n--- Testing Derived Class (TravelAgent) ---\n";
    TravelAgent a("Sarah Smith", "456 Oak Ln", 999, 50000.00);
    a.printInfo();

    return 0;
}
