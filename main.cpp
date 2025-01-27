#include <iostream>
#include <fstream>
#include "json.hpp" // Inclua o arquivo json.hpp no seu projeto
#include "classes/Manager.hpp"
using namespace std;
using json = nlohmann::json;


int main() {

    // Instanciando um Manage
    
    Manager vinicius("vinicius", "blabla@gmail.com", "81997654232", "manager", "coelhinho123", 22233344455);

    //Adicionando um usuario
    int choice;
    cout << "Escolha uma opção:\n1. Adicionar Morador\n2. Adicionar Trabalhador\n3. Adicionar Aviso\n4.Rent\n";
    cin >> choice;

    switch (choice) {
        case 1:
            vinicius.adicionarUsuarioMorador();
            break;
        case 2:
            vinicius.adicionarNovoFuncionario();
            break;
        case 3:
            vinicius.adicionarAvisos();
            break;
        case 4:
            vinicius.Rent();
        default:
            break;
}
}