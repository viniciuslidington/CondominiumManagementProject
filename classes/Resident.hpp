#ifndef RESIDENT_HPP
#define RESIDENT_HPP

#include "User.hpp"
#include <string>
#include <iostream>

using namespace std;

class Resident : public User {
public:
    Resident(const string& name, const string& email, const string& type, const string& senha, const int& cpf)
        : User(name, email, type, senha, cpf) {}
};
#endif 