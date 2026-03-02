#pragma once
#include <iostream>
#include <string>

class Printable {
public:
    virtual std::string toString() const = 0;

    friend std::ostream& operator<<(std::ostream& os, const Printable& p) {
        os << p.toString();
        return os;
    }

    virtual ~Printable() {}
};