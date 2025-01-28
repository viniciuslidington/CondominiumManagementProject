#ifndef RESIDENT_HPP
#define RESIDENT_HPP

#include "User.hpp"
#include <string>

using namespace std;

class Resident : public User {

private:
    bool pagamento_em_dia;

public:
    Resident(const string& name, const string& email, const string& phone, const string& type, 
    const string& senha, const long& cpf, bool& pagamento);

    void reservarAreaComum();
    void feedback();
    void verRegras();
    void verFuncionarios();
    void verAvisos();


};
#endif 