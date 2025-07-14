// cliente.cpp

#include "cliente.h"
using namespace std;

int Cliente::nextId = 1;

Cliente::Cliente(const string& telefone, const string& nome)
    : telefone(telefone), nome(nome) {
    id = nextId++;
}

int Cliente::getId() const {
    return id;
}

string Cliente::getNome() const {
    return nome;
}

string Cliente::getTelefone() const {
    return telefone;
}