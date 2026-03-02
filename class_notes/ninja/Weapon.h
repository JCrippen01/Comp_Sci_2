#pragma once
#include <string>
#include "Printable.h"
#include "Pair.h"
#include "Exceptions.h"

class Weapon : public Printable {
private:
    std::string    name;
    std::string    type;
    Pair<int, int> damageRange;
    int            speed;
    std::string    description;

public:
    Weapon(std::string name, std::string type,
           int minDamage, int maxDamage,
           int speed, std::string description);

    std::string    getName()        const;
    std::string    getType()        const;
    Pair<int, int> getDamageRange() const;
    int            getSpeed()       const;
    std::string    getDescription() const;
    int            rollDamage()     const;

    std::string toString() const override;
};