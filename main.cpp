// main.cpp

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include "corretor.h"
#include "cliente.h"
#include "imovel.h"
using namespace std;

// função Haversine
constexpr double EARTH_R = 6371.0;

double haversine(double lat1, double lon1, double lat2, double lon2) {
    auto deg2rad = [](double d) { return d * M_PI / 180.0; };
    double dlat = deg2rad(lat2 - lat1);
    double dlon = deg2rad(lon2 - lon1);
    double a = pow(sin(dlat / 2), 2) +
               cos(deg2rad(lat1)) * cos(deg2rad(lat2)) *
               pow(sin(dlon / 2), 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return EARTH_R * c;
}

// Struct para armazenar visitas agendadas
struct Visita {
    int imovelId;
    int hora;
    int minuto;

    Visita(int id, int h, int m) : imovelId(id), hora(h), minuto(m) {}
};

// Função Principal
int main() {
    vector<Corretor> corretores;
    vector<Cliente> clientes;
    vector<Imovel> imoveis;

    // Leitura dos Corretores
    int numCorretores;
    cin >> numCorretores;
    for (int i = 0; i < numCorretores; ++i) {
        string telefone;
        int avaliadorInt;
        double lat, lng;
        string nome;

        cin >> telefone >> avaliadorInt >> lat >> lng;
        getline(cin >> ws, nome);

        Corretor c(telefone, avaliadorInt == 1, lat, lng, nome);
        corretores.push_back(c);
    }

    // Leitura dos Clientes 
    int numClientes;
    cin >> numClientes;
    for (int i = 0; i < numClientes; ++i) {
        string telefone;
        string nome;

        cin >> telefone;
        getline(cin >> ws, nome);

        Cliente cliente(telefone, nome);
        clientes.push_back(cliente);
    }

    // Leitura dos Imóveis 
    int numImoveis;
    cin >> numImoveis;
    for (int i = 0; i < numImoveis; ++i) {
        string tipoStr;
        int proprietarioId;
        double lat, lng, preco;
        string endereco;

        cin >> tipoStr >> proprietarioId >> lat >> lng >> preco;
        getline(cin >> ws, endereco);

        Imovel imovel(tipoStr, proprietarioId, lat, lng, preco, endereco);
        imoveis.push_back(imovel);
    }

    // Filtro de Avaliadores 
    vector<Corretor> avaliadores;
    for (const Corretor& c : corretores) {
        if (c.isAvaliador()) {
            avaliadores.push_back(c);
        }
    }

    // Distribuição Round-Robin dos Imóveis
    vector<vector<Imovel>> imoveisPorAvaliador(avaliadores.size());

    sort(imoveis.begin(), imoveis.end(), [](const Imovel& a, const Imovel& b) {
        return a.getId() < b.getId();
    });

    int index = 0;
    for (const Imovel& imovel : imoveis) {
        imoveisPorAvaliador[index].push_back(imovel);
        index = (index + 1) % avaliadores.size();
    }

    // Agendamento e Impressão da Agenda 
    for (size_t i = 0; i < avaliadores.size(); ++i) {
        const Corretor& corretor = avaliadores[i];
        vector<Imovel> agenda = imoveisPorAvaliador[i];

        int hora = 9, minuto = 0;
        double atualLat = corretor.getLat();
        double atualLng = corretor.getLng();

        vector<Visita> visitas;

        while (!agenda.empty()) {
            // Encontra o imóvel mais próximo
            auto itMaisProximo = agenda.begin();
            double menorDist = haversine(atualLat, atualLng, itMaisProximo->getLat(), itMaisProximo->getLng());

            for (auto it = agenda.begin(); it != agenda.end(); ++it) {
                double dist = haversine(atualLat, atualLng, it->getLat(), it->getLng());
                if (dist < menorDist) {
                    menorDist = dist;
                    itMaisProximo = it;
                }
            }

            // Tempo de deslocamento (usar floor para garantir fidelidade)
            int deslocamento = static_cast<int>(floor(menorDist * 2));
            minuto += deslocamento;
            if (minuto >= 60) {
                hora += minuto / 60;
                minuto %= 60;
            }

            // Agendar a visita
            visitas.emplace_back(itMaisProximo->getId(), hora, minuto);

            // Adicionar 60 minutos da visita
            minuto += 60;
            if (minuto >= 60) {
                hora += minuto / 60;
                minuto %= 60;
            }

            atualLat = itMaisProximo->getLat();
            atualLng = itMaisProximo->getLng();
            agenda.erase(itMaisProximo);
        }

        // Impressão da agenda
        cout << "Corretor " << corretor.getId() << endl;
        for (const Visita& v : visitas) {
            cout << setfill('0') << setw(2) << v.hora << ":"
                 << setw(2) << v.minuto << " Imóvel " << v.imovelId << endl;
        }

        if (i != avaliadores.size() - 1) {
            cout << endl;
        }
    }

    return 0;
}