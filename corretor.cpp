// corretor.cpp

#include "corretor.h"
using namespace std;

int Corretor::nextId = 1;

Corretor::Corretor(const string& telefone, bool avaliador, double lat, double lng, const string& nome)
    : telefone(telefone), avaliador(avaliador), lat(lat), lng(lng), nome(nome) {
    id = nextId++;
}

int Corretor::getId() const {
    return id;
}

string Corretor::getNome() const {
    return nome;
}

string Corretor::getTelefone() const {
    return telefone;
}

bool Corretor::isAvaliador() const {
    return avaliador;
}

double Corretor::getLat() const {
    return lat;
}

double Corretor::getLng() const {
    return lng;
}
