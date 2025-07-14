// imovel.cpp

#include "imovel.h"
using namespace std;

int Imovel::nextId = 1;

Imovel::Imovel(const string& tipoStr, int proprietarioId, double lat, double lng, double preco, const string& endereco)
    : proprietarioId(proprietarioId), lat(lat), lng(lng), preco(preco), endereco(endereco) {

    if (tipoStr == "Casa") {
        tipo = Casa;
    } else if (tipoStr == "Apartamento") {
        tipo = Apartamento;
    } else {
        tipo = Terreno;
    }

    id = nextId++;
}

int Imovel::getId() const {
    return id;
}

TipoImovel Imovel::getTipo() const {
    return tipo;
}

int Imovel::getProprietarioId() const {
    return proprietarioId;
}

double Imovel::getLat() const {
    return lat;
}

double Imovel::getLng() const {
    return lng;
}

double Imovel::getPreco() const {
    return preco;
}

string Imovel::getEndereco() const {
    return endereco;
}