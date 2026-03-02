/*
 * Author: 5EA596
 * Course: CISP-1020 Computer Science II
 * Institution: Volunteer State Community College
 * Term: Spring 2026
 * Lab 6: The Generic Swapper
 *
 * ------------------------------------------------------------
 * Critical Thinking Reflection:
 *
 * Pass-by-Reference is mandatory for a swap function because we
 * need to modify the original variables that exist in main().
 *
 * When parameters are passed by value (T), the function receives
 * copies of the variables. Any changes made inside the function
 * affect only the copies, not the originals. Once the function
 * ends, the copies are destroyed and the variables in main()
 * remain unchanged.
 *
 * By using pass-by-reference (T &), the function works directly
 * with the original variables in memory, allowing the swap to
 * permanently modify their values.
 * ------------------------------------------------------------
 */

#include <iostream>
#include <string>

using namespace std;

// Template function definition
template <typename T>
void swapArgs(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}

int main()
{
    cout << "--- Global Roam Utility Test ---" << endl;

    // Integer Test
    cout << "\nTesting Integers..." << endl;
    int int1 = 10;
    int int2 = 20;

    cout << "Before: " << int1 << ", " << int2 << endl;
    swapArgs(int1, int2);
    cout << "After: " << int1 << ", " << int2 << endl;

    // Double Test
    cout << "\nTesting Doubles..." << endl;
    double double1 = 1.5;
    double double2 = 4.5;

    cout << "Before: " << double1 << ", " << double2 << endl;
    swapArgs(double1, double2);
    cout << "After: " << double1 << ", " << double2 << endl;

    // String Test
    cout << "\nTesting Strings..." << endl;
    string str1 = "World";
    string str2 = "Hello";

    cout << "Before: " << str1 << ", " << str2 << endl;
    swapArgs(str1, str2);
    cout << "After: " << str1 << ", " << str2 << endl;

    return 0;
}