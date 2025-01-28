#include "Manager.hpp"

Manager::Manager(const string& name, const string& email, const string& phone, const string& type, const string& senha, const long& cpf)
    : User(name, email, phone, type, senha, cpf) {}


void Manager::adicionarUsuarioMorador() {
    string caminhoUsuarios = "bdjson/usuarios.json"; // Caminho do arquivo
    json usuariosJson = carregarArquivo(caminhoUsuarios); // Carregando o arquivo dos usuários

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

    std::string tipo = "morador";

    // Dados adicionais para moradores
    bool pagamentoEmDia = true;
    std::cout << "O pagamento está em dia? (1 para Sim, 0 para Não): ";
    std::cin >> pagamentoEmDia;

    // Criar novo usuário
    json novoUsuario = {
        {"cpf", cpf},
        {"email", email},
        {"nome", nome},
        {"senha", senha},
        {"tipo", tipo},
        {"pagamento_em_dia", pagamentoEmDia}
    };

    // Adicionar ao JSON
    usuariosJson["usuarios"].push_back(novoUsuario);

    string caminhoUnidades = "bdjson/unidades.json";
    json unidadesJson = carregarArquivo(caminhoUnidades);

    int unidadeNum;
    bool unidadeValida = false;

    // Solicitar uma unidade válida (disponível e existente)
    while (!unidadeValida) {
        std::cout << "Digite o número da unidade que o usuário será cadastrado: ";
        std::cin >> unidadeNum;

        for (auto& unidade : unidadesJson["unidades"]) {
            if (unidade["numero"] == unidadeNum && !unidade["ocupado"]) {
                unidade["morador_cpf"] = cpf;
                unidade["ocupado"] = true;
                unidadeValida = true;
                break; // Parar o loop após encontrar a unidade válida
            }
        }

        if (!unidadeValida) {
            std::cout << "Unidade inválida ou já ocupada. Por favor, insira uma unidade disponível." << std::endl;
        }
    }

    // Salvar os JSONs atualizados no arquivo
    salvarArquivo(caminhoUnidades, unidadesJson);
    salvarArquivo(caminhoUsuarios, usuariosJson);

    std::cout << "Usuário " << nome << " cadastrado com sucesso na unidade " << unidadeNum << "!" << std::endl;
}

