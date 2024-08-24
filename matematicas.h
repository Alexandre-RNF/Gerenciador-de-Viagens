#ifndef MATEMATICAS_H
#define MATEMATICAS_H

// Bibliotecas do programa
#include "bibliotecas.h"

void calculo_viagem(int distancia, int hora_inicio_viagem, int velocidade_veiculo, int frequencia_pausas_veiculo, int tempo_pausas_veiculo){
    // Distancia = Distancia total do trajeto do ponto de origem até o destino (km)
    // Hora_inicio_viagem = Hora que a viagem começou
    // Velocidade_veiculo = Velocidade em km/h do veículo da viagem
    // Frequencia_pausas_veiculo = A cada x km, o veiculo realiza uma parada
    // Tempo_pausas_veiculo = Quanto tempo dura a parada (em horas)

    // Variáveis1
    int pausas = distancia / frequencia_pausas_veiculo;
    double horas = (distancia / (double)velocidade_veiculo) + (pausas * tempo_pausas_veiculo);
    int hora_chegada = ((int)horas + hora_inicio_viagem) % 24; 


    // Exibindo os resultados
    std::cout << "\n\n=== Dados da viagem ===" << std::endl;
    std::cout << "Distancia percorrida: " << distancia << " km" << std::endl;
    std::cout << "Número de paradas: " << pausas << std::endl;
    std::cout << "Duração da viagem: " << horas << " horas" << std::endl;
    std::cout << "Horário de chegada: " << hora_chegada << ":00"<< std::endl;
}

#endif

