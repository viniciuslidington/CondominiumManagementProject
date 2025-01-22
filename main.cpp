#include <iostream>
#include <fstream>
#include "json.hpp" // Inclua o arquivo json.hpp no seu projeto

using json = nlohmann::json;

void cadastrarUsuario(json& dados) {
    std::string email, senha, nome, tipo;

    // Solicitar dados do novo usuário
    std::cout << "Digite o email do novo usuário: ";
    std::cin >> email;
    std::cout << "Digite a senha do novo usuário: ";
    std::cin >> senha;
    std::cout << "Digite o nome do novo usuário: ";
    std::cin.ignore();  // Para limpar o buffer de entrada
    std::getline(std::cin, nome);
    std::cout << "Digite o tipo do usuário (morador/gestor): ";
    std::cin >> tipo;

    // Criar um novo usuário e adicionar na lista
    json novoUsuario = {
        {"email", email},
        {"senha", senha},
        {"nome", nome},
        {"tipo", tipo}
    };

    dados["dados"]["usuarios"].push_back(novoUsuario);
    std::cout << "Novo usuário cadastrado com sucesso!" << std::endl;
}

int main() {
    // Abrir o arquivo JSON
    std::ifstream arquivo("dados.json");
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo dados.json" << std::endl;
        return 1;
    }

    // Carregar o conteúdo do arquivo em um objeto JSON
    json dados;
    arquivo >> dados;

    // Opção para cadastrar um novo usuário
    char opcao;
    std::cout << "Deseja cadastrar um novo usuário? (s/n): ";
    std::cin >> opcao;
    if (opcao == 's' || opcao == 'S') {
        cadastrarUsuario(dados);
    }

    // Salvar o arquivo JSON com o novo usuário
    std::ofstream arquivoSaida("dados.json");
    if (!arquivoSaida.is_open()) {
        std::cerr << "Erro ao abrir o arquivo para salvar os dados." << std::endl;
        return 1;
    }
    arquivoSaida << dados.dump(4); // Escrever no arquivo com formatação legível
    arquivoSaida.close();

    return 0;
}