void Manager::removerUsuarioMorador() {
    string caminhoUsuarios = "bdjson/usuarios.json"; // Caminho do arquivo dos usuários
    json usuariosJson = carregarArquivo(caminhoUsuarios); // Carregar os dados dos usuários

    string caminhoUnidades = "bdjson/unidades.json"; // Caminho do arquivo das unidades
    json unidadesJson = carregarArquivo(caminhoUnidades); // Carregar os dados das unidades

    std::cout << "Digite o CPF do morador que deseja remover: ";
    long long cpf;
    std::cin >> cpf;

    bool usuarioEncontrado = false;

    // Procurar o usuário pelo CPF no JSON de usuários
    for (auto it = usuariosJson["usuarios"].begin(); it != usuariosJson["usuarios"].end(); ++it) {
        if ((*it)["cpf"] == cpf) {
            usuarioEncontrado = true;

            // Remover o morador do JSON de unidades
            for (auto& unidade : unidadesJson["unidades"]) {
                if (unidade["morador_cpf"] == cpf) {
                    unidade["morador_cpf"] = nullptr; // Transformar o cpf em null
                    unidade["ocupado"] = false;  // Marcar a unidade como disponível
                    break;
                }
            }

            // Remover o usuário do JSON de usuários
            usuariosJson["usuarios"].erase(it);
            break;
        }
    }

    if (usuarioEncontrado) {
        // Salvar os JSONs atualizados nos arquivos
        salvarArquivo(caminhoUsuarios, usuariosJson);
        salvarArquivo(caminhoUnidades, unidadesJson);
        std::cout << "Usuário removido com sucesso!" << std::endl;
    } else {
        std::cout << "Usuário com o CPF " << cpf << " não foi encontrado." << std::endl;
    }
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



void Manager::resgistraServico() {
    string caminhoCondominio = "bdjson/condominio.json";

    // Tenta carregar o arquivo JSON
    json servicosJson;
    try {
        servicosJson = carregarArquivo(caminhoCondominio);
    } catch (const exception &e) {
        cerr << "Erro ao carregar o arquivo JSON: " << e.what() << endl;
        return;
    }

    string nomeServico, empresa, dataInicio, dataFim;
    float valor;

    // Garante que o buffer de entrada esteja limpo antes de começar
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Coleta de dados com validações básicas
    cout << "Digite o nome do serviço: ";
    getline(cin, nomeServico);
    if (nomeServico.empty()) {
        cerr << "Erro: O nome do serviço não pode estar vazio." << endl;
        return;
    }

    cout << "Digite o nome da empresa fornecedora: ";
    getline(cin, empresa);
    if (empresa.empty()) {
        cerr << "Erro: O nome da empresa não pode estar vazio." << endl;
        return;
    }

    cout << "Digite a data de início do serviço (YYYY-MM-DD): ";
    getline(cin, dataInicio);
    if (dataInicio.empty() || dataInicio.size() != 10) {
        cerr << "Erro: Data de início inválida." << endl;
        return;
    }

    cout << "Digite a data de término do serviço (YYYY-MM-DD): ";
    getline(cin, dataFim);
    if (dataFim.empty() || dataFim.size() != 10) {
        cerr << "Erro: Data de término inválida." << endl;
        return;
    }

    cout << "Digite o valor do serviço: ";
    if (!(cin >> valor) || valor < 0) {
        cerr << "Erro: Valor inválido." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    // Limpa o buffer após a leitura numérica
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Criação do novo serviço
    json novoServico = {
        {"nome", nomeServico},
        {"empresa", empresa},
        {"data_inicio", dataInicio},
        {"data_fim", dataFim},
        {"valor", valor}
    };

    // Adiciona o novo serviço ao array de serviços
    servicosJson["servicos"].push_back(novoServico);

    // Tenta salvar o arquivo JSON atualizado
    try {
        salvarArquivo(caminhoCondominio, servicosJson);
        cout << "Serviço registrado com sucesso!" << endl;
    } catch (const exception &e) {
        cerr << "Erro ao salvar o arquivo JSON: " << e.what() << endl;
    }
}



void Manager::mostrarServicos() {
    string caminhoCondominio = "bdjson/condominio.json";
    json historicoJson = carregarArquivo(caminhoCondominio);

    cout << "\nServiços registrados:" << endl;

    // Verificando se a chave "servicos" existe no JSON
    if (historicoJson.contains("servicos")) {
        // Iterando sobre cada serviço
        for (const auto& servico : historicoJson["servicos"]) {
            // Verificando se todas as informações essenciais estão presentes
            if (servico.contains("nome") && servico.contains("empresa") && 
                servico.contains("data_inicio") && servico.contains("data_fim") && 
                servico.contains("valor")) {

                cout << "Serviço: " << servico["nome"]
                    << ", Empresa: " << servico["empresa"]
                    << ", Data de início: " << servico["data_inicio"]
                    << ", Data de término: " << servico["data_fim"]
                    << ", Valor: R$ " << servico["valor"] << endl;
            } else {
                cout << "Informações do serviço incompletas." << endl;
            }
        }
    } else {
        cout << "Nenhum serviço registrado." << endl;
    }
}

void Manager::mostrarAvisos() {
    string caminhoCondominio = "bdjson/condominio.json";
    json historicoJson = carregarArquivo(caminhoCondominio);

    cout << "\nAvisos:" << endl;

    if (historicoJson.contains("avisos")) {
        for (const auto& aviso : historicoJson["avisos"]) {
            cout << "Aviso: " << aviso["aviso"]
                << ", Data: " << aviso["data"]
                << ", Observações: " << aviso["observacoes"] << endl;
        }
    } else {
        cout << "Nenhum aviso encontrado." << endl;
    }
}

void Manager::mostrarReservas() {
    string caminhoCondominio = "bdjson/condominio.json";
    json historicoJson = carregarArquivo(caminhoCondominio);

    cout << "\nReservas de áreas comuns:" << endl;

    if (historicoJson.contains("reservas")) {
        for (const auto& reserva : historicoJson["reservas"]) {
            cout << "Área: " << reserva["area_reservada"]
                << ", Data: " << reserva["data_inicio"]
                << ", Apartamento: " << reserva["numero_apt"] << endl;
        }
    } else {
        cout << "Nenhuma reserva encontrada." << endl;
    }
}


void Manager::mostrarHistorico() {
    string caminhoCondominio = "bdjson/condominio.json";
    json historicoJson = carregarArquivo(caminhoCondominio);

    cout << "\nReservas de áreas comuns:" << endl;

    // Verificando e imprimindo as reservas
    if (historicoJson.contains("reservas")) {
        for (const auto& reserva : historicoJson["reservas"]) {
            if (reserva.contains("area_reservada") && reserva.contains("data_inicio") && reserva.contains("numero_apt")) {
                cout << "Área: " << reserva["area_reservada"]
                    << ", Data: " << reserva["data_inicio"]
                    << ", Apartamento: " << reserva["numero_apt"] << endl;
            } else {
                cout << "Informações de reserva incompletas." << endl;
            }
        }
    } else {
        cout << "Nenhuma reserva encontrada." << endl;
    }

    cout << "\nAvisos:" << endl;
    if (historicoJson.contains("avisos")) {
        for (const auto& aviso : historicoJson["avisos"]) {
            if (aviso.contains("aviso") && aviso.contains("data") && aviso.contains("observacoes")) {
                cout << "Aviso: " << aviso["aviso"]
                    << ", Data: " << aviso["data"]
                    << ", Observações: " << aviso["observacoes"] << endl;
            }
        }
    } else {
        cout << "Nenhum aviso encontrado." << endl;
    }

    cout << "\nServiços:" << endl;
    if (historicoJson.contains("servicos")) {
        for (const auto& servico : historicoJson["servicos"]) {
            if (servico.contains("nome") && servico.contains("empresa") && servico.contains("data_inicio") && servico.contains("data_fim")) {
                cout << "Serviço: " << servico["nome"]
                    << ", Empresa: " << servico["empresa"]
                    << ", Data de início: " << servico["data_inicio"]
                    << ", Data de término: " << servico["data_fim"]
                    << ", Valor: R$ " << servico["valor"] << endl;
            }
        }
    } else {
        cout << "Nenhum serviço encontrado." << endl;
    }
}


