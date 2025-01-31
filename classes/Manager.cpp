#include "Manager.hpp"
#include "ValidacaoInputs.hpp"
#include <iostream>
#include <fstream>
#include <limits>
#include <algorithm>

using namespace std;

Manager::Manager(const string& name, const string& email, const string& phone, const string& type, const string& senha, const long& cpf)
    : User(name, email, phone, type, senha, cpf) {}


// Função auxiliar para obter entrada numérica válida
template <typename T>
T obterEntradaValida(const string& mensagem) {
    T valor;
    while (true) {
        cout << mensagem;
        if (cin >> valor) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        } else {
            cout << "Entrada inválida! Tente novamente.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// Função auxiliar para buscar unidade disponível
bool buscarUnidadeDisponivel(json& unidadesJson, int unidadeNum, long cpf) {
    auto it = find_if(unidadesJson["unidades"].begin(), unidadesJson["unidades"].end(),
        [unidadeNum](const json& unidade) {
            return unidade["numero"] == unidadeNum && !unidade["ocupado"];
        });

    if (it != unidadesJson["unidades"].end()) {
        (*it)["morador_cpf"] = cpf;
        (*it)["ocupado"] = true;
        return true;
    }
    return false;
}

// Implementação da função de adicionar morador
void Manager::adicionarUsuarioMorador() {
    string email, nome, senha;
    long long cpf;
    int unidadeNum;
    bool pagamentoEmDia, unidadeValida = false;

    json usuariosJson = carregarArquivo("bdjson/usuarios.json");
    json unidadesJson = carregarArquivo("bdjson/unidades.json");

    cpf = solicitarCPF();
    if (cpf != 0) {
        cout << "CPF cadastrado com sucesso: " << cpf << endl;
    } else {
        cout << "Nenhum CPF foi cadastrado.\n";
        return;
    }

    cout << "Digite o email: ";
    cin.ignore();
    getline(cin, email);

    cout << "Digite o nome: ";
    getline(cin, nome);

    cout << "Digite a senha: ";
    getline(cin, senha);

    pagamentoEmDia = obterEntradaValida<bool>("O pagamento está em dia? (1 para Sim, 0 para Não): ");

    json novoUsuario = {
        {"cpf", cpf},
        {"email", email},
        {"nome", nome},
        {"senha", senha},
        {"tipo", "morador"},
        {"pagamento_em_dia", pagamentoEmDia}
    };

    // Solicita uma unidade válida
    while (!unidadeValida) {
        unidadeNum = obterEntradaValida<int>("Digite o número da unidade que o usuário será cadastrado: ");

        if (buscarUnidadeDisponivel(unidadesJson, unidadeNum, cpf)) {
            unidadeValida = true;
        } else {
            cout << "Unidade inválida ou já ocupada. Por favor, insira uma unidade disponível.\n";
        }
    }

    novoUsuario["unidade"] = unidadeNum;
    usuariosJson["usuarios"].push_back(novoUsuario);

    // Salvar os JSONs atualizados no arquivo
    salvarArquivo("bdjson/unidades.json", unidadesJson);
    salvarArquivo("bdjson/usuarios.json", usuariosJson);

    cout << "Usuário " << nome << " cadastrado com sucesso na unidade " << unidadeNum << "!\n";
}

void Manager::removerUsuarioMorador() {
    string caminhoUsuarios = "bdjson/usuarios.json"; // Caminho do arquivo dos usuários
    string caminhoUnidades = "bdjson/unidades.json"; // Caminho do arquivo das unidades
    json usuariosJson = carregarArquivo(caminhoUsuarios); // Carregar os dados dos usuários
    json unidadesJson = carregarArquivo(caminhoUnidades); // Carregar os dados das unidades
    long long cpf;
    bool usuarioEncontrado = false;

    cpf = solicitarCPF();

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
        cout << "Usuário removido com sucesso!" << endl;
    } else {
        cout << "Usuário com o CPF " << cpf << " não foi encontrado." << endl;
    }
}

void Manager::adicionarNovoFuncionario() {
    string caminhoCondominio = "bdjson/condominio.json";
    string nome, turno, funcao;
    json condominioJson = carregarArquivo(caminhoCondominio);
    int cod_funcionario;


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

void Manager::removerFuncionario() {
    string caminhoCondominio = "bdjson/condominio.json";
    json condominioJson = carregarArquivo(caminhoCondominio);
    int cod_funcionario;
    bool funcionarioEncontrado = false;

    cout << "Digite o código do funcionário que deseja remover: ";
    cin >> cod_funcionario;

    for (auto it = condominioJson["funcionarios"].begin(); it != condominioJson["funcionarios"].end(); ++it) {
        if ((*it)["cod_funcionario"] == cod_funcionario) {
            funcionarioEncontrado = true;
            condominioJson["funcionarios"].erase(it);
            break;
        }
    }

    if (funcionarioEncontrado) {
        salvarArquivo(caminhoCondominio, condominioJson);
        cout << "Funcionário removido com sucesso!" << endl;
    } else {
        cout << "Funcionário com o código " << cod_funcionario << " não foi encontrado." << endl;
    }
}

void Manager::adicionarAvisos() {
    string caminhoCondominio = "bdjson/condominio.json";
    string caminhoUnidades = "bdjson/unidades.json";
    string aviso, obs;
    json condominioJson = carregarArquivo(caminhoCondominio);
    json unidadesJson = carregarArquivo(caminhoUnidades);
    int destinatario = 0; // Valor padrão do destinatário
    bool possuiAviso, destinatarioEspecifico, unidadeValida = false;

    // Solicitar o texto do aviso
    cin.ignore();
    cout << "Digite o AVISO que deseja comunicar: ";
    getline(cin, aviso);

    // Verificar se o aviso possui observações
    cout << "O aviso possui alguma observação? (1 para Sim, 0 para Não): ";
    cin >> possuiAviso;
    cin.ignore();

    if (possuiAviso) {
        cout << "Digite a OBSERVAÇÃO do aviso: ";
        getline(cin, obs);
    } else {
        obs = nullptr;
    }

    // Verificar se o usuário deseja informar um destinatário específico
    cout << "Deseja enviar este aviso para uma unidade específica? (1 para Sim, 0 para Não): ";
    cin >> destinatarioEspecifico;

    if (destinatarioEspecifico) {
        while (!unidadeValida) {
            cout << "Digite o número da unidade destinatária: ";
            cin >> destinatario;

            // Validar se a unidade existe no banco de dados
            for (const auto& unidade : unidadesJson["unidades"]) {
                if (unidade["numero"] == destinatario) {
                    unidadeValida = true;
                    break;
                }
            }
            if (!unidadeValida) {
                cout << "Unidade não encontrada no banco de dados. Por favor, insira uma unidade válida." << endl;
            }
        }
    }

    // Criar o novo aviso
    json novoAviso = {
        {"aviso", aviso},
        {"observacoes", obs},
        {"destinatario", destinatario}
    };

    // Adicionar o aviso ao JSON de avisos
    condominioJson["avisos"].push_back(novoAviso);

    // Salvar o JSON atualizado
    salvarArquivo(caminhoCondominio, condominioJson);

    cout << "Aviso adicionado com sucesso!" << endl;
}

void Manager::reservarAreaComumManager() {
    string caminhoUsuarios = "bdjson/unidades.json";
    string caminhoAlugueis = "bdjson/condominio.json";
    json alugueisJson = carregarArquivo(caminhoAlugueis);
    json usuariosJson = carregarArquivo(caminhoUsuarios);
    string areaReservada, dataReserva, nome_morador;
    int codigoArea, numero_apt;
    bool cpfValido = false;
    long long cpfMorador;

    cout << "Digite o CPF do morador que está reservando o espaço:\n";
    cpfMorador = solicitarCPF();
    // Verificar se o CPF do morador existe no arquivo de usuários

    for (const auto& usuario : usuariosJson["unidades"]) {
        if (usuario["morador_cpf"] == cpfMorador) {
            cpfValido = true;
            numero_apt = usuario["unidade"];
            nome_morador = usuario["nome"];
            break;
        }
    }

    if (!cpfValido) {
        cout << "CPF não encontrado no sistema. Aluguel não registrado." << endl;
        return;
    }

    cout << "=============================\n";
    cout << "   Reservar Área Comum\n";
    cout << "=============================\n";
    cout << "Digite o código da área que deseja reservar:\n";
    cout << "1: Salão de Festas\n";
    cout << "2: Churrasqueira\n";
    cout << "3: Sauna\n";
    cout << "4: Playground\n";
    cout << "=============================\n";
    cout << "Digite o código da área que deseja reservar: ";

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

    while (true) {
        dataReserva = solicitarDataValida();

        // Verificar se a data já está reservada para a área escolhida
        bool dataDisponivel = true;
        for (const auto& reserva : alugueisJson["reservas"]) {
            if (reserva["area_reservada"] == areaReservada && reserva["data_reservada"] == dataReserva) {
                dataDisponivel = false;
                break;
            }
        }

        if (dataDisponivel) {
            break;
        } else {
            cout << "A área já está reservada para essa data. Deseja tentar outra data? (1 para Sim, 0 para Não): ";
            int escolha;
            cin >> escolha;
            if (escolha == 0) {
                cout << "Reserva cancelada." << endl;
                return;
            }
        }
    }

    json novoAluguel = {
        {"nome_morador", nome_morador},
        {"unidade", numero_apt},
        {"area_reservada", areaReservada},
        {"data_reservada", dataReserva}
    };


    alugueisJson["reservas"].push_back(novoAluguel);
    salvarArquivo(caminhoAlugueis, alugueisJson);

    cout << "\n===================================\n";
    cout << "|| Reserva registrada com sucesso! ||\n";
    cout << "===================================\n";
}


void Manager::resgistraServico() {
    string caminhoCondominio = "bdjson/condominio.json";
    json servicosJson = carregarArquivo(caminhoCondominio);
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

    cout << "Data de início do serviço : ";
    dataInicio = solicitarDataValida();
    
    cout << "Data termino do serviço : ";
    dataFim = solicitarDataValida();

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


    salvarArquivo(caminhoCondominio, servicosJson);
    cout << "Serviço registrado com sucesso!" << endl;
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
    bool encontrouAviso = false;

    cout << "\n====================\n";
    cout << "     Avisos\n";
    cout << "====================\n";

    if (historicoJson.contains("avisos")) {
        for (const auto& aviso : historicoJson["avisos"]) {
            if (aviso.contains("destinatario") && aviso["destinatario"] == 0) {
                cout << "Aviso: " << aviso["aviso"]
                    << ", Observações: " << aviso["observacoes"] << endl;
                encontrouAviso = true;
            }
        }
        if (!encontrouAviso) {
            cout << "Nenhum aviso para o destinatário 0000 encontrado.\n";
        }
    } else {
        cout << "Nenhum aviso encontrado.\n";
    }
    cout << "====================\n";
}

void Manager::mostrarReservas() {
    string caminhoCondominio = "bdjson/condominio.json";
    json historicoJson = carregarArquivo(caminhoCondominio);

    cout << "\nReservas de áreas comuns:" << endl;

    if (historicoJson.contains("reservas")) {
        for (const auto& reserva : historicoJson["reservas"]) {
            cout << "Área: " << reserva["area_reservada"]
                << ", Data: " << reserva["data_reservada"]
                << ", Reserva no Nome de: " << reserva["nome_morador"]
                <<", Unidade: " << reserva["unidade"] << endl;
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
            if (reserva.contains("area_reservada") && reserva.contains("data_reservada") && reserva.contains("unidade")) {
                cout << "Área: " << reserva["area_reservada"]
                    << ", Data: " << reserva["data_reservada"]
                    << ", Unidade: " << reserva["unidade"]
                    << ", Nome do Morador: " << reserva["nome_morador"] << endl;
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
            if (aviso.contains("aviso") && aviso.contains("observacoes")) {
                cout << "Aviso: " << aviso["aviso"]
                    << ", Observações: " << aviso["observacoes"]
                    << ", Destinatário: " << aviso["destinatario"] << endl;
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

void Manager::verFeedback() {
    string caminhoFeedbacks = "bdjson/condominio.json";
    json feedbacksJson = carregarArquivo(caminhoFeedbacks);

    cout << "\nFeedbacks recebidos:" << endl;

    if (feedbacksJson.contains("feedbacks")) {
        for (const auto& feedback : feedbacksJson["feedbacks"]) {
            if (feedback.contains("feedback") && feedback.contains("morador")) {
                cout << "Feedback: " << feedback["feedback"]
                    << ", Morador: " << feedback["morador"] << endl;
            } else {
                cout << "Informações de feedback incompletas." << endl;
            }
        }
    } else {
        cout << "Nenhum feedback encontrado." << endl;
    }
}

