#ifndef GESTOR_HPP
#define GESTOR_HPP

#include "User.hpp"
#include <string>
#include <iostream>
#include "../main.hpp"
#include "BancoJson.hpp"
using namespace std;

class Manager : public User {
public:
    Manager(const string& name, const string& email, const string& phone, const string& type, const string& senha, const long& cpf)
        : User(name, email, phone, type, senha, cpf) {}
    //Funcao para manipular o arquivo JSON (Tem que adicionar no arquivo BancoJson.hpp)    
    json carregarDados(){
        BancoJson banco;
        json dados = banco.abrirJson("dados.json");
        if (dados == nullptr) {
            cerr << "Erro ao carregar os dados do arquivo JSON." << endl;
            return dados;
        }
        return dados;
    }
    //Aplicar função de cadastrar novo usuario (Morador)
    void adicionarUsuarioMorador(){

        string email, senha, nome, telefone;
        int unidade;
        long cpf;

        ifstream arquivoEntrada("dados.json");
        if (!arquivoEntrada.is_open()) {
            cerr << "Erro ao abrir o arquivo dados.json" << std::endl;
            return;
        }

        // Carregar o conteúdo do arquivo em um objeto JSON
        json dados;
        arquivoEntrada >> dados;
        arquivoEntrada.close();

        std::cout << "Digite o email do novo usuário: ";
        std::cin >> email;
        std::cout << "Digite a senha do novo usuário: ";
        std::cin >> senha;
        std::cout << "Digite o nome do novo usuário: ";
        std::cin.ignore();  // Para limpar o buffer de entrada
        std::getline(cin, nome);
        std::cout << "Digite o cpf do novo usuario, somente os numeros: ";
        std::cin >> cpf;
        std::cout << "Digite o telefone do novo usuario: ";
        std::cin >> telefone;
        std::cout << "Digite o numero do apartamento ";
        std::cin >> unidade;

    // Procurar a unidade correspondente
        for (auto& unidadeObj : dados["dados"]["unidades"]) {
            if (unidadeObj["numero"] == unidade) {
                // Verificar se a unidade está disponível
                if (unidadeObj["ocupado"]) {
                    cout << "A unidade " << unidade << " já está ocupada!" << endl;
                    cout << "Por favor, escolha outra unidade ou tente novamente mais tarde." << endl;
                    return;
                }

                // Associar o CPF à unidade e marcar como ocupada
                unidadeObj["ocupado"] = true;
                unidadeObj["morador_cpf"] = cpf;

                // Adicionar o novo morador à lista de usuários
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
                return;
            }
        }

    // Se a unidade não for encontrada
        cout << "Unidade " << unidade << " nao encontrada!" << endl;

        ofstream arquivoSaida("dados.json");
        if (!arquivoSaida.is_open()) {
            cerr << "Erro ao abrir o arquivo para salvar os dados." << endl;
            return;
        }
        arquivoSaida << dados.dump(4); // Escrever no arquivo com formatação legível
        arquivoSaida.close();
    }
    //Adicionar um novo usuario (Funcionario)
    void addNewWorker(){
        string nome, turno, funcao;
        int cod_funcionario;
        char opcao;

        ifstream arquivoEntrada("dados.json");
        if (!arquivoEntrada.is_open()) {
            cerr << "Erro ao abrir o arquivo dados.json" << std::endl;
            return;
        }

        // Carregar o conteúdo do arquivo em um objeto JSON
        json dados;
        arquivoEntrada >> dados;
        arquivoEntrada.close();

        bool funcionarioValido;
        do {
            funcionarioValido = true; // Reinicia como válido no início do loop
            std::cout << "Digite o codigo do funcionario que deseja adicionar: ";
            std::cin >> cod_funcionario;

            // Verificar se o código já existe
            for (const auto& funcionarioObj : dados["dados"]["funcionarios"]) {
                if (funcionarioObj["codigo"] == cod_funcionario) {
                    cout << "O codigo " << cod_funcionario << " já está em uso!" << endl;
                    cout << "Deseja tentar novamente? (S para Sim / N para Não): ";
                    std::cin >> opcao;

                    if (toupper(opcao) == 'N') {
                        return; // Sai da função caso o usuário escolha não tentar novamente
                    } else {
                        funcionarioValido = false; // Define como inválido para continuar o loop
                        break;
                    }
                }
            }
        } while (!funcionarioValido);

        // Coletar os dados do novo funcionário
        cin.ignore(); // Limpar o buffer do cin
        cout << "Digite o nome do funcionario: ";
        getline(cin, nome);
        cout << "Digite o turno do funcionario: ";
        getline(cin, turno);
        cout << "Digite a funcao do funcionario: ";
        getline(cin, funcao);

        // Adicionar o novo funcionário ao JSON
        json novoFuncionario = {
            {"codigo", cod_funcionario},
            {"nome", nome},
            {"turno", turno},
            {"funcao", funcao}
        };
        dados["dados"]["funcionarios"].push_back(novoFuncionario);

        // Salvar os dados atualizados no arquivo
        ofstream arquivoSaida("dados.json");
        if (!arquivoSaida.is_open()) {
            cerr << "Erro ao abrir o arquivo para salvar os dados." << endl;
            return;
        }
        arquivoSaida << dados.dump(4); // Escrever no arquivo com formatação legível
        arquivoSaida.close();

        cout << "Funcionario " << nome << " adicionado com sucesso!" << endl;


    }
    //Funcao para Emitir avisos
    void SendInformation(string type, string mensagem){
        std::cout << type << " : " << mensagem << std::endl;
    }
    //funcao para Locacao 
    //acredito que podemos fazer essas funcoes para que todos usem e tenha a funcionalidade 
    //locacao, historico de locacao, registro de servicos, ver gastos
    void Rent(){

    }
    //Funcao para Ver historico de locaçoes
    void ShowHistory(){

    }
    //Funcao para Registrar Servicos
    void RegisterService(){

    }
    //Funcao para Adicionar Gastos dos servicos do predio (Manutencoes, eventos, etc)
    void AddExpenses(){

    }
    //Funcao para Ver gastos do predio
    void ShowExpenses(){

    }


};

#endif 