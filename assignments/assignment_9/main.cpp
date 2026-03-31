/**
 * @file main.cpp
 * @author 5EA596
 * @date March 26, 2026
 * @brief Driver program for Assignment 9.
 *
 * Builds a custom doubly linked list, prints it forward and backward,
 * compares it to std::list, and demonstrates a bonus custom iterator.
 *
 * [AI CITATION]
 * ChatGPT was used to clarify the STL comparison requirement using
 * std::list reverse iterators and to reinforce how a custom nested
 * iterator can support STL-style traversal with overloaded operators.
 */

#include <iostream>
#include <list>
#include <string>
#include "Itinerary.h"

using namespace std;

/**
 * @brief Main entry point of the program.
 * @return int Exit status
 */
int main()
{
    Itinerary myList;

    myList.append("London");
    myList.append("Paris");
    myList.append("Tokyo");

    cout << "--- Standard Requirement Output ---" << endl;
    myList.printForward();
    myList.printReverse();
    cout << endl;

    list<string> stlList;
    stlList.push_back("London");
    stlList.push_back("Paris");
    stlList.push_back("Tokyo");

    cout << "--- STL Comparison Output ---" << endl;
    cout << "std::list Reverse Iterator: ";

    for (list<string>::reverse_iterator it = stlList.rbegin(); it != stlList.rend(); ++it)
    {
        cout << *it << " ";
    }

    cout << endl << endl;

    cout << "--- [BONUS] Senior Engineer Iterator Trace ---" << endl;
    cout << "Traversing custom list via overloaded Iterator ++:" << endl;

    for (Itinerary::Iterator it = myList.begin(); it != myList.end(); ++it)
    {
        cout << ">> Visiting: " << *it << endl;
    }

    cout << endl;
    cout << "Memory secured (Destructor called)." << endl;

    return 0;
}