#include <iostream>
#include <fstream>
#include "json.hpp" // Inclua o arquivo json.hpp no seu projeto
#include "classes/Manager.hpp"
#include "classes/Resident.hpp"
using namespace std;
using json = nlohmann::json;

unique_ptr<User> login() {
    string email, senha;
    string caminhoUsuarios = "bdjson/usuarios.json";
    json usuariosJson = carregarArquivo(caminhoUsuarios);

    int tentativas = 3; // Limite de tentativas de login

    while (tentativas > 0) {
        cout << "Digite 1 para login ou 2 para encerrar o programa: ";
        int option;
        cin >> option;

        if (option == 2) {
            return nullptr;
        } else if (option != 1) {
            cout << "Opção inválida. Tente novamente." << endl;
            continue; // Volta ao início do loop
        }

        cout << "Digite seu email: ";
        cin >> email;

        bool emailEncontrado = false;
        for (const auto& usuario : usuariosJson["usuarios"]) {
            if (usuario["email"] == email) {
                emailEncontrado = true;

                cout << "Digite sua senha: ";
                cin >> senha;

                if (usuario["senha"] == senha) {
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
                } else {
                    cout << "Senha inválida. Tente novamente." << endl;
                }
            }
        }

        if (!emailEncontrado) {
            cout << "Email não encontrado. Tente novamente." << endl;
        }

        tentativas--; // Reduz uma tentativa
        if (tentativas > 0) {
            cout << "Você tem " << tentativas << " tentativas restantes." << endl;
        } else {
            cout << "Número máximo de tentativas alcançado. Encerrando o programa." << endl;
            return nullptr;
        }
    }

    return nullptr; // Caso o loop seja encerrado sem sucesso
}


int main() {
    
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
}