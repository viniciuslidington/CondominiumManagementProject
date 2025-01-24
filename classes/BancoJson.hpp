#ifndef BANCOJSON_HPP
#define BANCOJSON_HPP

#include <iostream>
#include <fstream>
#include <string>
#include "json.hpp" // Biblioteca JSON for Modern C++

using json = nlohmann::json;
using namespace std;

class BancoJson {
    public:
        json abrirJson(const string& nomeArquivo) {
            // Metodo para abrir um arquivo JSON e retornar o conteúdo
            ifstream arquivoEntrada(nomeArquivo);
            if (!arquivoEntrada.is_open()) {
                cerr << "Erro ao abrir o arquivo json." << std::endl;
                return nullptr;
            }
            json dados;
            try {
                arquivoEntrada >> dados;
            } catch (const json::parse_error& e) {
                cerr << "Erro ao interpretar o arquivo JSON: " << e.what() << endl;
                return nullptr; // Retorna se o erro for detectado
            }

            return dados;
        };   
        


    //Adicionar novos metodos a essa classe para manipular o arquivo JSON




};


#endif