#include "bibliotecas.h"
#include "classes.h" 

#ifndef CARREGAR_H
#define CARREGAR_H

void Carregar_cidades(std::unordered_map<std::string, Cidade>& mapa_cidades){
    std::fstream cidades;
    cidades.open("cidades.txt", std::ios::in);

    if(!cidades){
        std::cout << "Erro ao carregar os dados..." << std::endl;
    }
    else{
        std::string linha;
        while(std::getline(cidades, linha)){
            if(!linha.empty()){
                Cidade cidade(linha);
                mapa_cidades.insert({linha, cidade});
            }
        }
        cidades.close();
    }
}

void Carregar_trajetos(std::vector<Trajeto>& mapa_trajetos){
    std::fstream trajetos;
    trajetos.open("trajetos.txt", std::ios::in);

    if(!trajetos){
        std::cout << "Erro ao carregar os dados..." << std::endl;
        return;
    }

    std::string linha;
    std::string origem, destino;
    char tipo;
    int distancia;

    while (std::getline(trajetos, linha)){
        if(!linha.empty()){
            origem = linha;

            if(std::getline(trajetos, linha)){
                destino = linha;
            }

            if(std::getline(trajetos, linha)){
                tipo = linha[0];
            }

            if(std::getline(trajetos, linha)){
                linha = linha.substr(0, linha.find(" km"));
                distancia = std::stoi(linha);
            }

            Cidade* cidadeOrigem = new Cidade(origem);
            Cidade* cidadeDestino = new Cidade(destino);
            Trajeto trajeto(cidadeOrigem, cidadeDestino, tipo, distancia);
            mapa_trajetos.push_back(trajeto);
        }
    }

    trajetos.close();
}

void Carregar_transportes(std::unordered_map<std::string, Transporte>& mapa_transportes, std::unordered_map<std::string, Cidade>& mapa_cidades){
    std::fstream transportes;
    transportes.open("transportes.txt", std::ios::in);

    if (!transportes) {
        std::cout << "Erro ao carregar os dados..." << std::endl;
        return;
    }

    // Variáveis para montar o transporte 
    std::string nome; 
    std::string localAtualNome; 
    char tipo;
    int capacidade, velocidade, distancia_entre_descansos, tempo_de_descanso, tempo_de_descanso_atual;

    while(transportes >> nome >> tipo >> capacidade >> velocidade >> distancia_entre_descansos >> tempo_de_descanso >> tempo_de_descanso_atual >> localAtualNome){
        // Meu deus o fuzuê que é mexer com ponteiro 
        Cidade* localAtual = nullptr;
        auto it = mapa_cidades.find(localAtualNome);
        if(it != mapa_cidades.end()){
            localAtual = &it->second;
        }

        // Criação do objeto Transporte
        Transporte transporte(nome, tipo, capacidade, velocidade, distancia_entre_descansos, tempo_de_descanso, localAtual, tempo_de_descanso_atual);

        // Inserção no mapa
        mapa_transportes.insert({nome, transporte});
    }

    transportes.close();
}

void Carregar_passageiros(std::unordered_map<std::string, Passageiro>& mapa_passageiros, std::unordered_map<std::string, Cidade>& mapa_cidades){
    std::fstream passageiros;
    passageiros.open("passageiros.txt", std::ios::in);

    if(!passageiros){ 
        std::cout << "Erro ao carregar os dados..." << std::endl;
        return;  
    }

    std::string nome; 
    std::string localAtualNome;

    while(passageiros >> nome >> localAtualNome){
        Cidade* localAtual = nullptr;
        auto it = mapa_cidades.find(localAtualNome);
        if(it != mapa_cidades.end()){
            localAtual = &it->second; 
        }

        //Criação do objeto passageiro
        Passageiro passageiro (nome);

        //Inserção no mapa
        mapa_passageiros.insert({nome, passageiro});   
    }

    passageiros.close();    
}

void Carregar_viagens(std::unordered_map<std::string, Cidade>& mapa_cidades, 
                     std::unordered_map<std::string, Transporte>& mapa_transportes, 
                     std::vector<Viagem>& mapa_viagens){
    std::ifstream viagens("viagens.txt");

    if(!viagens){
        std::cout << "Erro ao abrir o arquivo de viagens." << std::endl;
        return;
    }

    std::string linha, nomeTransporte, nomeOrigem, nomeDestino;
    int horasEmTransito = 0;
    bool emAndamento = false;
    std::vector<Passageiro*> passageiros;

    while (std::getline(viagens, linha)) {
        if (linha.find("Transporte:") != std::string::npos) {
            // Se já existirem dados de uma viagem anterior, armazene-os
            if (!nomeTransporte.empty()) {
                auto itTransporte = mapa_transportes.find(nomeTransporte);
                auto itOrigem = mapa_cidades.find(nomeOrigem);
                auto itDestino = mapa_cidades.find(nomeDestino);

                if (itTransporte != mapa_transportes.end() && itOrigem != mapa_cidades.end() && itDestino != mapa_cidades.end()) {
                    Transporte& transporte = itTransporte->second;
                    Cidade* origem = &itOrigem->second;
                    Cidade* destino = &itDestino->second;

                    Viagem novaViagem(&transporte, passageiros, origem, destino);
                    // Adiciona as horas em trânsito e status de andamento
                    // Dado que você não pode modificar diretamente na viagem, utilize setters apropriados se houver
                    // novaViagem.setHorasEmTransito(horasEmTransito);
                    // novaViagem.setEmAndamento(emAndamento);

                    mapa_viagens.push_back(novaViagem);
                }
            }

            // Reseta os dados para a nova viagem
            nomeTransporte = linha.substr(linha.find(":") + 2);
            passageiros.clear();
            horasEmTransito = 0;
            emAndamento = false;
        } else if (linha.find("Origem:") != std::string::npos) {
            nomeOrigem = linha.substr(linha.find(":") + 2);
        } else if (linha.find("Destino:") != std::string::npos) {
            nomeDestino = linha.substr(linha.find(":") + 2);
        } else if (linha.find("Horas em Trânsito:") != std::string::npos) {
            horasEmTransito = std::stoi(linha.substr(linha.find(":") + 2));
        } else if (linha.find("Em Andamento:") != std::string::npos) {
            emAndamento = linha.substr(linha.find(":") + 2) == "Sim";
        } else if (linha.find("Passageiros:") != std::string::npos) {
            std::string passageiroNome = linha.substr(linha.find(":") + 2);
            Passageiro* passageiro = new Passageiro(passageiroNome, &mapa_cidades[nomeOrigem]);
            passageiros.push_back(passageiro);
        }
    }

    // Adiciona a última viagem lida (se houver)
    if (!nomeTransporte.empty()) {
        auto itTransporte = mapa_transportes.find(nomeTransporte);
        auto itOrigem = mapa_cidades.find(nomeOrigem);
        auto itDestino = mapa_cidades.find(nomeDestino);

        if (itTransporte != mapa_transportes.end() && itOrigem != mapa_cidades.end() && itDestino != mapa_cidades.end()) {
            Transporte& transporte = itTransporte->second;
            Cidade* origem = &itOrigem->second;
            Cidade* destino = &itDestino->second;

            Viagem novaViagem(&transporte, passageiros, origem, destino);
            // novaViagem.setHorasEmTransito(horasEmTransito);
            // novaViagem.setEmAndamento(emAndamento);

            mapa_viagens.push_back(novaViagem);
        }
    }

    viagens.close();
}





#endif
