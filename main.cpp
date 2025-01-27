#include <iostream>
#include <fstream>
#include "json.hpp" // Inclua o arquivo json.hpp no seu projeto
#include "classes/Manager.hpp"
#include "classes/Resident.hpp"
using namespace std;
using json = nlohmann::json;


unique_ptr<User> login() {
    string email, senha;
    cout << "Digite seu email: ";
    cin >> email;
    cout << "Digite sua senha: ";
    cin >> senha;

    // Simulação: carregando dados do JSON
    
    
    string caminhoUsuarios = "bdjson/usuarios.json";
    json usuariosJson = carregarArquivo(caminhoUsuarios);
    

    // Verificar usuário no JSON
    for (const auto& usuario : usuariosJson["usuarios"]) {
        if (usuario["email"] == email && usuario["senha"] == senha) {
            string tipo = usuario["tipo"];
            string nome = usuario["nome"];
            string phone = usuario["phone"];
            long cpf = usuario["cpf"];

            if (tipo == "manager") {
                return make_unique<Manager>(nome, email, phone, tipo, senha, cpf);
            } else if (tipo == "morador") {
                bool pagamento = usuario["pagamento_em_dia"];
                return make_unique<Resident>(nome, email, phone, tipo, senha, cpf, pagamento);
            }
        }
    }

    cout << "Email ou senha inválidos." << endl;
    return nullptr;
}


int main() {

    // Instanciando um Manage
    
    auto usuario = login();
    if (!usuario) {
        cout << "Falha no login. Encerrando o programa." << endl;
        return 1;
    }

    if (auto manager = dynamic_cast<Manager*>(usuario.get())) {
        int choice;
        cout << "Escolha uma opção:\n1. Adicionar Morador\n2. Adicionar Trabalhador\n3. Adicionar Aviso";
        cin >> choice;

        switch (choice) {
            case 1:
                manager->adicionarUsuarioMorador();
                break;
            case 2:
                manager->adicionarNovoFuncionario();
                break;
            case 3:
                manager->adicionarAvisos();
                break;
            default:
                cout << "Opção inválida!" << endl;
                break;
        }
    } else if (auto resident = dynamic_cast<Resident*>(usuario.get())) {
        cout << "resident iniciado";
    }

    cout << "Encerrando o programa." << endl;
    return 0;


    //Adicionando um usuario
    
}

