#include "Resident.hpp"
#include "ValidacaoInputs.hpp"
#include <iostream>
#include <ctime>

using namespace std;

// Construtor
Resident::Resident(const string& name, const string& email, const string& phone, const string& type, 
                   const string& senha, const long& cpf, bool& pagamento, const int& unidadeNumero) 
    : User(name, email, phone, type, senha, cpf), pagamento_em_dia(pagamento), unidade(unidadeNumero)  {}



const int& Resident::getUnidade() const {return unidade;}

void Resident::reservarAreaComumResident() {
    string areaReservada, dataReservada, caminhoAlugueis;
    json alugueisJson;
    int codigoArea;
    bool dataOcupada = false;

    caminhoAlugueis = "bdjson/condominio.json";
    alugueisJson = carregarArquivo(caminhoAlugueis);

    cout << "\n===================================\n";
    cout << "||   RESERVA DE ÁREA COMUM      ||\n";
    cout << "===================================\n";
    cout << "1: Salão de Festas\n";
    cout << "2: Churrasqueira\n";
    cout << "3: Sauna\n";
    cout << "4: Playground\n";
    cout << "===================================\n";
    cout << "Digite o código da área que deseja reservar: ";
    cin >> codigoArea;
    cin.ignore();

    switch (codigoArea) {
        case 1:
            areaReservada = "Salão de Festas";
            break;
        case 2:
            areaReservada = "Churrasqueira";
            break;
        case 3:
            areaReservada = "Sauna";
            break;
        case 4:
            areaReservada = "Playground";
            break;
        default:
            cout << "\n===================================\n";
            cout << "|| Código de área inválido.      ||\n";
            cout << "|| Aluguel não registrado.       ||\n";
            cout << "===================================\n";
            return;
    }

    do {
        dataReservada = solicitarDataValida();
        dataOcupada = false;

        for (const auto& reserva : alugueisJson["reservas"]) {
            if (reserva["area_reservada"] == areaReservada && reserva["data_reservada"] == dataReservada) {
                cout << "\n===================================\n";
                cout << "|| A área já está reservada     ||\n";
                cout << "|| para essa data. Escolha outra. ||\n";
                cout << "===================================\n";
                dataOcupada = true;
                break;
            }
        }
    } while (dataOcupada);

    json novoAluguel = {
        {"nome_morador", this->user_name},
        {"unidade", this->unidade},
        {"area_reservada", areaReservada},
        {"data_reservada", dataReservada}
    };

    alugueisJson["reservas"].push_back(novoAluguel);
    salvarArquivo(caminhoAlugueis, alugueisJson);

    cout << "\n===================================\n";
    cout << "|| Reserva registrada com sucesso! ||\n";
    cout << "===================================\n";
}


// Função para visualizar avisos
void Resident::verAvisos() {
    string caminhoCondominio = "bdjson/condominio.json";
    json condominioJson = carregarArquivo(caminhoCondominio);

    cout << "\n===================================\n";
    cout << "||        AVISOS GERAIS         ||\n";
    cout << "===================================\n";
    bool encontrouAvisoGeral = false;
    
    for (const auto& aviso : condominioJson["avisos"]) {
        if (aviso["destinatario"] == 0) {
            cout << "- " << aviso["aviso"] << "\n";
            encontrouAvisoGeral = true;
        }
    }
    if (!encontrouAvisoGeral) {
        cout << "Nenhum aviso geral disponível no momento.\n";
    }

    cout << "\n===================================\n";
    cout << "||  AVISOS PARA A UNIDADE " << getUnidade() << "  ||\n";
    cout << "===================================\n";
    bool encontrouAvisoUnidade = false;
    
    for (const auto& aviso : condominioJson["avisos"]) {
        if (aviso["destinatario"] == getUnidade()) {
            cout << "- " << aviso["aviso"] << "\n";
            encontrouAvisoUnidade = true;
        }
    }
    if (!encontrouAvisoUnidade) {
        cout << "Nenhum aviso para sua unidade no momento.\n";
    }
    cout << "===================================\n";
    
    salvarArquivo(caminhoCondominio, condominioJson);
}


