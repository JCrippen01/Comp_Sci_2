#pragma once
#include <string>
#include "Printable.h"
#include "Weapon.h"
#include "Exceptions.h"

class Ninja : public Printable {
private:
    std::string name;
    int         rank;
    int         health;
    int         stealth;
    Weapon*     weapon;

public:
    Ninja(std::string name, int rank, int health, int stealth);

    void equipWeapon(Weapon* w);
    void attack() const;

    std::string getName()    const;
    int         getRank()    const;
    int         getHealth()  const;
    int         getStealth() const;
    Weapon*     getWeapon()  const;

    std::string toString() const override;
};