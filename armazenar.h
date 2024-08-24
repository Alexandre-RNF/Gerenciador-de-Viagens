#ifndef ARMAZENAR_H
#define ARMAZENAR_H

#include "bibliotecas.h" // Fstream está aqui 
#include "classes.h"

// ARMAZENA AS CIDADES
void Armazenar_cidades(std::unordered_map<std::string, Cidade> mapa_cidades){
    // Inicialização e criação do arquivo 
    std::fstream cidades;
    cidades.open("cidades.txt", std::ios::out);

    // Verificação para ver se o arquivo foi criado com sucesso 
    if(!cidades){
        std::cout << "Não foi possível abrir o arquivo para armazenamento" << std::endl; 
    }
    else{
        std::cout << "Dados sendo armazenados..." << std::endl;
    }

    // Escrevendo no arquivo
    // Cidades --------------------------------------------------------------
        for(const auto& par : mapa_cidades){
            cidades << par.first << std::endl;
        } 
    cidades.close();
}

// ARMAZENA OS TRAJETOS 
void Armazenar_trajetos(std::vector <Trajeto> mapa_trajetos){
    // Inicialização e criação do arquivo
    std::fstream trajetos;
    trajetos.open("trajetos.txt", std::ios::out);

    // Verificação para ver se o arquivo foi criado com sucesso
    if(!trajetos){
        std::cout << "Não foi possível abrir o arquivo para armazenamento" << std::endl; 
    } 
    else{
        std::cout << "Dados sendo armazenados..." << std::endl; 
    }

    // Escrevendo no arquivo
    for(int i = 0; i < mapa_trajetos.size(); i++){
        trajetos << mapa_trajetos[i].getOrigem()->getNome() << std::endl; 
        trajetos << mapa_trajetos[i].getDestino()->getNome() << std::endl;
        trajetos << mapa_trajetos[i].getTipo() << std::endl;
        trajetos << mapa_trajetos[i].getDistancia() << " km" << std::endl;
        trajetos << std::endl; 
    }

    trajetos.close(); 
}

// ARMAZENA OS TRANSPORTES
void Armazenar_transportes(std::unordered_map<std::string, Transporte> mapa_transportes){
    //Inicialização e criação do arquivo
    std::fstream transportes; 
    transportes.open("transportes.txt", std::ios::out);

    if(!transportes){
        std::cout << "Não foi possível abrir o arquivo para armazenamento" << std::endl; 
    } 
    else{
        std::cout << "Dados sendo armazenados..." << std::endl; 
    }

    for(const auto& par : mapa_transportes){
            const Transporte& transporte = par.second;
            transportes << transporte.getNome() << " "
                        << transporte.getTipo() << " "
                        << transporte.getCapacidade() << " "
                        << transporte.getVelocidade() << " "
                        << transporte.getDistanciaEntreDescansos() << " "
                        << transporte.getTempoDescanso() << " "
                        << transporte.getTempoDescansoAtual() << " "
                        << (transporte.getLocalAtual() ? transporte.getLocalAtual()->getNome() : "NULL")
                        << std::endl;
    }

    transportes.close();
    std::cout << "Dados armazenados com sucesso!" << std::endl;
} 

// ARMAZENA OS PASSAGEIROS
void Armazenar_passageiro(std::unordered_map<std::string, Passageiro> mapa_passageiros){
    std::fstream passageiros; 
    passageiros.open("passageiros.txt",std::ios::out);

    if(!passageiros){
        std::cout << "Não foi possível abrir o arquivo para armazenamento" << std::endl;
    }
    else{
        std::cout << "Dados sendo armazenados"; 
    }

    for(const auto& par : mapa_passageiros){
        const Passageiro& passageiro = par.second; 
        passageiros << passageiro.getNome() << " "
                    << (passageiro.getLocalAtual() ? passageiro.getLocalAtual()->getNome() : "NULL")
                    << std::endl; 
    }
    passageiros.close();
    std::cout << "Dados armazenados com sucesso!" << std::endl;  
}

// ARMAZENA AS VIAGENS - PRECISO DISSO PARA OS RELATÓRIOS
void Armazenar_viagens(const Viagem& viagem){
    // Inicialização e criação do arquivo
    std::fstream viagens;
    viagens.open("viagens.txt", std::ios::out | std::ios::app); // Usando ios::app para adicionar ao final do arquivo

    // Verificação para ver se o arquivo foi criado com sucesso
    if(!viagens){
        std::cout << "Não foi possível abrir o arquivo para armazenamento" << std::endl; 
        return;
    } 
    else{
        std::cout << "Dados sendo armazenados..." << std::endl; 
    }

    // Escrevendo no arquivo
    viagens << "Transporte: " << viagem.getTransporte()->getNome() << std::endl;
    viagens << "Origem: " << viagem.getOrigem()->getNome() << std::endl;
    viagens << "Destino: " << viagem.getDestino()->getNome() << std::endl;
    viagens << "Horas em Trânsito: " << viagem.getHorasEmTransito() << std::endl;
    viagens << "Em Andamento: " << (viagem.isEmAndamento() ? "Sim" : "Não") << std::endl;

    viagens << "Passageiros: ";
    for (const auto& passageiro : viagem.getPassageiros()) {
        viagens << passageiro->getNome() << " ";
    }
    viagens << std::endl;

    viagens << "---------------------------------------------" << std::endl;

    viagens.close();
    std::cout << "Dados armazenados com sucesso!" << std::endl;
}

#endif