// Função para enviar feedback
void Resident::feedback() {
    string feedback, caminhoFeedbacks = "bdjson/condominio.json";
    json feedbacksJson, novoFeedback;
    char resposta;

    feedbacksJson = carregarArquivo(caminhoFeedbacks);

    cout << "\n===================================\n";
    cout << "||      Enviar Feedback         ||\n";
    cout << "===================================\n";
    cout << "Digite seu feedback ou sugestão: \n";
    cin.ignore();
    getline(cin, feedback);

    cout << "\nDeseja se identificar? (S/N): ";
    cin >> resposta;
    cin.ignore();

    if (resposta == 'S' || resposta == 's') {
        novoFeedback = {
            {"feedback", feedback},
            {"morador", this->getName()}
        };
    } else {
        novoFeedback = {
            {"feedback", feedback},
            {"morador", "Anônimo"}
        };
    }

    feedbacksJson["feedbacks"].push_back(novoFeedback);
    salvarArquivo(caminhoFeedbacks, feedbacksJson);

    cout << "\n===================================\n";
    cout << "||  ✅ Feedback enviado com sucesso! ||\n";
    cout << "===================================\n";
}


// Função para visualizar regras
void Resident::verRegras() {
    string caminhoRegras = "bdjson/condominio.json";
    json regrasJson = carregarArquivo(caminhoRegras);

    cout << "\n===================================\n";
    cout << "||     Regras do Condomínio      ||\n";
    cout << "===================================\n\n";

    for (const auto& regra : regrasJson["condominio"]["regras_condominio"].items()) {
        cout << "-----------------------------------\n";
        cout << "📌 Regra: " << regra.key() << "\n";
        cout << "📖 Descrição: " << regra.value().get<std::string>() << "\n";
    }

    cout << "\n===================================\n";
}

// Função para visualizar funcionários
void Resident::verFuncionarios() {
    string caminhoFuncionarios = "bdjson/condominio.json";
    json funcionariosJson = carregarArquivo(caminhoFuncionarios);

    cout << "\n===================================\n";
    cout << "||    Funcionários do Condomínio   ||\n";
    cout << "===================================\n";

    if (funcionariosJson["funcionarios"].empty()) {
        cout << "\nNenhum funcionário cadastrado no momento.\n";
    } else {
        for (const auto& funcionario : funcionariosJson["funcionarios"]) {
            cout << "\n-----------------------------------\n";
            cout << "Nome   : " << funcionario["nome"].get<std::string>() << "\n";
            cout << "Função : " << funcionario["funcao"].get<std::string>() << "\n";
            cout << "Turno  : " << funcionario["turno"].get<std::string>() << "\n";
            cout << "-----------------------------------\n";
        }
    }
}



void Resident::realizarPagamento() {
    const long&  cpf = getCpf();
    string caminhoUsuarios = "bdjson/usuarios.json";
    json usuariosJson = carregarArquivo(caminhoUsuarios);

    string caminhoSistema = "bdjson/sistema.json";
    json sistemaJson = carregarArquivo(caminhoSistema);

    bool encontrado = false;

    // Percorrer a lista de usuários para encontrar o CPF correspondente
    for (auto& user : usuariosJson["usuarios"]) {
        if (user["cpf"] == cpf) {
            if (user["pagamento_em_dia"] == true) {
                cout << "======================================" << endl;
                cout << "STATUS DO PAGAMENTO" << endl;
                cout << "--------------------------------------" << endl;
                cout << "O pagamento já está em dia." << endl;
                cout << "======================================" << endl;
                return;
            }
            // Atualizar status do pagamento
            user["pagamento_em_dia"] = true;
        } 
    }

    // Obter data atual
    time_t t = time(0);
    struct tm* now = localtime(&t);
    char buffer[11]; // Formato YYYY-MM-DD\0
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", now);
    std::string dataAtual(buffer);

    // Adicionar pagamento ao histórico
    for (auto& usuario : sistemaJson["pagamentos"]) {
        if (usuario["user_cpf"] == cpf) {
            usuario["historico"].push_back({{"data", dataAtual}});
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        json novoUsuario = {
            {"user_cpf", cpf},
            {"historico", json::array({
                {{"data", dataAtual}}
            })}
        };
        sistemaJson["pagamentos"].push_back(novoUsuario);
    }

    // Salvar as alterações nos arquivos JSON
    salvarArquivo(caminhoSistema, sistemaJson);
    salvarArquivo(caminhoUsuarios, usuariosJson);

    cout << "======================================" << endl;
    cout << "STATUS DO PAGAMENTO" << endl;
    cout << "--------------------------------------" << endl;
    cout << "Pagamento realizado com sucesso!" << endl;
    cout << "======================================" << endl;
}
