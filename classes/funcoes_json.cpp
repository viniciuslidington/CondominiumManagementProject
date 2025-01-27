#include "funcoes_json.hpp"
#include <fstream>
#include <iostream>
#include <cstdlib> // Para usar exit()

using namespace std;

// Implementação da função para carregar um arquivo JSON
json carregarArquivo(const string& caminho) {
    ifstream arquivo(caminho);
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo: " << caminho << endl;
        exit(1);
    }
    json dados;
    arquivo >> dados;
    arquivo.close();
    return dados;
}

// Implementação da função para salvar um arquivo JSON
void salvarArquivo(const string& caminho, const json& dados) {
    ofstream arquivo(caminho);
    if (!arquivo.is_open()) {
        cerr << "Erro ao salvar o arquivo: " << caminho << endl;
        exit(1);
    }
    arquivo << dados.dump(4); // Formatação com identação
    arquivo.close();
}
