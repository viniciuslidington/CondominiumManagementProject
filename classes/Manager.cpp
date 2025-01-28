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

    condominioJson["funcionarios"].push_back(novoFuncionario);

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

    condominioJson["avisos"].push_back(novoAviso);

    salvarArquivo(caminhoCondominio, condominioJson);

    cout << "Aviso adicionado com sucesso!" << endl;

}

void Manager::reservarAreaComumManager() {
    string areaReservada, dataInicio, caminhoUsuarios, caminhoAlugueis;
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

    cout << "Digite a data em que deseja alugar (DD-MM-YYYY): \n";
    getline(cin, dataInicio);

    // Verificar se a data já está reservada para a área escolhida
    for (const auto& reserva : alugueisJson["reservas"]) {
        if (reserva["area_reservada"] == areaReservada && reserva["data_inicio"] == dataInicio) {
            cout << "A área já está reservada para essa data. Por favor, escolha outra data." << endl;
            return;
        }
    }

    json novoAluguel = {
        {"numero_apt", numero_apt},
        {"area_reservada", areaReservada},
        {"data_inicio", dataInicio}
    };

    alugueisJson["reservas"].push_back(novoAluguel);
    salvarArquivo(caminhoAlugueis, alugueisJson);

    cout << "Reserva registrada com sucesso!" << endl;
}

void Manager::mostrarHistorico() {
    string caminhoCondominio = "bdjson/condominio.json";
    json historicoJson = carregarArquivo(caminhoCondominio);

    cout << "\nReservas de áreas comuns:" << endl;

    for (const auto& reserva : historicoJson["reservas"]) {
        cout << "Área: " << reserva["area_reservada"]
            << ", Data: " << reserva["data_inicio"]
            << ", Apartamento: " << reserva["numero_apt"] << endl;
    }

    cout << "\nAvisos:" << endl;

    for (const auto& aviso : historicoJson["avisos"]) {
        cout << "Aviso: " << aviso["aviso"]
            << ", Data: " << aviso["data"]
            << ", Observações: " << aviso["observacoes"] << endl;
    }

    cout << "\nServiços:" << endl;

    for (const auto& servico : historicoJson["servicos"]) {
        cout << "Serviço: " << servico["nome"]
            << ", Empresa: " << servico["empresa"]
            << ", Data de início: " << servico["data_inicio"]
            << ", Data de término: " << servico["data_fim"] << endl;
    }
}

void Manager::resgistraServico() {
    string caminhoCondominio = "bdjson/condominio.json";
    json servicosJson = carregarArquivo(caminhoCondominio);

    cout << "Digite o nome do serviço: ";
    string nomeServico;
    getline(cin, nomeServico);

    cin.ignore();
    
    cout << "Digite o nome da empresa fornecedora: ";
    string empresa;
    getline(cin, empresa);

    cin.ignore();

    cout << "Digite a data de início do serviço (YYYY-MM-DD): ";
    string dataInicio;
    getline(cin, dataInicio);

    cin.ignore();

    cout << "Digite a data de término do serviço (YYYY-MM-DD): ";
    string dataFim;
    getline(cin, dataFim);

    cin.ignore();

    json novoServico = {
        {"nome", nomeServico},
        {"empresa", empresa},
        {"data_inicio", dataInicio},
        {"data_fim", dataFim}
    };

    servicosJson["servicos"].push_back(novoServico);
    salvarArquivo(caminhoCondominio, servicosJson);

    cout << "Serviço registrado com sucesso!" << endl;
}

void Manager::adicionarDespesas() {
    string caminhoCondominio = "bdjson/condominio.json";
    json despesasJson = carregarArquivo(caminhoCondominio);

    cout << "Lista de serviços disponíveis:" << endl;
    for (size_t i = 0; i < despesasJson["servicos"].size(); ++i) {
        cout << i + 1 << ": " << despesasJson["servicos"][i]["nome"]
             << " - Data: " << despesasJson["servicos"][i]["data_inicio"] << " a " << despesasJson["servicos"][i]["data_fim"] << endl;
    }

    cout << "Escolha o número do serviço para adicionar a despesa: ";
    size_t escolha;
    cin >> escolha;
    cin.ignore();

    if (escolha < 1 || escolha > despesasJson["servicos"].size()) {
        cout << "Escolha inválida." << endl;
        return;
    }

    json& servicoEscolhido = despesasJson["servicos"][escolha - 1];

    cout << "Digite o valor da despesa: ";
    long valor;
    cin >> valor;
    cin.ignore();

    json novaDespesa = {"valor", valor};

    servicoEscolhido.push_back(novaDespesa);
    salvarArquivo(caminhoCondominio, servicoEscolhido);
    cout << "Despesa adicionada com sucesso!" << endl;
}

void Manager::mostrarDespesas() {
    string caminhoDespesas = "bdjson/despesas.json";
    json despesasJson = carregarArquivo(caminhoDespesas);

    cout << "Lista de despesas:" << endl;

    for (const auto& despesa : despesasJson["despesas"]) {
        cout << "Descrição: " << despesa["descricao"]
             << ", Valor: " << despesa["valor"]
             << ", Data: " << despesa["data"] << endl;
    }
}
