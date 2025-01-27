#ifndef GESTOR_HPP
#define GESTOR_HPP

#include "User.hpp"
#include <string>
#include <fstream>
#include "json.hpp" 
using json = nlohmann::json;

class Manager : public User {
public:
    Manager(const string& name, const string& email, const string& phone, const string& type, const string& senha, const long& cpf);

    void adicionarUsuarioMorador();
    void addNewWorker();
    void SendInformation(string type, string mensagem);
    void Rent();
    void ShowHistory();
    void RegisterService();
    void AddExpenses();
    void ShowExpenses();
};

#endif
