#ifndef GESTOR_HPP
#define GESTOR_HPP

#include "User.hpp"
#include <string>
#include <iostream>

using namespace std;

class Manager : public User {
public:
    Manager(const string& name, const string& email, const string& type, const string& senha)
        : User(name, email, type, senha) {}

    //Aplicar função de cadastrar novo usuario
};

#endif 