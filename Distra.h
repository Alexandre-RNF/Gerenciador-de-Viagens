#ifndef DISTRA_H
#define DISTRA_H

#include "classes.h"
#include "bibliotecas.h"
#include "carregar.h"

    std::unordered_map<std::string, Cidade> mapa_cidades;
    std::vector<Trajeto> mapa_trajetos;
    std::unordered_map<std::string, Transporte> mapa_transportes;
    std::unordered_map<std::string, Passageiro> mapa_passageiros;

    bool cidadesIguais(Cidade* a, Cidade* b){
    return a->getNome() == b->getNome();
    }


// Função para encontrar a rota mais curta usando o algoritmo de Dijkstra
    std::pair<std::vector<Cidade*>, int> encontrarMelhorRota(Cidade* origem, Cidade* destino){
    std::unordered_map<std::string, int> distancias;
    std::unordered_map<std::string, Cidade*> anteriores;
    std::priority_queue<std::pair<int, Cidade*>, std::vector<std::pair<int, Cidade*>>, std::greater<>> fila_prioridade;

    std::unordered_map<std::string, Cidade> mapa_cidades;
    std::vector<Trajeto> mapa_trajetos;
    std::unordered_map<std::string, Transporte> mapa_transportes;
    std::unordered_map<std::string, Passageiro> mapa_passageiros;

    Carregar_cidades(mapa_cidades);
    Carregar_trajetos(mapa_trajetos);
    Carregar_transportes(mapa_transportes, mapa_cidades);
    Carregar_passageiros(mapa_passageiros, mapa_cidades);

    for (const auto& it : mapa_cidades){
        distancias[it.first] = INT_MAX;
    }

    distancias[origem->getNome()] = 0;
    fila_prioridade.push({0, origem});

    while (!fila_prioridade.empty()) {
        Cidade* atual = fila_prioridade.top().second;
        fila_prioridade.pop();

        if (cidadesIguais(atual, destino)) break;

        for (const auto& trajeto : mapa_trajetos) {
            if (cidadesIguais(trajeto.getOrigem(), atual)) {
                Cidade* vizinho = trajeto.getDestino();
                int nova_distancia = distancias[atual->getNome()] + trajeto.getDistancia();

                if (nova_distancia < distancias[vizinho->getNome()]) {
                    distancias[vizinho->getNome()] = nova_distancia;
                    anteriores[vizinho->getNome()] = atual;
                    fila_prioridade.push({nova_distancia, vizinho});
                }
            }
        }
    }

    std::vector<Cidade*> caminho;
    int distancia_total = 0;

    for (Cidade* c = destino; c != nullptr; c = anteriores[c->getNome()]) {
        caminho.push_back(c);
        if (c != origem) {
            Cidade* anterior = anteriores[c->getNome()];
            for (const auto& trajeto : mapa_trajetos) {
                if (cidadesIguais(trajeto.getOrigem(), anterior) && cidadesIguais(trajeto.getDestino(), c)) {
                    distancia_total += trajeto.getDistancia();
                    break;
                }
            }
        }
    }

    std::reverse(caminho.begin(), caminho.end());

    if (!caminho.empty() && !cidadesIguais(caminho.front(), origem)) {
        std::cerr << "Erro: o caminho encontrado não começa na origem." << std::endl;
        return {{}, -1};
    }

    return {caminho, distancia_total};
}

void imprimirRota(const std::vector<Cidade*>& rota, int distancia_total) {
    if (rota.empty()) {
        std::cout << "Nenhuma rota encontrada." << std::endl;
        return;
    }

    for (size_t i = 0; i < rota.size(); ++i) {
        std::cout << rota[i]->getNome();
        if (i < rota.size() - 1) {
            std::cout << " -> ";
        }
    }
    // std::cout << "\nDistância total: " << distancia_total << " km" << std::endl; -> Output desnecessário mas talvez eu precise caso necessário
}

// Função para usar a distância total em outro lugar
void usarDistanciaTotal(int distancia_total) {
    std::cout << "A distância total é: " << distancia_total << " km" << std::endl;
}

int Distra_final(){
    Carregar_cidades(mapa_cidades);
    Carregar_trajetos(mapa_trajetos);
    Carregar_transportes(mapa_transportes, mapa_cidades);
    Carregar_passageiros(mapa_passageiros, mapa_cidades);

    std::string cidade_origem_distra, cidade_destino_distra;
    std::cin >> cidade_origem_distra;
    std::cin >> cidade_destino_distra;

    auto it_origem = mapa_cidades.find(cidade_origem_distra);
    auto it_destino = mapa_cidades.find(cidade_destino_distra);
    Cidade* origem = (it_origem != mapa_cidades.end()) ? &it_origem->second : nullptr;
    Cidade* destino = (it_destino != mapa_cidades.end()) ? &it_destino->second : nullptr;

    if (origem && destino){
        std::pair<std::vector<Cidade*>, int> resultado = encontrarMelhorRota(origem, destino);
        if(resultado.second >= 0){
            imprimirRota(resultado.first, resultado.second);
            usarDistanciaTotal(resultado.second); // Usa a distância total
        }
        else{
            std::cout << "Erro ao calcular a rota." << std::endl;
        }
    }
    else{
        std::cout << "Origem ou destino não encontrados." << std::endl;
    }

    return 0;
}

#endif 
