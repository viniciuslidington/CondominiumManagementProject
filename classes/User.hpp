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
    string user_type;
    string user_password;

public:
    User(const string& name, const string& email, const string& type, const string& password)
        : user_name(name), user_email(email), user_type(type), user_password(password){};


    const string& getName() const { return user_name; }
    const string& getEmail() const { return user_email; }
    const string& getType() const { return user_type; }
    const string& getPassword() const { return user_password; }

    void setName(const string& name) { user_name = name; }
    void setEmail(const string& email) { user_email = email; }
    void setType(const string& type) { user_type = type; }
    void setPassword(const string& password) { user_password = password; }

};
#endif 
