// cliente.h

#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>
using namespace std;

class Cliente {
private:
    static int nextId;
    int id;
    string nome;
    string telefone;

public:
    Cliente(const string& telefone, const string& nome);

    int getId() const;
    string getNome() const;
    string getTelefone() const;
};

#endif