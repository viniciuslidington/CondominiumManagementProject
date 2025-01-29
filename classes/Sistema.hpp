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

    // Função para verificar se hoje é o primeiro dia do mês
    bool isDayOfMonth(int day) ;
public:

    Sistema();

    void atualizarPagamentos();

};

#endif 