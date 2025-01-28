#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <iostream>

using namespace std;

// Declaração da classe User
class User {
protected:
    // Variáveis membro privadas
    string user_name;
    string user_email;
    string user_phone;
    string user_type;
    string user_password;
    long user_cpf;

public:
    // Construtor
    User(const string& name, const string& email, const string& phone, const string& type, const string& password, const long& cpf);

    // Getters
    const string& getName() const;
    const string& getEmail() const;
    const string& getPhone() const;
    const string& getType() const;
    const string& getPassword() const;
    const long& getCpf() const;

    // Setters
    void setName(const string& name);
    void setEmail(const string& email);
    void setPhone(const string& phone);
    void setType(const string& type);
    void setPassword(const string& password);
    void setCpf(const long& cpf);

    // Método virtual
    virtual void exibirInformacoes() const;
};

#endif
