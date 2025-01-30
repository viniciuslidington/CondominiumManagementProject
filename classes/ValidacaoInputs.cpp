#include "ValidacaoInputs.hpp"
#include <iostream>
#include <ctime>
#include <sstream>
#include <limits>

using namespace std;

bool validarDataFutura(const string& data) {
    int dia, mes, ano;
    char separador;

    istringstream ss(data);
    if (!(ss >> dia >> separador >> mes >> separador >> ano) || separador != '-') {
        cout << "Formato inválido! Use DD-MM-YYYY." << endl;
        return false;
    }

    time_t t = time(nullptr);
    tm* now = localtime(&t);

    int diaAtual = now->tm_mday;
    int mesAtual = now->tm_mon + 1;
    int anoAtual = now->tm_year + 1900;

    if (ano > anoAtual || (ano == anoAtual && mes > mesAtual) || (ano == anoAtual && mes == mesAtual && dia >= diaAtual)) {
        return true;
    }

    cout << "A data digitada não pode ser no passado!" << endl;
    return false;
}

string solicitarDataValida() {
    string data;
    do {
        cout << "Digite a data em que deseja (DD-MM-YYYY): ";
        getline(cin, data);

        if (validarDataFutura(data)) {
            return data;
        } else {
            cout << "Data inválida" << endl;
            cout << "Deseja tentar novamente? (S/N): ";
            char resposta;
            cin >> resposta;
            cin.ignore();
            if (resposta == 'N' || resposta == 'n') {
                exit(0);
            } else {
                continue;
            }
    }
    } while (true);
}

bool validarCPF(long long cpf) {
    // CPF deve estar entre 11 dígitos (10000000000 a 99999999999)
    if (cpf < 10000000000LL || cpf > 99999999999LL) {
        cout << "CPF inválido! Deve conter exatamente 11 números.\n";
        return false;
    }
    return true;
}

long long solicitarCPF() {
    long long cpf;

    while (true) {
        cout << "Digite o CPF (apenas números, 11 dígitos): ";

        // Lendo a entrada como string para garantir que não pule linhas
        string cpfStr;
        cin >> cpfStr;

        // Verifica se a string contém exatamente 11 números
        if (cpfStr.length() != 11 || cpfStr.find_first_not_of("0123456789") != string::npos) {
            cout << "Entrada inválida! O CPF deve conter apenas 11 números.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpa buffer
            continue;
        }

        // Converte para long long
        cpf = stoll(cpfStr);

        if (validarCPF(cpf)) {
            cout << "CPF válido!\n";
            return cpf;
        }

        // Perguntar se o usuário deseja tentar novamente
        cout << "Deseja tentar novamente? (S/N): ";
        char resposta;
        cin >> resposta;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpa buffer para evitar que pule inputs

        if (resposta == 'N' || resposta == 'n') {
            cout << "Operação cancelada.\n";
            return 0; // Retorna 0 indicando que não foi cadastrado
        }
    }
}