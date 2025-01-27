#include "Manager.hpp"

Manager::Manager(const string& name, const string& email, const string& phone, const string& type, const string& senha, const long& cpf)
    : User(name, email, phone, type, senha, cpf) {}

void Manager::adicionarUsuarioMorador() {
   
    string caminhoUsuarios = "bdjson/usuarios.json";

    json usuariosJson = carregarArquivo(caminhoUsuarios);

        // Solicitar informações do novo usuário
    std::cout << "Digite o CPF: ";
    long long cpf;
    std::cin >> cpf;

    std::cin.ignore(); // Limpa o buffer
    std::cout << "Digite o email: ";
    std::string email;
    std::getline(std::cin, email);

    std::cout << "Digite o nome: ";
    std::string nome;
    std::getline(std::cin, nome);

    std::cout << "Digite a senha: ";
    std::string senha;
    std::getline(std::cin, senha);

    std::cout << "Digite o tipo (morador/gestor): ";
    std::string tipo;
    std::getline(std::cin, tipo);

    // Dados adicionais para moradores
    bool pagamentoEmDia = false;
    if (tipo == "morador") {
        std::cout << "O pagamento está em dia? (1 para Sim, 0 para Não): ";
        std::cin >> pagamentoEmDia;
    }

    // Criar novo usuário
    json novoUsuario = {
        {"cpf", cpf},
        {"email", email},
        {"nome", nome},
        {"senha", senha},
        {"tipo", tipo}
    };

    if (tipo == "morador") {
        novoUsuario["pagamento_em_dia"] = pagamentoEmDia;
    }

    // Adicionar ao JSON
    usuariosJson["usuarios"].push_back(novoUsuario);

    // Salvar as alterações no arquivo
    salvarArquivo(caminhoUsuarios, usuariosJson);

    std::cout << "Usuário adicionado com sucesso!" << std::endl;
      
}

void Manager::addNewWorker() {
    string nome, turno, funcao;
    int cod_funcionario;
    char opcao;

    string caminhoCondominio = "bdjson/condominio.json";

    json condominioJson = carregarArquivo(caminhoCondominio);

    cin.ignore();
    cout << "Digite o cod funcionario: ";
    cin >> cod_funcionario;
    cin.ignore(); // Limpa o buffer
    cout << "Digite a funcao do funcionario: ";
    getline(cin, funcao);
    cout << "Digite a nome do funcionario: ";
    getline(cin, nome);
    cout << "Digite o turno do funcionario: ";
    getline(cin, turno);


    json novoFuncionario = {
        {"cod_funcionario", cod_funcionario},
        {"funcao", funcao},
        {"nome", nome},
        {"turno", turno}
    };

    condominioJson["condominio"]["funcionarios"].push_back(novoFuncionario);

    salvarArquivo(caminhoCondominio, condominioJson);

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
