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
        cout << "2. Remover Morador\n";
        cout << "3. Adicionar Trabalhador\n";
        cout << "4. Adicionar Aviso\n";
        cout << "5. Mostrar Avisos\n";
        cout << "6. Reservar área comum\n";
        cout << "7. Mostrar Reservas\n";
        cout << "8. Registrar serviço\n";
        cout << "9. Mostrar serviços\n";
        cout << "10. Mostrar histórico\n";
        cout << "11. Sair\n";
        cout << "Digite sua escolha: ";
        cin >> choice;

        // Verifica se a entrada é válida
        if (cin.fail()) {
            cin.clear(); // Limpa os erros do buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora entradas inválidas
            cout << "Opção inválida. Por favor, digite um número entre 1 e 8.\n";
            continue;
        }

        switch (choice) {
            case 1:
                manager->adicionarUsuarioMorador();
                break;
            case 2:
                manager->removerUsuarioMorador();
                break;
            case 3:
                manager->adicionarNovoFuncionario();
                break;
            case 4:
                manager->adicionarAvisos();
                break;
            case 5:
                manager->mostrarAvisos();
                break;
            case 6:
                manager->reservarAreaComumManager();
                break;
            case 7:
                manager->mostrarReservas();
                break;
            case 8:
                manager->resgistraServico();
                break;
            case 9:
                manager->mostrarServicos();
                break;
            case 10:
                manager->mostrarHistorico();
                break;
            case 11:
                cout << "Saindo do menu do gestor...\n";
                return 0; // Sai do menu do gestor
            default:
                cout << "Opção inválida. Por favor, digite um número entre 1 e 11.\n";
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
