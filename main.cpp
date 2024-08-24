//Classes e bibliotecas
#include "classes.h"
#include "bibliotecas.h"

// Funcões para funcionalidade do programa
#include "armazenar.h" // -> Conjunto de funções que armazena os dados do código em um arquivo
#include "carregar.h" // -> Conjunto de funções que carrega os dados armazenados no programa em sua inicialização
#include "gerenciador.h" // -> Função que vai trabalhar com o gerenciador de viagens. Complexo demais então estou fazendo em um arquivo separado para não me perder 
#include "relatorios.h" // - Funcionalidade de relatórrios

// Menu principal
void Menu(){
std::cout << "CADASTROS ======================================================" << std::endl;
std::cout << "(1) - Cadastrar cidade" << std::endl;
std::cout << "(2) - Cadastrar trajeto" << std::endl;
std::cout << "(3) - Cadastrar transporte" << std::endl; 
std::cout << "(4) - Cadastrar passageiro" << std::endl;
std::cout << "\nVIAGENS ========================================================" << std::endl; 
std::cout <<"(5) - Gestão de viagens" << std::endl; //  Gestão de viagens, consultas e relatórios
std::cout << "(6) - Relatórios" << std::endl;
std::cout << "\nSAIR DO PROGRAMA ===============================================" << std::endl;
std::cout << "(7) - Sair" << std::endl;
}

// Um menu próprio para a parte de relatórios
void Menu_relatorios(){
std::cout << "(1) - Relatar passageiros" << std::endl;
std::cout << "(2) - Relatar transportes" << std::endl;
std::cout << "(3) - Relatar viagens em andamento" << std::endl;
std::cout << "(4) - Relatar cidades mais visitadas" << std::endl;   
}

