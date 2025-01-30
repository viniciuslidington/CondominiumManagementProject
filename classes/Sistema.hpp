#ifndef SISTEMA_HPP
#define SISTEMA_HPP

#include <iostream>
#include <string>
#include <fstream>
#include "../json.hpp" 
#include "funcoes_json.hpp"
#include <ctime>

using json = nlohmann::json;
using namespace std;

class Sistema {
private:
    bool isDayOfMonth(int day);
    string getMesAtual();
    bool precisaAtualizar(const json& data);
    void removerUsuario(const long& cpf, json& usuariosJson);

public:
    Sistema();
    void atualizarPagamentos();
};

#endif
