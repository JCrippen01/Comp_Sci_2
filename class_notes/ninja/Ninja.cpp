#include "Ninja.h"
#include <iostream>

Ninja::Ninja(std::string name, int rank, int health, int stealth)
    : name(name), rank(rank), health(health),
      stealth(stealth), weapon(nullptr) {

    if (name.empty()) {
        throw InvalidNinjaException("Ninja name cannot be empty");
    }
    if (rank < 1 || rank > 10) {
        throw InvalidNinjaException(
            "Rank must be 1-10, got: " + std::to_string(rank)
        );
    }
    if (health < 1 || health > 100) {
        throw InvalidNinjaException(
            "Health must be 1-100, got: " + std::to_string(health)
        );
    }
    if (stealth < 1 || stealth > 10) {
        throw InvalidNinjaException(
            "Stealth must be 1-10, got: " + std::to_string(stealth)
        );
    }
}

void Ninja::equipWeapon(Weapon* w) {
    if (w == nullptr) {
        throw InvalidWeaponException("Cannot equip a null weapon");
    }
    weapon = w;
    std::cout << "\n[EQUIPPED] " << name
              << " equipped " << w->getName() << "!" << std::endl;
}

void Ninja::attack() const {
    if (weapon == nullptr) {
        throw InvalidWeaponException(
            name + " has no weapon equipped - cannot attack!"
        );
    }
    int damage = weapon->rollDamage();
    std::cout << "\n[ATTACK] " << name
              << " strikes with " << weapon->getName()
              << " for "         << damage << " damage!" << std::endl;
}

std::string Ninja::getName()    const { return name; }
int         Ninja::getRank()    const { return rank; }
int         Ninja::getHealth()  const { return health; }
int         Ninja::getStealth() const { return stealth; }
Weapon*     Ninja::getWeapon()  const { return weapon; }

std::string Ninja::toString() const {
    std::string weaponStr = weapon ? weapon->getName() : "None";
    return "Ninja: "     + name
         + " | Rank: "   + std::to_string(rank)
         + " | HP: "     + std::to_string(health)
         + " | Stealth: "+ std::to_string(stealth) + "/10"
         + " | Weapon: " + weaponStr;
}   