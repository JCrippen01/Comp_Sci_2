#include "Weapon.h"
#include <cstdlib>

Weapon::Weapon(std::string name, std::string type,
               int minDamage, int maxDamage,
               int speed, std::string description)
    : name(name), type(type),
      damageRange(minDamage, maxDamage),
      speed(speed), description(description) {

    if (name.empty()) {
        throw InvalidWeaponException("Weapon name cannot be empty");
    }
    if (speed < 1 || speed > 10) {
        throw InvalidWeaponException(
            "Weapon speed must be 1-10, got: " + std::to_string(speed)
        );
    }
}

std::string    Weapon::getName()        const { return name; }
std::string    Weapon::getType()        const { return type; }
Pair<int, int> Weapon::getDamageRange() const { return damageRange; }
int            Weapon::getSpeed()       const { return speed; }
std::string    Weapon::getDescription() const { return description; }

int Weapon::rollDamage() const {
    return damageRange.getFirst() +
           rand() % (damageRange.getSecond() -
                     damageRange.getFirst() + 1);
}

std::string Weapon::toString() const {
    return "[ " + name + " | Type: " + type
         + " | Damage: " + damageRange.toString()
         + " | Speed: "  + std::to_string(speed) + "/10 ]";
}