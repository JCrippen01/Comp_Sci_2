/**
 * @file 5EA596_labAI.cpp
 * @author 5EA596
 * @date 2026-02-04
 * @brief Book class for a library inventory system demonstrating proper
 *        encapsulation and AI-assisted development with citation.
 */

#include <iostream>
#include <string>

// [AI CITATION]
// Tool: ChatGPT
// Prompt: "Write a simple C++ class named Book that has a title, author, and page count."
// Changes: Refactored to private member variables, added displayBookInfo() const,
//          ensured output matches exact required format, and used camelCase naming.

class Book {
private:
    std::string title;
    std::string author;
    int pageCount;

public:
    Book(const std::string& t, const std::string& a, int p)
        : title(t), author(a), pageCount(p) {}

    void displayBookInfo() const {
        std::cout << "Entry: " << title << " written by " << author
                  << " (" << pageCount << " pages)" << std::endl;
    }
};

int main() {
    Book b1("The Hobbit", "J.R.R. Tolkien", 310);
    b1.displayBookInfo();
    return 0;
}

/*
ORAL DEFENSE:
Making member variables public breaks encapsulation because outside code can
modify the object's internal state directly, potentially causing invalid or
inconsistent data. Keeping them private ensures changes happen through controlled
methods, which protects data integrity and makes the class safer and easier to maintain.
*/
