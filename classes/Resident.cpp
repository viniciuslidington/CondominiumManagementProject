#include "Resident.hpp"
#include <iostream>

using namespace std;

// Construtor
Resident::Resident(const string& name, const string& email, const string& phone, const string& type, 
                   const string& senha, const long& cpf, bool& pagamento) 
    : User(name, email, phone, type, senha, cpf), pagamento_em_dia(pagamento) {}

// Função para reservar área comum -- COPIAR DA MANAGER
void Resident::reservarAreaComumResident() {
    string areaReservada, dataReservada, caminhoUsuarios, caminhoAlugueis;
    json alugueisJson, usuariosJson;
    int codigoArea, numero_apt;
    bool cpfValido = false;
    long long cpfMorador;

    caminhoUsuarios = "bdjson/unidades.json";
    caminhoAlugueis = "bdjson/condominio.json";

    alugueisJson = carregarArquivo(caminhoAlugueis);

    cout << "Digite o CPF do morador que está reservando o espaço: ";
    cin >> cpfMorador;
    cin.ignore();
    // Verificar se o CPF do morador existe no arquivo de usuários
    usuariosJson = carregarArquivo(caminhoUsuarios);

    for (const auto& usuario : usuariosJson["unidades"]) {
        if (usuario["morador_cpf"] == cpfMorador) {
            cpfValido = true;
            numero_apt = usuario["numero"];
            break;
        }
    }

    if (!cpfValido) {
        cout << "CPF não encontrado no sistema. Aluguel não registrado." << endl;
        return;
    }
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
        cout << "Digite a data em que deseja alugar (DD-MM-YYYY): \n";
        getline(cin, dataReservada);
        
        bool dataOcupada = false;
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
        {"numero_apt", numero_apt},
        {"area_reservada", areaReservada},
        {"data_reservada", dataReservada}
    };

    alugueisJson["reservas"].push_back(novoAluguel);
    salvarArquivo(caminhoAlugueis, alugueisJson);

    cout << "Reserva registrada com sucesso!" << endl;
}

// Função para visualizar avisos
void Resident::verAvisos() {
    cout << "Exibindo avisos para o residente...\n";
    // Código para exibir avisos
}

// Função para enviar feedback
void Resident::feedback() {
    cout << "Enviando feedback...\n";
    // Código para enviar feedback
}

// Função para visualizar regras
void Resident::verRegras() {
    cout << "Exibindo as regras do condomínio...\n";
    // Código para exibir regras
}

// Função para visualizar funcionários
void Resident::verFuncionarios() {
    cout << "Exibindo a lista de funcionários do condomínio...\n";
    // Código para exibir funcionários
}
