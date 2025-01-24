#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <iostream>

using namespace std;

// Exemplo de uma classe simples
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
    User(const string& name, const string& email,const string& phone, const string& type, const string& password, const long& cpf)
        : user_name(name), user_email(email), user_phone(phone), user_type(type), user_password(password), user_cpf(cpf){};


    const string& getName() const { return user_name; }
    const string& getEmail() const { return user_email; }
    const string& getPhone() const { return user_phone; }
    const string& getType() const { return user_type; }
    const string& getPassword() const { return user_password; }
    const long& getCpf() const { return user_cpf; }

    void setName(const string& name) { user_name = name; }
    void setEmail(const string& email) { user_email = email; }
    void setPhone(const string& phone) { user_phone = phone; }
    void setType(const string& type) { user_type = type; }
    void setPassword(const string& password) { user_password = password; }
    void setCpf(const long& cpf) { user_cpf = cpf; }

};
#endif 
