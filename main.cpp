#include <iostream>
#include <fstream>
#include "json.hpp" // Inclua o arquivo json.hpp no seu projeto
#include "classes/Manager.hpp"
#include "classes/Resident.hpp"
using namespace std;
using json = nlohmann::json;

//Login (Loop para verificar login e acessar funcoes das respectivas classes)
unique_ptr<User> login() {
    string email, senha;
    string caminhoUsuarios = "bdjson/usuarios.json";
    json usuariosJson = carregarArquivo(caminhoUsuarios);

    while (true) {
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

                    if (tipo == "gestor") {
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
    }

    return nullptr; // Caso o loop seja encerrado sem sucesso
}

int main() {
    // Chama o login e obtém o ponteiro único para o usuário logado
    auto usuario = login();
    
    if (!usuario) { // Verifica se o login foi cancelado ou falhou
        cout << "Login cancelado ou inválido. Encerrando o programa." << endl;
        return 1;
    }

    // Após o login, verifica o tipo de usuário usando dynamic_cast
    if (auto manager = dynamic_cast<Manager*>(usuario.get())) {
        while (true) { // Menu do gestor
            int choice;
            cout << "\nEscolha uma opção:\n";
            cout << "1. Adicionar Morador\n";
            cout << "2. Adicionar Trabalhador\n";
            cout << "3. Adicionar Aviso\n";
            cout << "4. Reservar área comum\n";
            cout << "5. Mostrar histórico\n";
            cout << "6. Registrar serviço\n";
            cout << "7. Adicionar despesas\n";
            cout << "8. Mostrar despesas\n";
            cout << "Digite sua escolha: ";
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
                case 4:
                    manager->reservarAreaComumManager();
                    break;
                case 5:
                    manager->mostrarHistorico();
                    break;
                case 6:
                    manager->resgistraServico();
                    break;
                case 7:
                    manager->adicionarDespesas();
                    break;
                case 8:
                    manager->mostrarDespesas();
                    break;
                default:
                    cout << "Opção inválida. Tente novamente." << endl;
                    break;
            }
        }
    } else if (auto resident = dynamic_cast<Resident*>(usuario.get())) {
        while (true) { // Menu do gestor
            int choice;
            cout << "\nEscolha uma opção:\n";
            cout << "1. Adicionar Morador adicional\n";
            cout << "2. Reservar área comum\n";
            cout << "3. Dar FeedBack ou sugestão\n";
            cout << "4. Ver regras do condomínio\n";
            cout << "5. Ver funcionários\n";
            cout << "6. Ver avisos\n";
            cout << "7. Sair\n";
            cout << "Digite sua escolha: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    resident->reservarAreaComum();
                    break;
                case 2:
                    resident->feedback();
                    break;
                case 3:
                    resident->verRegras();
                    break;
                case 4:
                    resident->verFuncionarios();
                    break;
                case 5:
                    resident->verAvisos();
                    break;
                default:
                    cout << "Opção inválida. Tente novamente." << endl;
                    break;
            }
        }
    } else {
        cout << "Tipo de usuário não reconhecido. Encerrando o programa." << endl;
        return 1;
    }

    return 0; // Finaliza o programa
}
