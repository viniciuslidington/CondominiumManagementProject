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
            cout << "Data válida!" << endl;
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
