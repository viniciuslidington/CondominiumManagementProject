#include "Resident.hpp"


 Resident::Resident(const string& name, const string& email, const string& phone, const string& type, 
    const string& senha, const long& cpf, bool& pagamento)
: User(name, email, phone, type, senha, cpf), pagamento_em_dia(pagamento){}