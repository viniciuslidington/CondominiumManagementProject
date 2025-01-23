#ifndef GESTOR_HPP
#define GESTOR_HPP

#include "User.hpp"
#include <string>
#include <iostream>
#include "../main.hpp"
using namespace std;

class Manager : public User {
public:
    Manager(const string& name, const string& email, const string& type, const string& senha, const long& cpf)
        : User(name, email, type, senha, cpf) {}

    //Aplicar função de cadastrar novo usuario
    void adicionarUsuario(){

        string email, senha, nome;
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
        std::cout << "Digite o cpf do novo usuario ";
        std::cin >> cpf;
        std::cout << "Digite o numero da unidade ";
        std::cin >> unidade;

    // Procurar a unidade correspondente
        for (auto& unidadeObj : dados["dados"]["unidades"]) {
            if (unidadeObj["numero"] == unidade) {
                // Verificar se a unidade está disponível
                if (unidadeObj["ocupado"]) {
                    cout << "A unidade " << unidade << " já está ocupada!" << endl;
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
                    {"tipo", "morador"},
                    {"pagamento_em_dia", true}
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

};

#endif 