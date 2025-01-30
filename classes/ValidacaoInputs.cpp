#include "ValidacaoInputs.hpp"
#include <iostream>
#include <ctime>
#include <sstream>

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
    string cpfStr = to_string(cpf);
    if (cpfStr.length() != 11) {
        cout << "CPF deve ter 11 dígitos." << endl;
        return false;
    }

    int soma = 0, resto;
    for (int i = 0; i < 9; ++i) {
        soma += (cpfStr[i] - '0') * (10 - i);
    }
    resto = (soma * 10) % 11;
    if (resto == 10) resto = 0;
    if (resto != (cpfStr[9] - '0')) {
        cout << "CPF inválido." << endl;
        return false;
    }

    soma = 0;
    for (int i = 0; i < 10; ++i) {
        soma += (cpfStr[i] - '0') * (11 - i);
    }
    resto = (soma * 10) % 11;
    if (resto == 10) resto = 0;
    if (resto != (cpfStr[10] - '0')) {
        cout << "CPF inválido." << endl;
        return false;
    }

    return true;
}

long long solicitarCPF() {
    long long cpf;
    do {
        cout << "Digite o CPF: (Somente números) ";
        cin >> cpf;
        if (validarCPF(cpf)) {
            cout << "CPF válido!" << endl;
            return cpf;
        } else {
            cout << "Deseja tentar novamente? (S/N): ";
            char resposta;
            cin >> resposta;
            cin.ignore();
            if (resposta == 'N' || resposta == 'n') {
                break;
            } else {
                continue;
            }
        }
    } while (true);
    return 0;
}