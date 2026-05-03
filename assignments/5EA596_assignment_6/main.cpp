/**
 * @file main.cpp
 * @author 5EA596
 * @brief Assignment 6: The Cargo Bin
 *
 * Reflection:
 * Class templates must usually be implemented entirely in the header file
 * because the compiler needs to see the full template definition when it
 * creates a version of the class for a specific type. For example, when the
 * program uses CargoBin<int> or CargoBin<std::string>, the compiler generates
 * those versions during compilation. If the template implementation is hidden
 * in a normal .cpp file, the compiler may not have enough information to
 * generate the needed type-specific code, which can cause linker errors.
 *
 * AI Citation:
 * Tool Used: ChatGPT
 * Prompt Summary: Generate a complete C++ Assignment 6 solution using class
 * templates, heap memory, exception handling, Doxygen comments, and error logging.
 * Changes Made: Formatted code and adjusted names to match the assignment.
 */

#include <iostream>
#include <fstream>
#include <string>
#include "cargobin.h"
#include "ticket.h"

using namespace std;

/**
 * @brief Logs caught exceptions to error_log.txt.
 * @param binType The type of bin where the error happened.
 * @param errorMessage The exception message caught.
 */
void logError(const string& binType, const string& errorMessage) {
    ofstream logFile("error_log.txt", ios::app);

    if (logFile) {
        logFile << "Bin Type: " << binType
                << " | Exception: " << errorMessage << endl;
    }

    logFile.close();
}

int main() {
    cout << "--- Global Roam Cargo Bin Test ---" << endl;

    // Integer Bin Test
    cout << "\n[Integer Bin Test]" << endl;

    try {
        CargoBin<int> intBin(3);

        intBin.push(10);
        intBin.push(20);
        intBin.push(30);

        cout << "Pushed 10, 20, and 30 successfully." << endl;

        intBin.push(40);
    }
    catch (string error) {
        cout << "Caught Exception: " << error << endl;
        logError("Integer Bin", error);
    }

    // String Bin Test
    cout << "\n[String Bin Test]" << endl;

    try {
        CargoBin<string> stringBin(1);

        stringBin.push("Mail");
        cout << "Pushed Mail successfully." << endl;

        cout << "Popped: " << stringBin.pop() << endl;

        stringBin.pop();
    }
    catch (string error) {
        cout << "Caught Exception: " << error << endl;
        logError("String Bin", error);
    }

    // Custom Object Test
    cout << "\n[Ticket Object Bin Test]" << endl;

    try {
        CargoBin<Ticket> ticketBin(2);

        Ticket ticket1(1001, "Sarah");
        ticketBin.push(ticket1);

        cout << "Ticket pushed successfully." << endl;
        cout << "Popped Ticket: " << ticketBin.pop() << endl;
    }
    catch (string error) {
        cout << "Caught Exception: " << error << endl;
        logError("Ticket Bin", error);
    }

    cout << "\nAll tests complete." << endl;
    cout << "Any caught exceptions were written to error_log.txt." << endl;

    return 0;
}