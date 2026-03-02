#pragma once
#include <string>
#include <stdexcept>
#include "Printable.h"

// Templates must be fully defined in the header file
// The compiler needs the full implementation at compile time
template <typename TFirst, typename TSecond>
class Pair : public Printable {
protected:
    TFirst  first;
    TSecond second;

public:
    Pair(TFirst first, TSecond second) : first(first), second(second) {
        if (first < 0 || second < 0) {
            throw std::invalid_argument("Pair values cannot be negative");
        }
        if (first > second) {
            throw std::invalid_argument(
                "Pair first value cannot exceed second value"
            );
        }
    }

    TFirst  getFirst()  const { return first; }
    TSecond getSecond() const { return second; }

    std::string toString() const override {
        return "(" + std::to_string(first)
             + " - " + std::to_string(second) + ")";
    }

    virtual ~Pair() {}
};