#include <iostream>
#include <string>

// ============================================================
// Pair class template - holds any two values of any type
// T1 = type of the first value, T2 = type of the second value
// ============================================================
template <typename T1, typename T2>
class Pair {
private:
    T1 first;   // First value (type determined at compile time)
    T2 second;  // Second value (type determined at compile time)

public:
    // Constructor - initializes both values using an initializer list
    Pair(T1 first, T2 second) : first(first), second(second) {}

    // Getter for the first value
    T1 getFirst() const { return first; }

    // Getter for the second value
    T2 getSecond() const { return second; }

    // Prints both values side by side using the << operator
    // Works with any type that has operator<< defined
    void display() const {
        std::cout << "[ " << first << " | " << second << " ]" << std::endl;
    }
};

// ============================================================
// Ninja class - represents a ninja with a name and rank
// ============================================================
class Ninja {
private:
    std::string name;  // Ninja's name
    int rank;          // Ninja's skill rank

public:
    // Constructor - sets name and rank
    Ninja(std::string name, int rank) : name(name), rank(rank) {}

    // Overloads << so Ninja can be printed directly with cout
    // 'friend' allows access to private members from outside the class
    friend std::ostream& operator<<(std::ostream& os, const Ninja& n) {
        os << "Ninja(" << n.name << ", Rank " << n.rank << ")";
        return os;  // Return the stream to allow chaining (e.g. cout << a << b)
    }
};

// ============================================================
// Weapon class - represents a weapon with a name and damage value
// ============================================================
class Weapon {
private:
    std::string name;  // Weapon's name
    int damage;        // Weapon's damage stat

public:
    // Constructor - sets name and damage
    Weapon(std::string name, int damage) : name(name), damage(damage) {}

    // Overloads << so Weapon can be printed directly with cout
    friend std::ostream& operator<<(std::ostream& os, const Weapon& w) {
        os << "Weapon(" << w.name << ", DMG " << w.damage << ")";
        return os;  // Return the stream to allow chaining
    }
};

// ============================================================
// main - demonstrates the Pair template with different type combos
// ============================================================
int main() {
    // --- Example 1: Pair of two plain strings ---
    // T1 = string, T2 = string
    Pair<std::string, std::string> p1("Naruto", "Kunai");
    p1.display();  // Output: [ Naruto | Kunai ]

    // --- Example 2: Pair of a Ninja object and a Weapon object ---
    // T1 = Ninja, T2 = Weapon
    // The Pair template works with custom classes thanks to operator<< overloading
    Ninja ninja("Shadow", 5);
    Weapon weapon("Shuriken", 42);

    Pair<Ninja, Weapon> p2(ninja, weapon);
    p2.display();  // Output: [ Ninja(Shadow, Rank 5) | Weapon(Shuriken, DMG 42) ]

    // --- Example 3: Pair of a string and an integer ---
    // T1 = string, T2 = int
    // Shows the template works across completely different types
    Pair<std::string, int> p3("Katana", 99);
    p3.display();  // Output: [ Katana | 99 ]

    return 0;  // Program completed successfully
}
