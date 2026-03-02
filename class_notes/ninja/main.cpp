#include <iostream>
#include <vector>
#include <limits>
#include "Ninja.h"
#include "Weapon.h"
#include "Exceptions.h"

// ============================================================
// Helper functions
// ============================================================
int getIntInput(const std::string& prompt) {
    std::cout << prompt;
    int value;
    if (!(std::cin >> value)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw InvalidChoiceException("Invalid input - please enter a number");
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

std::string getStringInput(const std::string& prompt) {
    std::cout << prompt;
    std::string value;
    std::getline(std::cin, value);
    if (value.empty()) {
        throw InvalidChoiceException("Input cannot be empty");
    }
    return value;
}

void displayWeapons(const std::vector<Weapon>& weapons) {
    std::cout << "\n========================================" << std::endl;
    std::cout << "         AVAILABLE WEAPONS              " << std::endl;
    std::cout << "========================================" << std::endl;
    for (int i = 0; i < (int)weapons.size(); i++) {
        std::cout << "[" << (i + 1) << "] " << weapons[i] << std::endl;
        std::cout << "     " << weapons[i].getDescription() << std::endl;
    }
    std::cout << "========================================\n" << std::endl;
}

void displayNinjaStatus(const Ninja& ninja) {
    std::cout << "\n========================================" << std::endl;
    std::cout << "           NINJA STATUS                 " << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << ninja << std::endl;
    if (ninja.getWeapon()) {
        std::cout << "Weapon Stats: " << *ninja.getWeapon() << std::endl;
        std::cout << "Description:  "
                  << ninja.getWeapon()->getDescription() << std::endl;
    }
    std::cout << "========================================\n" << std::endl;
}

// ============================================================
// Main
// ============================================================
int main() {
    srand(time(0));

    std::cout << "========================================" << std::endl;
    std::cout << "       WELCOME TO NINJA SELECTOR        " << std::endl;
    std::cout << "========================================" << std::endl;

    // Build arsenal
    std::vector<Weapon> weapons;
    try {
        weapons.push_back(Weapon("Katana",     "Sword",   15, 30, 6,
            "A classic curved blade. Balanced damage and speed."));
        weapons.push_back(Weapon("Shuriken",   "Thrown",   5, 15, 9,
            "Throwing stars. Low damage but lightning fast."));
        weapons.push_back(Weapon("Nunchaku",   "Blunt",   10, 25, 8,
            "Chained sticks. Fast and unpredictable."));
        weapons.push_back(Weapon("Kusarigama", "Chain",   12, 35, 5,
            "Sickle and chain. High damage but slow."));
        weapons.push_back(Weapon("Tanto",      "Dagger",   8, 20, 10,
            "Short blade. Fastest weapon in the arsenal."));

    } catch (const InvalidWeaponException& e) {
        std::cerr << "[FATAL] Failed to build arsenal: "
                  << e.what() << std::endl;
        return 1;
    }

    // Create ninja
    Ninja* playerNinja = nullptr;
    while (playerNinja == nullptr) {
        try {
            std::string name = getStringInput("\nEnter your ninja name: ");
            int rank         = getIntInput("Enter your rank (1-10): ");
            int health       = getIntInput("Enter your health (1-100): ");
            int stealth      = getIntInput("Enter your stealth (1-10): ");

            playerNinja = new Ninja(name, rank, health, stealth);
            std::cout << "\n[CREATED] Ninja " << name
                      << " is ready!" << std::endl;

        } catch (const InvalidNinjaException& e) {
            std::cerr << "[Ninja Error] " << e.what()
                      << " - Please try again." << std::endl;
        } catch (const InvalidChoiceException& e) {
            std::cerr << "[Input Error] " << e.what()
                      << " - Please try again." << std::endl;
        }
    }

    // Weapon selection
    while (playerNinja->getWeapon() == nullptr) {
        try {
            displayWeapons(weapons);
            int choice = getIntInput("Choose your weapon (enter number): ");

            if (choice < 1 || choice > (int)weapons.size()) {
                throw InvalidChoiceException(
                    "Choice must be between 1 and "
                    + std::to_string(weapons.size())
                );
            }
            playerNinja->equipWeapon(&weapons[choice - 1]);

        } catch (const InvalidChoiceException& e) {
            std::cerr << "[Choice Error] " << e.what()
                      << " - Please try again." << std::endl;
        } catch (const InvalidWeaponException& e) {
            std::cerr << "[Weapon Error] " << e.what()
                      << " - Please try again." << std::endl;
        }
    }

    // Status and attack demo
    displayNinjaStatus(*playerNinja);

    std::cout << "=== ATTACK DEMO - 3 strikes ===" << std::endl;
    try {
        for (int i = 0; i < 3; i++) {
            playerNinja->attack();
        }
    } catch (const InvalidWeaponException& e) {
        std::cerr << "[Attack Error] " << e.what() << std::endl;
    }

    delete playerNinja;

    std::cout << "\n========================================" << std::endl;
    std::cout << "          THANKS FOR PLAYING!           " << std::endl;
    std::cout << "========================================" << std::endl;

    return 0;
}