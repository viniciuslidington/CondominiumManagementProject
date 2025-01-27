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

void Manager::adicionarNovoFuncionario() {
    string nome, turno, funcao, caminhoCondominio;
    int cod_funcionario;

    caminhoCondominio = "bdjson/condominio.json";
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

void Manager::adicionarAvisos() {
    string aviso, data, obs, caminhoCondominio;
    bool possuiData, possuiAviso;

    caminhoCondominio = "bdjson/condominio.json";
    json condominioJson = carregarArquivo(caminhoCondominio);

    cin.ignore();
    cout << "Digite o AVISO que deseja comunicar: ";
    getline(cin, aviso);
    cout << "O aviso possui uma data específica? (1 para Sim, 0 para Não): ";
    cin >> possuiData;
    cin.ignore(); // Limpa o buffer

    if (possuiData) {
        cout << "Digite a DATA que o evento acontecerá: ";
        getline(cin, data);
    } else {
        data = "";
    }

    cout << "O aviso possui alguma Observção? (1 para Sim, 0 para Não) ";
    cin >> possuiAviso;
    cin.ignore();

    if(possuiAviso) {
        cout << "Digite a OBSERVAÇÃO do aviso: ";
        getline(cin,obs);
    } else {
        obs = "";
    }

    json novoAviso = {
        {"aviso", aviso},
        {"data", data},
        {"observacoes", obs}
    };

    condominioJson["condominio"]["avisos"].push_back(novoAviso);

    salvarArquivo(caminhoCondominio, condominioJson);

    cout << "Aviso adicionado com sucesso!" << endl;

}

void Manager::Rent() {
    string caminhoAlugueis = "bdjson/alugueis.json";
    json alugueisJson = carregarArquivo(caminhoAlugueis);

    cout << "Digite o CPF do morador que está alugando: ";
    long long cpfMorador;
    cin >> cpfMorador;
    cin.ignore();

    cout << "Digite o código do apartamento alugado: ";
    int codApartamento;
    cin >> codApartamento;
    cin.ignore();

    cout << "Digite a data de início do aluguel (YYYY-MM-DD): ";
    string dataInicio;
    getline(cin, dataInicio);

    cout << "Digite a data de término do aluguel (YYYY-MM-DD): ";
    string dataFim;
    getline(cin, dataFim);

    json novoAluguel = {
        {"cpf_morador", cpfMorador},
        {"cod_apartamento", codApartamento},
        {"data_inicio", dataInicio},
        {"data_fim", dataFim}
    };

    alugueisJson["alugueis"].push_back(novoAluguel);
    salvarArquivo(caminhoAlugueis, alugueisJson);

    cout << "Aluguel registrado com sucesso!" << endl;
}

void Manager::ShowHistory() {
    string caminhoHistorico = "bdjson/historico.json";
    json historicoJson = carregarArquivo(caminhoHistorico);

    cout << "Histórico de eventos do condomínio:" << endl;

    for (const auto& evento : historicoJson["historico"]) {
        cout << "Data: " << evento["data"] << ", Descrição: " << evento["descricao"] << endl;
    }
}

void Manager::RegisterService() {
    string caminhoServicos = "bdjson/servicos.json";
    json servicosJson = carregarArquivo(caminhoServicos);

    cout << "Digite o nome do serviço: ";
    string nomeServico;
    getline(cin, nomeServico);

    cout << "Digite o nome da empresa fornecedora: ";
    string empresa;
    getline(cin, empresa);

    cout << "Digite a data de início do serviço (YYYY-MM-DD): ";
    string dataInicio;
    getline(cin, dataInicio);

    cout << "Digite a data de término do serviço (YYYY-MM-DD): ";
    string dataFim;
    getline(cin, dataFim);

    json novoServico = {
        {"nome", nomeServico},
        {"empresa", empresa},
        {"data_inicio", dataInicio},
        {"data_fim", dataFim}
    };

    servicosJson["servicos"].push_back(novoServico);
    salvarArquivo(caminhoServicos, servicosJson);

    cout << "Serviço registrado com sucesso!" << endl;
}

void Manager::AddExpenses() {
    string caminhoDespesas = "bdjson/despesas.json";
    json despesasJson = carregarArquivo(caminhoDespesas);

    cout << "Digite a descrição da despesa: ";
    string descricao;
    getline(cin, descricao);

    cout << "Digite o valor da despesa: ";
    double valor;
    cin >> valor;
    cin.ignore();

    cout << "Digite a data da despesa (YYYY-MM-DD): ";
    string data;
    getline(cin, data);

    json novaDespesa = {
        {"descricao", descricao},
        {"valor", valor},
        {"data", data}
    };

    despesasJson["despesas"].push_back(novaDespesa);
    salvarArquivo(caminhoDespesas, despesasJson);

    cout << "Despesa adicionada com sucesso!" << endl;
}

void Manager::ShowExpenses() {
    string caminhoDespesas = "bdjson/despesas.json";
    json despesasJson = carregarArquivo(caminhoDespesas);

    cout << "Lista de despesas:" << endl;

    for (const auto& despesa : despesasJson["despesas"]) {
        cout << "Descrição: " << despesa["descricao"]
             << ", Valor: " << despesa["valor"]
             << ", Data: " << despesa["data"] << endl;
    }
}
