#include <iostream>
#include <fstream>
#include "json.hpp" // Incluir o arquivo json.hpp 
#include "classes/Manager.hpp"
#include "classes/Resident.hpp"
#include "classes/Sistema.hpp"
#include "classes/ValidacaoInputs.hpp"

using namespace std;
using json = nlohmann::json;

unique_ptr<Sistema> IniciarSistema(){
    return make_unique<Sistema>();
}
//Login (Loop para verificar login e acessar funcoes das respectivas classes)
unique_ptr<User> login() {
    string email, senha;
    string caminhoUsuarios = "bdjson/usuarios.json";
    json usuariosJson = carregarArquivo(caminhoUsuarios);

    while (true) {
        cout << "\n===================================\n";
        cout << "||          Bem vindo!           ||\n";
        cout << "===================================\n";
        cout << "|| 1. Login                      ||\n";
        cout << "|| 2. Encerrar o programa        ||\n";
        cout << "===================================\n";
        cout << "Digite sua escolha: ";
        int option;
        cin >> option;

        if (option == 2) {
            return nullptr;
        } else if (option != 1) {
            cout << "Opção inválida. Tente novamente." << endl;
            continue; // Volta ao início do loop
        }

        cout << "\n===================================\n";
        cout << "||           LOGIN               ||\n";
        cout << "===================================\n";
        cout << "Digite seu email: ";
        getline(cin >> ws, email);

        bool emailEncontrado = false;
        for (const auto& usuario : usuariosJson["usuarios"]) {
            if (usuario["email"] == email) {
                emailEncontrado = true;

                cout << "Digite sua senha: ";
                getline(cin >> ws, senha);

                if (usuario["senha"] == senha) {
                    string tipo = usuario["tipo"];
                    string nome = usuario["nome"];
                    string phone = usuario["phone"];
                    long cpf = usuario["cpf"];
                    
                    cout << "\n===================================\n";
                    cout << "|| Login bem-sucedido!           ||\n";
                    cout << "===================================\n";

                    if (tipo == "gestor") {
                        return make_unique<Manager>(nome, email, phone, tipo, senha, cpf);
                    } else if (tipo == "morador") {
                        int unidade = usuario["unidade"];
                        bool pagamento = usuario["pagamento_em_dia"];
                        return make_unique<Resident>(nome, email, phone, tipo, senha, cpf, pagamento, unidade);
                    }
                } else {
                    cout << "\n===================================\n";
                    cout << "|| Senha inválida. Tente novamente. ||\n";
                    cout << "===================================\n";
                }
            }
        }

        if (!emailEncontrado) {
            cout << "\n===================================\n";
            cout << "|| Email não encontrado. Tente novamente. ||\n";
            cout << "===================================\n";
        }
    }

    return nullptr; // Caso o loop seja encerrado sem sucesso
}

