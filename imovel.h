// imovel.h

#ifndef IMOVEL_H
#define IMOVEL_H

#include <string>
using namespace std;

enum TipoImovel { Casa, Apartamento, Terreno };

class Imovel {
private:
    static int nextId;
    int id;
    TipoImovel tipo;
    int proprietarioId;
    double lat;
    double lng;
    double preco;
    string endereco;

public:
    Imovel(const string& tipoStr, int proprietarioId, double lat, double lng, double preco, const string& endereco);

    int getId() const;
    TipoImovel getTipo() const;
    int getProprietarioId() const;
    double getLat() const;
    double getLng() const;
    double getPreco() const;
    string getEndereco() const;
};

#endif