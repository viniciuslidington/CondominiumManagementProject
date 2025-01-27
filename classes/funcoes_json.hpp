#ifndef FUNCOES_JSON_HPP
#define FUNCOES_JSON_HPP

#include "../json.hpp"
#include <string>

using json = nlohmann::json;

// Declaração da função para carregar um arquivo JSON
json carregarArquivo(const std::string& caminho);

// Declaração da função para salvar um arquivo JSON
void salvarArquivo(const std::string& caminho, const json& dados);

#endif // FUNCOES_JSON_HPP
