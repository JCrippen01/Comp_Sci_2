/**
 * @file justin_crippen_module_7_main.cpp
 * @author Justin Crippen
 * @date March 22, 2026
 * @brief Midterm Remediation Assignment - Polymorphism and Dynamic Memory
 *
 * @details
 * This program demonstrates object-oriented programming concepts including
 * abstract base classes, inheritance, and polymorphism. A base class
 * (TravelPackage) is defined with a pure virtual function, making it abstract.
 *
 * Three derived classes (LandTour, LuxuryCruise, and Flight) implement their
 * own versions of calculateTotal() using different pricing logic.
 *
 * The program dynamically allocates objects, stores them in a vector of
 * base-class pointers, and uses polymorphism to calculate totals.
 *
 * Proper memory management is demonstrated using a virtual destructor and
 * deleting all allocated objects to prevent memory leaks.
 */

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

/**
 * @class TravelPackage
 * @brief Abstract base class representing a generic travel package.
 */
class TravelPackage
{
protected:
    string customerName; ///< Customer name
    double basePrice;    ///< Base price of package

public:
    /**
     * @brief Constructor initializes base data.
     */
    TravelPackage(string name, double price)
    {
        customerName = name;
        basePrice = price;
    }

    /**
     * @brief Pure virtual function for calculating total cost.
     * @return double Total cost
     */
    virtual double calculateTotal() = 0;

    /**
     * @brief Virtual destructor ensures correct cleanup.
     */
    virtual ~TravelPackage()
    {
        cout << " TravelPackage closed." << endl;
    }

    /**
     * @brief Returns customer name.
     */
    string getCustomerName()
    {
        return customerName;
    }
};

/**
 * @class LandTour
 * @brief Land-based travel package with guide fee.
 */
class LandTour : public TravelPackage
{
private:
    double guideFee;

public:
    LandTour(string name, double price, double fee)
        : TravelPackage(name, price)
    {
        guideFee = fee;
    }

    double calculateTotal()
    {
        return basePrice + guideFee;
    }

    ~LandTour()
    {
        cout << "LandTour for " << customerName;
    }
};

/**
 * @class LuxuryCruise
 * @brief Cruise package with surcharge and port tax.
 */
class LuxuryCruise : public TravelPackage
{
private:
    double portTax;

public:
    LuxuryCruise(string name, double price, double tax)
        : TravelPackage(name, price)
    {
        portTax = tax;
    }

    double calculateTotal()
    {
        return (basePrice * 1.05) + portTax;
    }

    ~LuxuryCruise()
    {
        cout << "LuxuryCruise for " << customerName;
    }
};

/**
 * @class Flight
 * @brief Flight package with tax and fuel surcharge.
 */
class Flight : public TravelPackage
{
private:
    double tax;
    double fuelSurcharge;

public:
    Flight(string name, double price, double t, double fuel)
        : TravelPackage(name, price)
    {
        tax = t;
        fuelSurcharge = fuel;
    }

    double calculateTotal()
    {
        return basePrice + tax + fuelSurcharge;
    }

    ~Flight()
    {
        cout << "Flight for " << customerName;
    }
};

int main()
{
    cout << fixed << setprecision(2);

    /**
     * Instantiation Experiment:
     * The line below would cause a compilation error because TravelPackage
     * is an abstract class due to the pure virtual function calculateTotal().
     * Abstract classes cannot be instantiated directly.
     */
    // TravelPackage trip("John Doe", 1000.00); // ERROR

    vector<TravelPackage*> packages;

    // LandTour objects
    packages.push_back(new LandTour("Sarah Jenkins", 1000.00, 250.00));
    packages.push_back(new LandTour("Michael Chen", 3200.50, 250.00));
    packages.push_back(new LandTour("Elena Rodriguez", 1800.00, 300.00));

    // LuxuryCruise objects
    packages.push_back(new LuxuryCruise("David Lee", 2000.00, 175.00));
    packages.push_back(new LuxuryCruise("Priya Patel", 3500.00, 225.50));
    packages.push_back(new LuxuryCruise("James Walker", 4200.00, 310.25));

    // Flight objects
    packages.push_back(new Flight("Ava Thompson", 500.00, 80.00, 45.00));
    packages.push_back(new Flight("Noah Garcia", 920.00, 120.00, 60.00));
    packages.push_back(new Flight("Olivia Martinez", 1450.00, 160.00, 95.00));

    cout << "=== Package Totals ===" << endl;

    for (int i = 0; i < packages.size(); i++)
    {
        cout << "Total for " << packages[i]->getCustomerName()
             << ": $" << packages[i]->calculateTotal() << endl;
    }

    cout << endl;
    cout << "=== Memory Cleanup ===" << endl;

    /**
     * Memory Management Explanation:
     * The destructor in the base class is virtual so that when deleting objects
     * through a base-class pointer, the correct derived class destructor runs first.
     * If it were not virtual, only the base destructor would execute, causing
     * partial destruction and potential memory leaks.
     */

    for (int i = 0; i < packages.size(); i++)
    {
        delete packages[i];
    }

    return 0;
}