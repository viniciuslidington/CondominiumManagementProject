#include <iostream>
#include <fstream>
#include "json.hpp" // Inclua o arquivo json.hpp no seu projeto
#include "classes/Manager.hpp"
using namespace std;
using json = nlohmann::json;


int main() {
    // Instanciando um Manager
    Manager vinicius("vinicius", "blabla@gmail.com", "manager", "coelhinho123", 22233344455);

    //Adicionando um usuario
    vinicius.adicionarUsuario();
   
}
