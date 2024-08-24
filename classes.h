#ifndef CLASSES_H
#define CLASSES_H

// Bibliotecas do programa
#include "bibliotecas.h"

class Cidade{
private:
    std::string nome; 
public:
    // Declaração dos construtores e métodos
    Cidade(); // Construtor padrão
    Cidade(std::string nome);                   
    std::string getNome();                      
};

// Implementação dos construtores e métodos
Cidade::Cidade() : nome("") {}

Cidade::Cidade(std::string nome) : nome(nome) {}

std::string Cidade::getNome(){
    return nome;
}

// Classe Trajeto
class Trajeto {
private:
    Cidade* origem;
    Cidade* destino;
    char tipo; // 'A' para Aquático, 'T' para Terrestre
    int distancia;
public:
    Trajeto(Cidade* origem, Cidade* destino, char tipo, int distancia)
        : origem(origem), destino(destino), tipo(tipo), distancia(distancia) {}

    Cidade* getOrigem() const { // Tornando const
        return origem;
    }

    Cidade* getDestino() const { // Tornando const
        return destino;
    }

    char getTipo() const { // Tornando const
        return tipo;
    }

    int getDistancia() const { // Tornando const
        return distancia;
    }
};

// Classe Transporte
class Transporte {
private:
    std::string nome;
    char tipo; // 'A' para Aquático, 'T' para Terrestre
    int capacidade; // número de passageiros
    int velocidade; // km/h
    int distancia_entre_descansos; // em km
    int tempo_de_descanso; // em horas
    int tempo_de_descanso_atual;  // em horas
    Cidade* localAtual;

public:
    Transporte(std::string nome, char tipo, int capacidade, int velocidade, int distancia_entre_descansos, int tempo_de_descanso, Cidade* localAtual = nullptr, int tempo_de_descanso_atual = 0)
        : nome(nome), tipo(tipo), capacidade(capacidade), velocidade(velocidade), distancia_entre_descansos(distancia_entre_descansos), tempo_de_descanso(tempo_de_descanso), localAtual(localAtual), tempo_de_descanso_atual(tempo_de_descanso_atual){}

    std::string getNome() const{
        return nome;
    }

    char getTipo() const{
        return tipo;
    }

    int getCapacidade() const{
        return capacidade;
    }

    int getVelocidade() const{
        return velocidade;
    }

    int getDistanciaEntreDescansos() const{
        return distancia_entre_descansos;
    }

    int getTempoDescanso() const{
        return tempo_de_descanso;
    }

    int getTempoDescansoAtual() const{
        return tempo_de_descanso_atual;
    }

    Cidade* getLocalAtual() const{
        return localAtual;
    }

    void setLocalAtual(Cidade* local){
        localAtual = local;
    }
};

// Classe Passageiro
class Passageiro {
private:
    std::string nome;
    Cidade* localAtual;
public:
    Passageiro(std::string nome, Cidade* localAtual = nullptr)
        : nome(nome), localAtual(localAtual){}
    std::string getNome() const{
        return nome; 
    }
    Cidade* getLocalAtual() const{
        return localAtual;  
    }
    void setLocalAtual(Cidade* local);
};

// Classe Viagem
class Viagem {
private:
    Transporte* transporte;
    std::vector<Passageiro*> passageiros;
    Cidade* origem;
    Cidade* destino;
    int horasEmTransito;
    bool emAndamento;

public:
    Viagem(Transporte* transporte, std::vector<Passageiro*> passageiros, Cidade* origem, Cidade* destino)
        : transporte(transporte), passageiros(passageiros), origem(origem), destino(destino), horasEmTransito(0), emAndamento(false) {}

    // Métodos getters
    Transporte* getTransporte() const{
        return transporte;
    }

    const std::vector<Passageiro*>& getPassageiros() const{
        return passageiros;
    }

    Cidade* getOrigem() const{
        return origem;
    }

    Cidade* getDestino() const{
        return destino;
    }

    int getHorasEmTransito() const{
        return horasEmTransito;
    }

    bool isEmAndamento() const{
        return emAndamento;
    }
};



#endif 