int main(){
    // Estruturas de armazenamento de dados                         // Mapas - Onde eles ficam registrados           
    std::unordered_map<std::string, Cidade> mapa_cidades;           // Cidades
    std::vector <Trajeto> mapa_trajetos;                            // Trajetos
    std::unordered_map<std::string, Transporte> mapa_transportes;   // Transportes
    std::unordered_map<std::string, Passageiro> mapa_passageiros;   // Passageiros
    std::vector <Viagem> mapa_viagens;                              // Viagens   

    // Variavéis que eu vou usar (deixar dentro do switch case estava dando erro)
    // Cadastrar cidade
    std::string nome_cidade;

    // Cadastrar trajeto
    std::string cidade_origem;
    std::string cidade_destino;
    char tipo; 
    int distancia;

    // Cadastrar transporte
    std::string nome_transporte;
    char tipo_transporte;
    int capacidade; 
    int velocidade; 
    int distancia_descansos; 
    int tempo_descanso;

    // Cadastrar passageiro
    std::string nome_passageiro;

    // Relatórios
    int input_relatorios;

    // Iteradores
    int i;   

    // Carregar os dados salvos em outras sessões
    Carregar_cidades(mapa_cidades);
    Carregar_trajetos(mapa_trajetos);
    Carregar_transportes(mapa_transportes, mapa_cidades);
    Carregar_passageiros(mapa_passageiros, mapa_cidades);
    Carregar_viagens(mapa_cidades, mapa_transportes, mapa_viagens);   

    // Mensagem de bem-vindo e inicalização
    system("cls");
    std::cout << "=== Bem vindo ao Ubio: Gerenciador de Viagens ===" << std::endl;
    std::cout << "Digite 'iniciar' para inicializar o programa" << std::endl;

    // O programa só vai iniciar se o usuário digitar "iniciar" 
    while(true){
        std::string play; 
        std::cin >> play;
        if(play == "iniciar"){
            break;
        } 
    }
    system("cls");

    // Menu
    std::cout << "Selecione a funcionalidade digitando o número entre parênteses" << std::endl;
    while(true){
        std::cout << " " << std::endl; 
        Menu(); 

        // Input do usuário e acesso de menu
        int input;

        std::cin >> input;
        switch(input){

        // ==========================================================================================================================================
        // Cadastrar cidade
        case 1:{
            system("cls"); 
            std::cout << "Nome da cidade: "; 
            std::cin >> nome_cidade;

            // Checa se o nome já foi registrado antes
            if(mapa_cidades.find(nome_cidade) != mapa_cidades.end()){
                std::cout << "Essa cidade já está registrada" << std::endl;                   // Se sim. Erro
                break; 
            } 
            else{
                Cidade nova_cidade(nome_cidade);
                mapa_cidades.insert({nome_cidade, nova_cidade});       
                std::cout << "Cidade cadastrada com sucesso!!!" << std::endl;                // Se não. Cadastra
                Armazenar_cidades(mapa_cidades);
            }
            break;
        } 


        // ==========================================================================================================================================
        // Cadastrar trajeto
        case 2:{
            system("cls"); 
            // Input - Cidade de Origem
            std::cout << "Digite o nome da cidade de origem: ";
            std::cin >> cidade_origem;

            // Checa para ver se a Origem existe
            if(mapa_cidades.find(cidade_origem) != mapa_cidades.end()){
                std::cout << "Cidade de origem registrada" << std::endl; 
            }
            else{
                std::cout << "A cidade não existe" << std::endl; 
                break; 
            }

            // Input - Cidade Destino
            std::cout << "\nDigite o nome da cidade destino: ";
            std::cin >> cidade_destino; 

            // Checa para ver se o Destino existe
            if(mapa_cidades.find(cidade_destino) != mapa_cidades.end()){
                std::cout << "Cidade destino registrada" << std::endl; 
            }
            else{
                std::cout << "A cidade não existe" << std::endl; 
                break; 
            }

            // Input - Tipo de trajeto (Aquático ou terrestre)
            std::cout << "\nO trajeto é aquático ou terrestre?" << std::endl; 
            std::cout << "(A/T): "; 
            std::cin >> tipo; //[...]


            // Input - Distancia entre cidades
            std::cout << "\nQual é a distância, em quilômetros entre essas duas cidades?: "; 
            std::cin >> distancia;  //[...]

            // Todos os dados coletados e validados, agora iremos realizar o cadastro do trajeto
            Trajeto novo_trajeto(&mapa_cidades[cidade_origem], &mapa_cidades[cidade_destino], tipo, distancia);
            mapa_trajetos.push_back(novo_trajeto);        
            std::cout << "Trajeto registrado com sucesso!!!" << std::endl;

            Armazenar_trajetos(mapa_trajetos); 
            break;
        } 


        // ==========================================================================================================================================
        // Cadastrar veículo
        case 3:{
            system("cls"); 
            std::cout << "Insira o nome do veículo: ";
            std::cin >> nome_transporte;
            if(mapa_transportes.find(nome_transporte) != mapa_transportes.end()){
                std::cout << "Esse transporte já está registrado!" <<std::endl;
                break; 
            }
    

            std::cout << "\nInsira o tipo do veículo (aquático ou terrestre)" << std::endl; 
            std::cout << "(A/T): "; 
            std::cin >> tipo_transporte;
            // If não usável. Mensagem de erro (a ser implementado)

            std::cout << "\nInforme a capacidade de passageiros que o veículo permite: "; 
            std::cin >> capacidade;
            // If não é número ou número inválido (valor negativo ou 0) -> Mensagem de erro (a ser implementado)

            std::cout << "\nInforme a velocidade do transporte em km/h (digite apenas o número): ";
            std::cin >> velocidade;

            std::cout << "\nInforme quantos km o transporte percorre antes de descansar: "; 
            std::cin >> distancia_descansos;

            std::cout << "\nInforme quantas horas duram o descanso do veículo: "; 
            std::cin >> tempo_descanso;

            Transporte novo_transporte(nome_transporte, tipo_transporte, capacidade, velocidade, distancia_descansos, tempo_descanso); 
            mapa_transportes.insert({nome_transporte, novo_transporte});
            std::cout << "Transporte armazenado com sucesso!!!" << std::endl;
                    
            Armazenar_transportes(mapa_transportes); 
            break; 
        }

        // =========================================================================================================================================
        // Cadastrar passageiro
        case 4:{
            system("cls");
            // Input 
            std::cout << "Informe o nome do passageiro: ";
            std::cin >> nome_passageiro;

            // Checa para ver se o passageiro já existe
            if(mapa_passageiros.find(nome_passageiro) != mapa_passageiros.end()){           // Se sim. Erro
                std::cout << "Passageiro já registrado" << std::endl;                   
                break; 
            } 
            else{
                Passageiro novo_passageiro(nome_passageiro);
                mapa_passageiros.insert({nome_passageiro, novo_passageiro});       
                std::cout << "Passageiro cadastrado com sucesso!!!" << std::endl;           // Se não. Cadastra
                Armazenar_passageiro(mapa_passageiros);
            }
            break;
        }

        // =========================================================================================================================================
        // Modo gerenciador: Cadastrar viagem
        case 5:{
            system("cls");
            Gerenciador(mapa_cidades, mapa_trajetos, mapa_transportes, mapa_passageiros); 
            break;  
        }

        // Vai abrir um segundo menu com mais opções
        case 6:{
            system("cls");
            Menu_relatorios();
            std::cin >> input_relatorios;
            Relatorios(input_relatorios, mapa_cidades, mapa_trajetos, mapa_transportes, mapa_passageiros, mapa_viagens);  
            break;  
        }

        // Limpa a tela e mensagem de despedida
        case 7:{
            system("cls");
            std::cout << "Obrigado por utilizar o Ubio! Fechando programa..." << std::endl;
            return 0;
        }

        // Caso o usuário digite uma opção inválida
        default:
            system("cls");
            std::cout << "Opção inválida\n" << std::endl;
            break;
        }
    }  
}


