#include "Resident.hpp"
#include <iostream>

using namespace std;

// Construtor
Resident::Resident(const string& name, const string& email, const string& phone, const string& type, 
                   const string& senha, const long& cpf, bool& pagamento) 
    : User(name, email, phone, type, senha, cpf), pagamento_em_dia(pagamento) {}

// Função para reservar área comum -- COPIAR DA MANAGER
void Resident::reservarAreaComum() {
    cout << "Reservando uma área comum...\n";
    // Código para a lógica de reserva de área comum
}

// Função para visualizar avisos
void Resident::verAvisos() {
    cout << "Exibindo avisos para o residente...\n";
    // Código para exibir avisos
}

// Função para enviar feedback
void Resident::feedback() {
    cout << "Enviando feedback...\n";
    // Código para enviar feedback
}

// Função para visualizar regras
void Resident::verRegras() {
    cout << "Exibindo as regras do condomínio...\n";
    // Código para exibir regras
}

// Função para visualizar funcionários
void Resident::verFuncionarios() {
    cout << "Exibindo a lista de funcionários do condomínio...\n";
    // Código para exibir funcionários
}
