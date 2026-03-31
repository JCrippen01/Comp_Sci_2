/**
 * @file 5EA596_lab_11_main.cpp
 * @author 5EA596
 * @date 2026-03-31
 * @brief Lab 11 - Recursive Luggage Reorganizer (v2.0)
 *
 * @details
 * This program demonstrates object-oriented recursion using a Luggage class.
 * It includes three recursive functions:
 * 1. countdown(int n) for linear recursion,
 * 2. factorial(int n) for recursive mathematical calculation,
 * 3. moveLuggage(...) for branching recursion using Towers of Hanoi logic.
 *
 * In this lab, luggage is represented as objects instead of simple integers.
 * Each object contains both an owner name and a weight, allowing the recursive
 * function to work with meaningful real-world data while still following the
 * same recursive pattern.
 *
 * Mandatory Header Question:
 * How does representing luggage as an Object change the way the recursive
 * function interacts with the data compared to using a simple integer?
 * In terms of memory, what is being stored on the Call Stack during each
 * branching call of moveLuggage?
 *
 * Answer:
 * Representing luggage as an object changes the recursive function because the
 * function is no longer working with only a number. Instead, it must access
 * object attributes such as ownerName and weight when printing and processing
 * each move. The recursive pattern still depends on the integer n to determine
 * how many items are involved, but the actual output now comes from the object
 * data stored in the array.
 *
 * During each branching call of moveLuggage, the Call Stack stores the function
 * parameters for that specific call. This includes the current value of n,
 * the source platform, target platform, auxiliary platform, and the reference
 * to the luggage array. Each recursive call gets its own stack frame, and those
 * frames remain in memory until the base case is reached and the calls begin
 * returning.
 *
 * AI Usage Statement:
 * AI assistance (ChatGPT) was used to help deepen understanding of recursion,
 * specifically how the call stack behaves during both linear and branching
 * recursive functions. It was also used to clarify how the Towers of Hanoi
 * pattern applies to object-based data structures.
 *
 * The code and logic were written and verified independently to ensure full
 * understanding of the recursive process and adherence to assignment requirements.
 *
 */

#include <iostream>
#include <string>
using namespace std;

/**
 * @struct Luggage
 * @brief Represents one piece of luggage in the logistics system.
 */
struct Luggage
{
    string ownerName;   ///< Passenger name
    double weight;      ///< Weight of the luggage in pounds

    /**
     * @brief Default constructor
     */
    Luggage()
    {
        ownerName = "";
        weight = 0.0;
    }

    /**
     * @brief Value constructor
     * @param name Passenger name
     * @param lbs Luggage weight in pounds
     */
    Luggage(string name, double lbs)
    {
        ownerName = name;
        weight = lbs;
    }
};

/**
 * @brief Recursively counts down to zero.
 * @param n Current countdown value
 *
 * Base case:
 * - If n is 0, print "Blastoff!"
 *
 * Recursive case:
 * - Print n
 * - Recurse with n - 1
 */
void countdown(int n)
{
    if (n == 0)
    {
        cout << "Blastoff!" << endl;
        return;
    }

    cout << n << endl;
    countdown(n - 1);
}

/**
 * @brief Recursively calculates factorial.
 * @param n Integer value
 * @return Factorial of n
 *
 * Base case:
 * - If n <= 1, return 1
 *
 * Recursive case:
 * - Return n * factorial(n - 1)
 */
int factorial(int n)
{
    if (n <= 1)
    {
        return 1;
    }

    return n * factorial(n - 1);
}

/**
 * @brief Recursively moves luggage between platforms using Towers of Hanoi logic.
 * @param n Number of luggage pieces to move
 * @param source Source platform name
 * @param target Target platform name
 * @param aux Auxiliary platform name
 * @param items Array of luggage objects
 *
 * @details
 * This function uses branching recursion:
 * 1. Move n - 1 items from source to aux
 * 2. Move the nth item from source to target
 * 3. Move n - 1 items from aux to target
 *
 * The items array is assumed to be ordered from lightest at index 0
 * to heaviest at higher indexes. Therefore, items[n - 1] is the current
 * luggage object being moved in that recursive step.
 *
 * Base case:
 * - If n <= 0, stop recursion
 */
void moveLuggage(int n, string source, string target, string aux, Luggage items[])
{
    if (n <= 0)
    {
        return;
    }

    moveLuggage(n - 1, source, aux, target, items);

    cout << "Moving " << items[n - 1].ownerName
         << "'s luggage (" << items[n - 1].weight
         << " lbs) from " << source
         << " to " << target << endl;

    moveLuggage(n - 1, aux, target, source, items);
}

/**
 * @brief Main driver for Lab 11 recursive tests.
 * @return int Program exit status
 */
int main()
{
    cout << "--- Global Roam Logistics Check ---" << endl;

    cout << "\n[TEST 1] Countdown:" << endl;
    countdown(3);

    cout << "\n[TEST 2] Seating Permutations (Factorial 5): "
         << factorial(5) << endl;

    Luggage items[3] =
    {
        Luggage("Smith", 10.5),
        Luggage("Jones", 25.0),
        Luggage("Brown", 50.2)
    };

    cout << "\n[TEST 3] Reorganizing 3 Pieces (Safety Weight Protocol):" << endl;
    moveLuggage(3, "Platform A", "Platform C", "Platform B", items);

    return 0;
}