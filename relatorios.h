#ifndef RELATORIOS_H
#define RELATORIOS_H

#include "bibliotecas.h"
#include "classes.h"

// Também vou precisar passar a lista de viagens como parâmetro [EM CONSTRUÇÃO]
void Relatorios(int input,
                const std::unordered_map<std::string, Cidade>& mapa_cidades, 
                const std::vector<Trajeto>& mapa_trajetos, 
                const std::unordered_map<std::string, Transporte>& mapa_transportes, 
                const std::unordered_map<std::string, Passageiro>& mapa_passageiros,
                const std::vector<Viagem>& mapa_viagens)
{
    switch(input){
        case 1:{
            // Relatar onde estão cada pessoa (cidade ou em trânsito, informando origem-destino-transporte)
            std::cout << "Relatando localização das pessoas:" << std::endl;
            for(const auto& pair : mapa_passageiros){
                const Passageiro& passageiro = pair.second;
                std::cout << "Nome do passageiro: " << passageiro.getNome() << " ||| ";
                if(passageiro.getLocalAtual() != nullptr){
                    std::cout << "Cidade atual: " << passageiro.getLocalAtual()->getNome() << std::endl;
                } 
                else{
                    std::cout << "Cidade atual: Indefinida" << std::endl;
                }
            }
            break;
        }

        case 2:{
            // Relatar transportes (se está em cidade ou em trânsito)
            std::cout << "Relatando transportes:" << std::endl;
            for(const auto& pair : mapa_transportes){
                const Transporte& transporte = pair.second;
                std::cout << "Nome do transporte: " << transporte.getNome() << " ||| ";
                if(transporte.getLocalAtual() != nullptr){
                    std::cout << "Cidade atual: " << transporte.getLocalAtual()->getNome() << std::endl; 
                }
                else{
                    std::cout << "Cidade atual: Indefinida" << std::endl;
                }
            }
            break;
        }

        case 3: {
            std::cout << "Relatando todas as viagens:" << std::endl;

            for(const Viagem& viagem : mapa_viagens) {
                if (viagem.getTransporte() && viagem.getOrigem() && viagem.getDestino()) {
                    std::cout << "Transporte: " << viagem.getTransporte()->getNome() << std::endl;
                    std::cout << "Origem: " << viagem.getOrigem()->getNome() << std::endl;
                    std::cout << "Destino: " << viagem.getDestino()->getNome() << std::endl;
                    std::cout << "Horas em trânsito: " << viagem.getHorasEmTransito() << std::endl;
                    std::cout << "Status da viagem: " << (viagem.isEmAndamento() ? "Em andamento" : "Concluída") << std::endl;
                    std::cout << "Passageiros:" << std::endl;

                    for(const Passageiro* passageiro : viagem.getPassageiros()) {
                        if (passageiro) {
                            std::cout << " - " << passageiro->getNome() << std::endl;
                        } else {
                            std::cout << " - Passageiro com dados inválidos." << std::endl;
                        }
                    }

                    std::cout << "---------------------------------------------" << std::endl;
                } else {
                    std::cout << "Dados da viagem incompletos." << std::endl;
                }
            }

            break;
}





        case 4:{
            std::cout << "Relatando cidades mais visitadas:" << std::endl;
            std::unordered_map<std::string, int> visita_count;
            
            // Contar visitas às cidades
            for(const Viagem& viagem : mapa_viagens){
                if (viagem.getOrigem() && viagem.getDestino()){
                    std::string origem = viagem.getOrigem()->getNome();
                    std::string destino = viagem.getDestino()->getNome();
                    
                    visita_count[origem]++;
                    visita_count[destino]++;
                }
            }

            // Ordenar e relatar as cidades mais visitadas
            if(visita_count.empty()) {
                std::cout << "Nenhuma cidade foi visitada." << std::endl;
            } 
            else{
                std::vector<std::pair<std::string, int>> cidades_visitadas(visita_count.begin(), visita_count.end());
                std::sort(cidades_visitadas.begin(), cidades_visitadas.end(), 
                    [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
                        return a.second > b.second; 
                    });

                for(const auto& cidade : cidades_visitadas){
                    std::cout << "Cidade: " << cidade.first << " - Visitas: " << cidade.second << std::endl;
                }
            }
            break;
        }       


        default:{
            std::cout << "Opção inválida" << std::endl;
            break; 
        }
    }
}


#endif
