#ifndef RESIDENT_HPP
#define RESIDENT_HPP

#include "User.hpp"
#include <string>
#include <iostream>

using namespace std;

class Resident : public User {
private:
bool pagamento_em_dia;

public:
    Resident(const string& name, const string& email, const string& phone, const string& type, 
    const string& senha, const long& cpf, bool& pagamento)
        : User(name, email, phone, type, senha, cpf) {
            pagamento_em_dia = pagamento;
        }
};
#endif 