int main() {
    int choice;
    int* choicePtr = &choice; // Ponteiro para a escolha do usuário

    // Chama o login e obtém o ponteiro único para o usuário logado
    auto sistema = IniciarSistema();
    sistema->atualizarPagamentos();
    auto usuario = login();
    
    if (!usuario) { // Verifica se o login foi cancelado ou falhou
        cout << "Login cancelado ou inválido. Encerrando o programa." << endl;
        return 1;
    }

    // Após o login, verifica o tipo de usuário usando dynamic_cast
    if (auto manager = dynamic_cast<Manager*>(usuario.get())) {
        while (true) { // Menu do gestor
            cout << "\n===================================\n";
            cout << "   Bem-vindo, gestor " << manager->getName() << "!   \n";
            cout << "===================================\n";
            cout << "|| Escolha uma opção:             ||\n";
            cout << "|| 1. Hub Moradores/Trabalhadores ||\n";
            cout << "|| 2. Hub Ações Condominio        ||\n";
            cout << "|| 3. Exibir Informações          ||\n";
            cout << "|| 4. Sair do Portal              ||\n";
            cout << "===================================\n";
            cout << "Digite sua escolha: ";
            cin >> *choicePtr;

            // Verifica se a entrada é válida
            if (cin.fail()) {
                cin.clear(); // Limpa os erros do buffer
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora entradas inválidas
                cout << "Opção inválida. Por favor, digite um número entre 1 e 4.\n";
                continue;
            }

            switch (*choicePtr) {
                case 1:
                    cout << "\n===================================\n";
                    cout << "|| Hub Moradores/Trabalhadores   ||\n";
                    cout << "===================================\n";
                    cout << "|| 1. Adicionar Morador          ||\n";
                    cout << "|| 2. Remover Morador            ||\n";
                    cout << "|| 3. Adicionar Trabalhador      ||\n";
                    cout << "|| 4. Remover Trabalhador        ||\n";
                    cout << "|| 5. Ver FeedBacks              ||\n";
                    cout << "|| 6. Voltar                     ||\n";
                    cout << "===================================\n";
                    cout << "|| Escolha uma opção: ";
                    cin >> *choicePtr;
                    cout << "===================================\n";

                    switch (*choicePtr) {
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
                            manager->removerFuncionario();
                            break;
                        case 5:
                            manager->verFeedback();
                            break;
                        case 6:
                            cout << "Saindo do Hub Moradores/Trabalhadores...\n";
                            break; // Volta ao menu do gestor
                        default:
                            cout << "Opção inválida. Por favor, digite um número entre 1 e 6.\n";
                            break;
                    }
                    break;

                case 2:
                    cout << "\n===================================\n";
                    cout << "|| Hub Ações Condominio           ||\n";
                    cout << "===================================\n";
                    cout << "|| Escolha uma opção:             ||\n";
                    cout << "|| 1. Adicionar Aviso             ||\n";
                    cout << "|| 2. Mostrar Avisos              ||\n";
                    cout << "|| 3. Reservar área comum         ||\n";
                    cout << "|| 4. Mostrar Reservas            ||\n";
                    cout << "|| 5. Registrar serviço           ||\n";
                    cout << "|| 6. Mostrar serviços            ||\n";
                    cout << "|| 7. Mostrar histórico           ||\n";
                    cout << "|| 8. Voltar                      ||\n";
                    cout << "===================================\n";
                    cout << "Digite sua escolha: ";
                    cin >> *choicePtr;

                    switch (*choicePtr)
                    {
                    case 1:
                        manager->adicionarAvisos();
                        break;
                    case 2:
                        manager->mostrarAvisos();
                        break;
                    case 3:
                        manager->reservarAreaComumManager();
                        break;
                    case 4:
                        manager->mostrarReservas();
                        break;
                    case 5:
                        manager->resgistraServico();
                        break;
                    case 6:
                        manager->mostrarServicos();
                        break;
                    case 7:
                        manager->mostrarHistorico();
                        break;
                    case 8:
                        cout << "Saindo do Hub Ações Condominio...\n";
                        break; // Volta ao menu do gestor
                    default:
                        cout << "Opção inválida. Por favor, digite um número entre 1 e 8.\n";
                        break;
                    }
                    break;
                case 3:
                    manager->exibirInformacoes();
                    break;    
                case 4:
                    cout << "Saindo do Portal\n";
                    return 0; // Sai do menu do gestor
                default:
                    cout << "Opção inválida. Por favor, digite um número entre 1 e 4.\n";
                    break;
            }
        }
    } else if (auto resident = dynamic_cast<Resident*>(usuario.get())) {
        while (true) { // Menu do gestor
            cout << "\n===================================\n";
            cout << "   Bem-vindo, morador " << resident->getName() << "!   \n";
            cout << "===================================\n";
            cout << "|| Escolha uma opção:             ||\n";
            cout << "|| 1. Reservar área comum         ||\n";
            cout << "|| 2. Dar FeedBack ou sugestão    ||\n";
            cout << "|| 3. Ver regras do condomínio    ||\n";
            cout << "|| 4. Ver funcionários            ||\n";
            cout << "|| 5. Ver avisos                  ||\n";
            cout << "|| 6. Realizar Pagamento          ||\n";
            cout << "|| 7. Exibir Informações          ||\n";
            cout << "|| 8. Sair do Portal              ||\n";
            cout << "===================================\n";
            cout << "Digite sua escolha: ";
            cin >> *choicePtr;

            switch (*choicePtr) {
                case 1:
                    resident->reservarAreaComumResident();
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
                case 6:
                    resident->realizarPagamento();
                    break;
                case 7:
                    resident->exibirInformacoes();
                    break;
                case 8:
                    cout << "\n===================================\n";
                    cout << "|| Saindo do menu do morador...  ||\n";
                    cout << "===================================\n";
                    return 0;
                default:
                    cout << "\n===================================\n";
                    cout << "|| Opção inválida. Por favor,    ||\n";
                    cout << "|| digite um número entre 1 e 8. ||\n";
                    cout << "===================================\n";
                    break;
            }
        }
    } else {
        cout << "\n===================================\n";
        cout << "|| Tipo de usuário não           ||\n";
        cout << "|| reconhecido. Encerrando o     ||\n";
        cout << "|| programa.                     ||\n";
        cout << "===================================\n";
        return 1;
    }

    return 0; // Finaliza o programa
}