#include "Resident.hpp"
#include "ValidacaoInputs.hpp"
#include <iostream>
#include <ctime>

using namespace std;

// Construtor
Resident::Resident(const string& name, const string& email, const string& phone, const string& type, 
                   const string& senha, const long& cpf, bool& pagamento, const int& unidadeNumero) 
    : User(name, email, phone, type, senha, cpf), pagamento_em_dia(pagamento), unidade(unidadeNumero)  {}


void Resident::reservarAreaComumResident() {
    string areaReservada, dataReservada, caminhoAlugueis, datateste;
    json alugueisJson;
    int codigoArea;
    bool dataOcupada = false;

    caminhoAlugueis = "bdjson/condominio.json";
    alugueisJson = carregarArquivo(caminhoAlugueis);


    cout << "Digite o código da área que deseja reservar: \n";
    cout << "1: Salao de Festas \n";
    cout << "2: Churrasqueira \n";
    cout << "3: Sauna \n";
    cout << "4: Playgroud \n";
    cout << "\nDigite o código da área que deseja reservar:  \n";

    cin >> codigoArea;
    cin.ignore();

    switch (codigoArea) {
        case 1:
            areaReservada = "Salao de Festas";
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
            cout << "Código de área inválido. Aluguel não registrado." << endl;
            return;
    }

    do {
        dataReservada = solicitarDataValida();
        
        // Verificar se a data já está reservada para a área escolhida
        for (const auto& reserva : alugueisJson["reservas"]) {
            if (reserva["area_reservada"] == areaReservada && reserva["data_reservada"] == dataReservada) {
                cout << "A área já está reservada para essa data. Por favor, escolha outra data." << endl;
                dataOcupada = true;
                break;
            }
        }

        if (!dataOcupada) {
            break;
        }
    } while (true);

    json novoAluguel = {
        {"nome_morador", this->user_name},
        {"unidade", this->unidade},
        {"area_reservada", areaReservada},
        {"data_reservada", dataReservada}
    };

    alugueisJson["reservas"].push_back(novoAluguel);
    salvarArquivo(caminhoAlugueis, alugueisJson);

    cout << "Reserva registrada com sucesso!" << endl;
}

// Função para visualizar avisos
void Resident::verAvisos() {
    string caminhoAvisos;
    json avisosJson;

    caminhoAvisos = "bdjson/condominio.json";
    avisosJson = carregarArquivo(caminhoAvisos);


    

}

// Função para enviar feedback
void Resident::feedback() {
    string feedback, caminhoFeedbacks;
    json feedbacksJson, novoFeedback;
    char resposta;

    caminhoFeedbacks = "bdjson/condominio.json";
    feedbacksJson = carregarArquivo(caminhoFeedbacks);

    cout << "Digite seu feedback ou sugestão: ";
    cin.ignore();
    getline(cin, feedback);

    cout << "Deseja se identificar? (S/N): ";
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

    cout << "Feedback enviado com sucesso!" << endl;
}

// Função para visualizar regras
void Resident::verRegras() {
    string caminhoRegras;
    json regrasJson;
    
    caminhoRegras = "bdjson/condominio.json";
    regrasJson = carregarArquivo(caminhoRegras);

    cout << "Regras do condomínio:\n";
    cout << endl;

    for(const auto& regra : regrasJson["condominio"]["regras_condominio"].items()) {
        cout << "Regra: " << regra.key() << endl;
        cout << "Descrição: " << regra.value().get<std::string>() << endl;
        cout << endl;
    }
}

// Função para visualizar funcionários
void Resident::verFuncionarios() {
    string caminhoFuncionarios;
    json funcionariosJson;

    caminhoFuncionarios = "bdjson/condominio.json";
    funcionariosJson = carregarArquivo(caminhoFuncionarios);

    cout << "Funcionários do condomínio:\n";

    for(const auto& funcionario : funcionariosJson["funcionarios"]) {
        cout << endl;
        cout << "Nome: " << funcionario["nome"].get<std::string>() << endl;
        cout << "Função: " << funcionario["funcao"].get<std::string>() << endl;
        cout << "Turno: " << funcionario["turno"].get<std::string>() << endl;
        cout << endl;
    }

}



// Biblioteca JSON for Modern C++ (nlohmann/json)

void Resident::realizarPagamento(const long& cpf) {
    string caminhoUsuarios = "bdjson/usuarios.json";
    json usuariosJson = carregarArquivo(caminhoUsuarios);

    string caminhoSistema = "bdjson/usuarios.json";
    json sistemaJson = carregarArquivo(caminhoSistema);

    bool encontrado = false;

    // Percorrer a lista de usuários para encontrar o CPF correspondente
    for (auto& user : usuariosJson["usuarios"]) {
        if (user["cpf"] == cpf) {
            if (user["pagamento_em_dia"] == true) {
                std::cout << "O pagamento já está em dia.\n";
                return;
            }

            // Atualizar status do pagamento
            user["pagamento_em_dia"] = true;

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
                json novoUsuario;
                novoUsuario["user_cpf"] = cpf;
                novoUsuario["historico"] = json::array(); // Inicializa um array vazio
                json novaData = {
                    {"data", dataAtual}
                };
                novoUsuario["historico"].push_back(novaData);

                sistemaJson["pagamentos"].push_back(novoUsuario);
            }

            // Salvar as alterações nos arquivos JSON
            salvarArquivo(caminhoSistema, sistemaJson);
            salvarArquivo(caminhoUsuarios, usuariosJson);

            std::cout << "Pagamento realizado com sucesso!\n";
            return;
        }
    }

    std::cerr << "Usuário não encontrado.\n";
}

