// corretor.h

#ifndef CORRETOR_H
#define CORRETOR_H

#include <string>
using namespace std;

class Corretor {
private:
    static int nextId;  // Para gerar os IDs automáticos
    int id;
    string nome;
    string telefone;
    bool avaliador;
    double lat;
    double lng;

public:
    // Construtor
    Corretor(const string& telefone, bool avaliador, double lat, double lng, const string& nome);

    // Getters
    int getId() const;
    string getNome() const;
    string getTelefone() const;
    bool isAvaliador() const;
    double getLat() const;
    double getLng() const;
};

#endif