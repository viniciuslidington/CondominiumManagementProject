#include "Sistema.hpp"

// Construtor padrão
Sistema::Sistema() {
    // Qualquer inicialização adicional pode ser feita aqui, se necessário
}

// Função para verificar se hoje é o dia específico do mês
bool Sistema::isDayOfMonth(int day) {
    if (day < 1 || day > 31) {
        std::cerr << "Dia inválido!" << std::endl;
        return false;
    }

    std::time_t t = std::time(nullptr);
    std::tm* local_time = std::localtime(&t);
    return (local_time->tm_mday == day);
}

// Função para atualizar os pagamentos dos moradores
void Sistema::atualizarPagamentos() {
    int dia = 1;
    // Verifica se hoje é o dia especificado
    if (!isDayOfMonth(dia)) {
        cout << "-----------------------------------\n";
        cout << endl;
        std::cout << "Hoje não é o dia " << dia << " do mês. Nenhuma alteração foi feita." << std::endl;
        cout << endl;
        cout << "-----------------------------------\n";
        
        return;
    }
    
    // Lê o arquivo JSON
    string caminhoUsuarios = "bdjson/usuarios.json"; // Caminho do arquivo
    json usuariosJson = carregarArquivo(caminhoUsuarios);

    // Itera sobre os usuários e atualiza o pagamento_em_dia para false se for morador
    for (auto& usuario : usuariosJson["usuarios"]) {
        if (usuario["tipo"] == "morador" && usuario.contains("pagamento_em_dia")) {
            usuario["pagamento_em_dia"] = false;
        }
    }

    // Salva as alterações no arquivo JSON
    salvarArquivo(caminhoUsuarios, usuariosJson);
    cout << "-----------------------------------\n";
    cout << endl;
    std::cout << "Pagamentos dos moradores foram atualizados com sucesso!" << std::endl;
    cout << endl;
    cout << "-----------------------------------\n";
}
