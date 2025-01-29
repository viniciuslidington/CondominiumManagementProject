#include "Sistema.hpp"

// Construtor padrão
Sistema::Sistema() {}

// Função para verificar se hoje é um determinado dia do mês
bool Sistema::isDayOfMonth(int day) {
    if (day < 1 || day > 31) {
        std::cerr << "Dia inválido!" << std::endl;
        return false;
    }

    std::time_t t = std::time(nullptr);
    std::tm* local_time = std::localtime(&t);
    return (local_time->tm_mday == day);
}

// Retorna o mês atual no formato "YYYY-MM"
string Sistema::getMesAtual() {
    std::time_t t = std::time(nullptr);
    std::tm* local_time = std::localtime(&t);
    
    char buffer[8];
    std::strftime(buffer, sizeof(buffer), "%Y-%m", local_time);
    
    return string(buffer);
}

// Verifica se é necessário atualizar os pagamentos
bool Sistema::precisaAtualizar(const json& data) {
    string mesAtual = getMesAtual();
    
    // Se o campo "ultima_atualizacao" não existir ou for diferente do mês atual, precisa atualizar
    if (!data.contains("ultima_atualizacao") || data["ultima_atualizacao"] != mesAtual) {
        return true;
    }
    
    return false;
}

// Função para atualizar os pagamentos dos moradores
void Sistema::atualizarPagamentos() {
    string caminhoUsuarios = "bdjson/usuarios.json"; // Caminho do arquivo JSON
    json usuariosJson = carregarArquivo(caminhoUsuarios);

    string caminhoSistema = "bdjson/sistema.json"; // Caminho do arquivo JSON
    json sistemaJson = carregarArquivo(caminhoSistema);

    // Verifica se já foi atualizado este mês
    if (!precisaAtualizar(sistemaJson)) {
        std::cout << "Os pagamentos já foram atualizados neste mês. Nenhuma alteração foi feita." << std::endl;
        return;
    }

    // Atualiza os moradores
    for (auto& usuario : usuariosJson["usuarios"]) {
        if (usuario["tipo"] == "morador" && usuario.contains("pagamento_em_dia")) {
            usuario["pagamento_em_dia"] = false;
        }
    }

    // Atualiza a última data de atualização
    sistemaJson["ultima_atualizacao"] = getMesAtual();
    
    // Salva no arquivo
    salvarArquivo(caminhoUsuarios, usuariosJson);
    salvarArquivo(caminhoSistema, sistemaJson);
    std::cout << "Pagamentos dos moradores foram atualizados com sucesso!" << std::endl;
}
