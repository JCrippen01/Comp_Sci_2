#pragma once
#include <exception>
#include <string>

class InvalidNinjaException : public std::exception {
private:
    std::string message;
public:
    InvalidNinjaException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

class InvalidWeaponException : public std::exception {
private:
    std::string message;
public:
    InvalidWeaponException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

class InvalidChoiceException : public std::exception {
private:
    std::string message;
public:
    InvalidChoiceException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};