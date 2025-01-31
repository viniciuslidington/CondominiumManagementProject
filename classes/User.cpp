#include "User.hpp"

// Construtor
User::User(const string& name, const string& email, const string& phone, const string& type, const string& password, const long& cpf)
    : user_name(name), user_email(email), user_phone(phone), user_type(type), user_password(password), user_cpf(cpf) {}

// Getters
const string& User::getName() const { return user_name; }
const string& User::getEmail() const { return user_email; }
const string& User::getPhone() const { return user_phone; }
const string& User::getType() const { return user_type; }
const string& User::getPassword() const { return user_password; }
const long& User::getCpf() const { return user_cpf; }

// Setters
void User::setName(const string& name) { user_name = name; }
void User::setEmail(const string& email) { user_email = email; }
void User::setPhone(const string& phone) { user_phone = phone; }
void User::setType(const string& type) { user_type = type; }
void User::setPassword(const string& password) { user_password = password; }
void User::setCpf(const long& cpf) { user_cpf = cpf; }

// Método virtual
void User::exibirInformacoes() const {
    cout << "=============================" << endl;
    cout << "       Informações do Usuário" << endl;
    cout << "=============================" << endl;
    cout << "Nome    : " << user_name << endl;
    cout << "Email   : " << user_email << endl;
    cout << "Telefone: " << user_phone << endl;
    cout << "Tipo    : " << user_type << endl;
    cout << "CPF     : " << user_cpf << endl;
    cout << "=============================" << endl;
}
