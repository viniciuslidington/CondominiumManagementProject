#include "Manager.hpp"

Manager::Manager(const string& name, const string& email, const string& phone, const string& type, const string& senha, const long& cpf)
    : User(name, email, phone, type, senha, cpf) {}

void Manager::adicionarUsuarioMorador() {
    string email, senha, nome, telefone;
    int unidade;
    long cpf;

    ifstream arquivoEntrada("dados.json");
    if (!arquivoEntrada.is_open()) {
        cerr << "Erro ao abrir o arquivo dados.json" << endl;
        return;
    }

    json dados;
    arquivoEntrada >> dados;
    arquivoEntrada.close();

    cout << "Digite o email do novo usuário: ";
    cin >> email;
    cout << "Digite a senha do novo usuário: ";
    cin >> senha;
    cout << "Digite o nome do novo usuário: ";
    cin.ignore();
    getline(cin, nome);
    cout << "Digite o cpf do novo usuario, somente os numeros: ";
    cin >> cpf;
    cout << "Digite o telefone do novo usuario: ";
    cin >> telefone;
    cout << "Digite o numero do apartamento: ";
    cin >> unidade;

    for (auto& unidadeObj : dados["dados"]["unidades"]) {
        if (unidadeObj["numero"] == unidade) {
            if (unidadeObj["ocupado"]) {
                cout << "A unidade " << unidade << " já está ocupada!" << endl;
                cout << "Por favor, escolha outra unidade ou tente novamente mais tarde." << endl;
                return;
            }

            unidadeObj["ocupado"] = true;
            unidadeObj["morador_cpf"] = cpf;

            json novoUsuario = {
                {"cpf", cpf},
                {"email", email},
                {"nome", nome},
                {"senha", senha},
                {"tipo", "Morador"},
                {"pagamento_em_dia", true},
                {"telefone", telefone}
            };
            dados["dados"]["usuarios"].push_back(novoUsuario);

            cout << "Usuario " << nome << " adicionado com sucesso à unidade " << unidade << "!" << endl;

            ofstream arquivoSaida("dados.json");
            if (!arquivoSaida.is_open()) {
                cerr << "Erro ao abrir o arquivo para salvar os dados." << endl;
                return;
            }
            arquivoSaida << dados.dump(4);
            arquivoSaida.close();
            return;
        }
    }

    cout << "Unidade " << unidade << " nao encontrada!" << endl;
}

void Manager::addNewWorker() {
    string nome, turno, funcao;
    int cod_funcionario;
    char opcao;

    ifstream arquivoEntrada("dados.json");
    if (!arquivoEntrada.is_open()) {
        cerr << "Erro ao abrir o arquivo dados.json" << endl;
        return;
    }

    json dados;
    arquivoEntrada >> dados;
    arquivoEntrada.close();

    bool funcionarioValido;
    do {
        funcionarioValido = true;
        cout << "Digite o codigo do funcionario que deseja adicionar: ";
        cin >> cod_funcionario;

        for (const auto& funcionarioObj : dados["dados"]["funcionarios"]) {
            if (funcionarioObj["codigo"] == cod_funcionario) {
                cout << "O codigo " << cod_funcionario << " já está em uso!" << endl;
                cout << "Deseja tentar novamente? (S para Sim / N para Não): ";
                cin >> opcao;

                if (toupper(opcao) == 'N') {
                    return;
                } else {
                    funcionarioValido = false;
                    break;
                }
            }
        }
    } while (!funcionarioValido);

    cin.ignore();
    cout << "Digite o nome do funcionario: ";
    getline(cin, nome);
    cout << "Digite o turno do funcionario: ";
    getline(cin, turno);
    cout << "Digite a funcao do funcionario: ";
    getline(cin, funcao);

    json novoFuncionario = {
        {"codigo", cod_funcionario},
        {"nome", nome},
        {"turno", turno},
        {"funcao", funcao}
    };
    dados["dados"]["funcionarios"].push_back(novoFuncionario);

    ofstream arquivoSaida("dados.json");
    if (!arquivoSaida.is_open()) {
        cerr << "Erro ao abrir o arquivo para salvar os dados." << endl;
        return;
    }
    arquivoSaida << dados.dump(4);
    arquivoSaida.close();

    cout << "Funcionario " << nome << " adicionado com sucesso!" << endl;
}

void Manager::SendInformation(string type, string mensagem) {
    cout << type << " : " << mensagem << endl;
}

void Manager::Rent() {
    // Implementação futura
}

void Manager::ShowHistory() {
    // Implementação futura
}

void Manager::RegisterService() {
    // Implementação futura
}

void Manager::AddExpenses() {
    // Implementação futura
}

void Manager::ShowExpenses() {
    // Implementação futura
}
