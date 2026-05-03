#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "BST.h"
#include "Employee.h"

using namespace std;

/**
 * @file 5EA596_module_12_main.cpp
 * @author 5EA596
 * @date 2026-04-04
 * @brief Loads employee data from a file into a BST, prints traversals,
 * performs alphabetical search tracing, and demonstrates optional removal.
 *
 * AI Citation:
 * Tool Used: ChatGPT
 * Prompt Summary: Generate a full solution for a templated BST assignment
 * with recursive insert, remove, copy, destroy, traversal functions, file I/O,
 * Employee class support, and search tracing.
 * Changes Made: Adjusted formatting, names, comments, and output wording.
 */

int main()
{
    BST<Employee> directory;

    ifstream infile("employees.txt");

    if (!infile)
    {
        cout << "Error: Could not open employees.txt" << endl;
        return 1;
    }

    string line;

    while (getline(infile, line))
    {
        if (line.empty())
        {
            continue;
        }

        stringstream ss(line);
        string idText;
        string name;

        getline(ss, idText, ',');
        getline(ss, name);

        int id = stoi(idText);
        Employee emp(id, name);
        directory.insert(emp);
    }

    infile.close();

    cout << "--- Global Roam Searchable Directory ---" << endl;
    cout << endl;

    cout << "In-Order (Alphabetical):" << endl;
    directory.inorder();
    cout << endl;

    cout << "Pre-Order:" << endl;
    directory.preorder();
    cout << endl;

    cout << "Post-Order:" << endl;
    directory.postorder();
    cout << endl;

    cout << "Search Trace for Zane:" << endl;
    Employee targetZane(0, "Zane");
    if (directory.search(targetZane))
    {
        cout << "Result: Zane found." << endl;
    }
    else
    {
        cout << "Result: Zane not found." << endl;
    }
    cout << endl;

    cout << "Search Trace for Mike:" << endl;
    Employee targetMike(0, "Mike");
    if (directory.search(targetMike))
    {
        cout << "Result: Mike found." << endl;
    }
    else
    {
        cout << "Result: Mike not found." << endl;
    }
    cout << endl;

    cout << "--- Bonus Removal Test: Removing Sarah ---" << endl;
    Employee targetSarah(0, "Sarah");
    directory.remove(targetSarah);

    cout << "In-Order After Removing Sarah:" << endl;
    directory.inorder();
    cout << endl;

    cout << "Search Trace for Sarah After Removal:" << endl;
    if (directory.search(targetSarah))
    {
        cout << "Result: Sarah found." << endl;
    }
    else
    {
        cout << "Result: Sarah not found." << endl;
    }
    cout << endl;

    cout << "Program ending. Destructor trace will now run." << endl;

    return 0;
}