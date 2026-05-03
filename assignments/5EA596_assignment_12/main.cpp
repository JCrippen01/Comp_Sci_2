#include <iostream>
#include <fstream>
#include <sstream>
#include "BST.h"
#include "Employee.h"

using namespace std;

/**
 * @file 5EA596_module_12_main.cpp
 * @author 5EA596
 * @date 2026-04-04
 *
 * Reflection:
 * BST is faster than vector because it reduces search space each step (O(log n)).
 * Vector must check each element (O(n)).
 *
 * Duplicate names go to the right subtree because insertRec uses < comparison
 * and all others fall into the else branch.
 */

int main() {
    bst<Employee> directory;

    ifstream file("employees.txt");
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, name;

        getline(ss, idStr, ',');
        getline(ss, name);

        int id = stoi(idStr);
        directory.insert(Employee(id, name));
    }

    cout << "\n--- Directory (In-Order) ---\n";
    directory.printInOrder();

    cout << "\n--- Search Trace for Zane ---\n";
    directory.searchByName("Zane");

    cout << "\n--- Removing Sarah ---\n";
    directory.remove(Employee(50, "Sarah"));

    cout << "\n--- Directory After Removal ---\n";
    directory.printInOrder();

    cout << "\n--- Search Trace for Zane After Removal ---\n";
    directory.searchByName("Zane");

    cout << "\n--- Program End ---\n";
    return 0;
}