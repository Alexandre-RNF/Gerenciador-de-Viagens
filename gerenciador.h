#ifndef GERENCIADOR_H
#define GERENCIADOR_H

// Definições
#include "bibliotecas.h"
#include "classes.h"

// Modularização
#include "Distra.h" // Conjunto de funções para 
#include "matematicas.h"

// Recebe os dados cadastrados, iremos trabalhar com eles
void Gerenciador    (const std::unordered_map<std::string, Cidade>& mapa_cidades, 
                    const std::vector<Trajeto>& mapa_trajetos, 
                    const std::unordered_map<std::string, Transporte>& mapa_transportes, 
                    const std::unordered_map<std::string, Passageiro>& mapa_passageiros)
{
   // Variáveis Internas
   // Cidade de origem e destino 
   std::string cidade_origem_gerenciador, cidade_destino_gerenciador;
   // Transporte da viagem
   std::string transporte_gerenciador;
   // Passageiros da viagem  
    std::vector<Passageiro*> passageiros;
    std::string input_passageiro;
    // Hora
    int hora; 

   // Lista as cidades para o usuário  
   std::cout << "Exibindo cidades disponíveis:" << std::endl;
   for(const auto& pair : mapa_cidades){
       std::cout << pair.first << std::endl;
   }

   // Input do usuário - Origem e Destino
   std::cout << "Digite a cidade de origem: " << std::endl;
   std::cin >> cidade_origem_gerenciador;
   if(mapa_cidades.find(cidade_origem_gerenciador) == mapa_cidades.end()){
       std::cout << "Cidade de origem não encontrada." << std::endl;
       return;
   }

   std::cout << "Digite a cidade destino: " << std::endl;
   std::cin >> cidade_destino_gerenciador; 
   if(mapa_cidades.find(cidade_destino_gerenciador) == mapa_cidades.end()){
       std::cout << "Cidade de destino não encontrada." << std::endl;
       return;
   }

   if(cidade_origem_gerenciador == cidade_destino_gerenciador){
        std::cout << "A viagem está feita!!! Você nem precisa sair da sua cidade para chegar nessa cidade!!!" << std::endl; 
        return; 
    }

    std::cout << " " << std::endl; // Espaço para tornar a parede de informações mais agradável ao usuário

    std::cout << "Exibindo transportes disponíveis:" << std::endl;
    // Falta adicionar: Imprime todos em que Cidade Atual = NULL ou que Cidade Atual = Cidade de origem
    for(const auto& pair : mapa_transportes){
        std::cout << pair.first << std::endl; 
    }
    std::cout << "Digite o transporte da viagem: " << std::endl;
    std::cin >> transporte_gerenciador; 
    if(mapa_transportes.find(transporte_gerenciador) == mapa_transportes.end()){
        std::cout << "Transporte não encontrado." << std::endl;
        return;  
    } 
    // Adicionar checador para ver se atinge as condições mesmo 

    std::cout << " " << std::endl; // Espaço para tornar a parede de informações mais agradável ao usuário

    std::cout << "Exibindo passageiros disponíveis:" << std::endl; 
    // Falta adicionar: Imprime todos em que Cidade Atual = NULL ou que Cidade atual = Cidade de Origem
    for(const auto& pair : mapa_passageiros){
        std::cout << pair.first << std::endl; 
    }
    
    std::cout << "\nO transporte escolhido possui uma capacidade de " << mapa_transportes.at(transporte_gerenciador).getCapacidade() << " passageiros" << std::endl;

    // Preenchendo os veículos com os passageiros
    int passageiros_adicionados = 0;
    while(true){
        std::cout << "Digite o nome do passageiro " << (passageiros_adicionados + 1) << " ou digite 'ok' para encerrar:" << std::endl;
        std::cin >> input_passageiro;
        if(input_passageiro == "ok"){
            std::cout << "Passageiros atribuidos!!!" << std::endl;  
            break;
        }

        auto it = mapa_passageiros.find(input_passageiro);
        if(it != mapa_passageiros.end()){
            passageiros.push_back(const_cast<Passageiro*>(&it->second));
            passageiros_adicionados++;
        }
        else{
            std::cout << "Passageiro não encontrado." << std::endl;
        }


        if(passageiros_adicionados == mapa_transportes.at(transporte_gerenciador).getCapacidade()){
            std::cout << "Capacidade máxima atingida." << std::endl;
            break;
        }
    }

    // Obtendo a hora de partida da viagem
    std::cout << "\nDigite a hora de partida da viagem: " << std::endl;

    // Loop até digitar hora válida
    while(true){
        std::cin >> hora;
        if(hora < 0 || hora > 23){
            std::cout << "Hora inválida. Deve estar entre 0 e 23" << std::endl; 
        }
        else{
            break; 
        }
    }

    int distancia;

    // Cálculo da melhor rota
    auto it_origem = mapa_cidades.find(cidade_origem_gerenciador);
    auto it_destino = mapa_cidades.find(cidade_destino_gerenciador);

    if(it_origem != mapa_cidades.end() && it_destino != mapa_cidades.end()){
        Cidade* origem = const_cast<Cidade*>(&it_origem->second);
        Cidade* destino = const_cast<Cidade*>(&it_destino->second);

        std::pair<std::vector<Cidade*>, int> resultado = encontrarMelhorRota(origem, destino);
        std::cout << "\nDistância total da rota: " << resultado.second << std::endl;
        distancia = resultado.second; 
        if(resultado.second >= 0){
            imprimirRota(resultado.first, resultado.second);
            // usarDistanciaTotal(resultado.second); -> Output desnecessário mas talvez eu precise caso necessário
        } 
        else{
            std::cout << "Erro ao calcular a rota." << std::endl;
        }
    } 
    else{
        std::cout << "Origem ou destino não encontrados." << std::endl;
    }

    // Obtendo os dados do veículo para calcular a viagem final
    int velocidade_veiculo = mapa_transportes.at(transporte_gerenciador).getVelocidade();
    int frequencia_pausas_veiculo = mapa_transportes.at(transporte_gerenciador).getDistanciaEntreDescansos();
    int tempo_pausa_veiculo = mapa_transportes.at(transporte_gerenciador).getTempoDescanso();

    // Impressão dos dados da viagem 
    calculo_viagem(distancia, hora, velocidade_veiculo, frequencia_pausas_veiculo, tempo_pausa_veiculo);

    // Criando a viagem
    Transporte* transporte = const_cast<Transporte*>(&mapa_transportes.at(transporte_gerenciador));
    Cidade* origem = const_cast<Cidade*>(&mapa_cidades.at(cidade_origem_gerenciador));
    Cidade* destino = const_cast<Cidade*>(&mapa_cidades.at(cidade_destino_gerenciador));

    Viagem viagem(transporte, passageiros, origem, destino);
    Armazenar_viagens(viagem);
}


#endif
