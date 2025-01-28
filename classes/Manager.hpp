#ifndef GESTOR_HPP
#define GESTOR_HPP

#include "User.hpp"
#include <string>
#include <fstream>
#include "../json.hpp" 
#include "funcoes_json.hpp"

using json = nlohmann::json;

class Manager : public User {
public:
    Manager(const string& name, const string& email, const string& phone, const string& type, const string& senha, const long& cpf);

    void adicionarUsuarioMorador();
    void adicionarNovoFuncionario();
    void adicionarAvisos();
    void reservarAreaComumManager();
    void mostrarHistorico(); // Histórico de eventos do condomínio/eventos/avisos
    void resgistraServico();
    void adicionarDespesas();
    void mostrarDespesas();
};

#endif
