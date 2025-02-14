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
    
    // Verifica se há um histórico de atualizações
    if (data.contains("historico_atualizacoes") && data["historico_atualizacoes"].is_array()) {
        if (!data["historico_atualizacoes"].empty()) {
            string ultimaAtualizacao = data["historico_atualizacoes"].back();
            if (ultimaAtualizacao == mesAtual) {
                return false;
            }
        }
    }
    
    return true;
}

void Sistema::removerUsuario(const long& cpf, json& usuariosJson){
     // Carregar os dados dos usuários
    string caminhoUnidades = "bdjson/unidades.json"; // Caminho do arquivo das unidades
    json unidadesJson = carregarArquivo(caminhoUnidades); // Carregar os dados das unidades


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
        salvarArquivo(caminhoUnidades, unidadesJson);
        
    } else {
        
    }
}
// Função para atualizar os pagamentos dos moradores
void Sistema::atualizarPagamentos() {
    string caminhoUsuarios = "bdjson/usuarios.json"; // Caminho do arquivo JSON
    json usuariosJson = carregarArquivo(caminhoUsuarios);

    string caminhoSistema = "bdjson/sistema.json"; // Caminho do arquivo JSON
    json sistemaJson = carregarArquivo(caminhoSistema);

    bool existe = true;
    bool achado = false;

    // Verifica se já foi atualizado este mês
    if (!precisaAtualizar(sistemaJson)) {
        
        return;
    }

    while(existe){
        achado = false;
        cout << "iniciando while" << endl;
        for (auto& usuario3 : usuariosJson["usuarios"]) {
        if (usuario3["tipo"] == "morador" && usuario3.contains("pagamento_em_dia") ) {
            if(usuario3["pagamento_em_dia"] == false){
                removerUsuario(usuario3["cpf"], usuariosJson);
                break;
                
                } 
            }
        }
        for (auto& usuario2 : usuariosJson["usuarios"]){
            if (usuario2["tipo"] == "morador" && usuario2.contains("pagamento_em_dia") ) {
                if(usuario2["pagamento_em_dia"] == false){
                    achado = true;
                    break;
                    }
            }
        }
        if (!achado){ existe = false;}

    }

    //Remove os moradores que não realizaram o pagamento do mês anterior
    // Atualiza os moradores
    for (auto& usuario : usuariosJson["usuarios"]) {
        if (usuario["tipo"] == "morador" && usuario.contains("pagamento_em_dia")) {
            usuario["pagamento_em_dia"] = false;
        }
    }

    // Adiciona a nova atualização no histórico
    if (!sistemaJson.contains("historico_atualizacoes") || !sistemaJson["historico_atualizacoes"].is_array()) {
        sistemaJson["historico_atualizacoes"] = json::array();
    }
    sistemaJson["historico_atualizacoes"].push_back(getMesAtual());
    
    // Salva no arquivo
    salvarArquivo(caminhoUsuarios, usuariosJson);
    salvarArquivo(caminhoSistema, sistemaJson);
    
}
