/**
 * @file main.cpp
 * @author 5EA596
 * @date 2026-02-08
 * @brief Driver program for Lab 1B: Global Roam Multi-File Standards.
 */

#include <iostream>
#include "Passenger.h"

int main()
{
    Passenger passenger1("Ada Lovelace", "12A");
    Passenger passenger2("Alan Turing", "7C");

    std::cout << "=== Global Roam Passenger List ===" << std::endl;
    passenger1.print();
    passenger2.print();

    return 0;
}
