# "Ubio"
### Sistema Controlador de viagens 
O objetivo deste projeto é aplicar os conceitos de programação orientada a objetos em C++ para desenvolver um sistema de controle de viagens. 

## Como compilar
- Ao baixar os arquivos, certifique-se que todos eles se encontram na mesma pasta.
- Abra o terminal do seu computador. Comumente nomeado como "Prompt de comando" (cmd).
- Por meio do terminal, acesse o diretório em que o código se encontra (Isso é feito a partir do comando: "cd 'nome da pasta'").
- Aberto o diretório, digite: "g++ -o 'nome_do_executável' main.cpp" para compilar. (Observação: o 'nome_do_executável' é fornecido por você no momento da digitação dessa linha).
- Feita a compilação. Digite: "./nome_do_executável".
- Diferentes terminais podem não reconhecer o comando, caso isso ocorra, digite: "nome_do_executável.exe".

## Instruções 
Inicializado o código, será aberto para o usuário um menu com as seguintes opções: 

- CADASTROS:
  - "(1) - Cadastrar cidade"
  - "(2) - Cadastrar trajeto"
  - "(3) - Cadastrar transporte"
  - "(4) - Cadastrar passageiro"

- VIAGENS:
  - "(5) - Gestão de viagens"

- RELATÓRIOS:
  - "(6) - Relatórios"

Para acessar uma determinada opção do menu, digite o número correspondente a ela.
Por exemplo: Para acessar a função de cadastrar astronauta. Digite "1".
Quando uma opção do menu for finalizada, o programa automáticamente retornará para o menu, abrindo a oportunidade para que você digite outra opção.

## Funcionalidades
- Dados salvos em arquivo. Permitindo que continuem salvos entre sessões
### (1) - Cadastrar cidade
- Digitando o nome da cidade
### (2) - Cadastrar trajeto
- Digitando o nome da cidade de origem (Caso não exista, mensagem de erro)
- Digitando o nome da cidade destino (Caso não exista, mensagem de erro
- Digitando o tipo de trajeto('A' para aquático 'T' para terrestre) - (Caso não seja um tipo válido, mensagem de erro)
- Digitando o a distância em km entre essas duas cidades
### (3) - Cadastrar transporte
- Digitando o nome do transporte
- Digitando o tipo do transporte('A' para aquático 'T' para terrestre) - (Caso não seja um tipo válido, mensagem de erro)
- Digitando a capacidade de passageiros
- Digitando a velocidade em km/h
- Digitando a distância entre descansos em km
- Digitando o tempo de descanso em km/h
### (4) - Cadastrar passageiro
- Digitando o nome do passageiro
### (5) - Gestão de viagens
- Criação de viagem
- Escolha de cidade origem (Precisa existir)
- Escolha de cidade destino (Precisa existir)
- Escolha de transporte (Precisa existir)
- Atribuição de passageiros para o transporte (Limite para a capacidade máxima do transporte escolhido)
- Digitar a hora de partida da viagem

- Por meio da cidade de origem e cidade destino, o sistema calculará o melhor trajeto a ser seguido, exibindo as cidades da rota e a distância a ser percorrida
```diff
- Infelizmente o programa não diferencia entre rotas terrestres e aquáticas
```
- A partir dos dados fornecidos, o programa irá exibir os dados á respeito da viagem, tais como: (Distância percorrida, número de paradas, duração da viagem e horário de chegada)
- Ao fim, a viagem é criada e armazenada no sistema
```diff
- O programa não altera a cidade atual dos passageiros e transportes na finalização de uma viagem
- Por mais que o tempo final da viagem seja exibido, o programa não armazena as horas em trânsito da viagem
- Não existe estado em trânsito em que o programa avança as horas automaticamente ou manualmente. Na criação de uma viagem os dados a respeito dela são exibidos imediatamente.
```
### (6) - Relatórios
Dependendo da opção escolhida pelo usuário, quatro tipos de informação diferentes podem ser exibidas
- Relatar cada pessoa
```diff
- O programa não exibe origem-destino-transporte. Além disso, devido ao erro citado anteriormente de não alterar a cidade dos passageiros ele sempre exibe como disponível (estado padrão de um passageiro)
```
- Relatar cada transporte
- Relata todas as viagens
```diff
- Novamente, o erro citado anteriormente. Por mais que o tempo final da viagem seja exibido, o programa não armazena as horas em trânsito da viagem e exibe como 0 
```
- Relata as cidades mais visitadas
## Estrutura do Código 
![Mapa codigo](https://github.com/user-attachments/assets/0e662623-2203-4ee3-b27f-115eac09a090)

- bibliotecas.h: Inclusão de todas as bibliotecas utilizadas no código
- classes.h: Inclusão de todas as classes utilizadas no código

- main.cpp: Corpo principal do código. É onde ocorre a navegação pelo menu e o cadastro dos dados principais (passageiros, transportes, trajetos e cidades). Além disso, ocorre a armazenação e carregamento dos dados
- armazenar.h: Conjunto de funções responsável por armazenar os dados cadastrados
- carregar.h: Conjunto de funções responsável por carregar os dados cadastrados

- relatorios.h: É onde ocorre a navegação de um segundo mini menu e a exibição de diversos dados envolvendo as viagens, transportes e passageiros

- gerenciador.h: Criação e armazenamento da viagem a partir dos dados fornecidos pelo usuário. Exibição do melhor trajeto e rota a ser seguida (listando cada cidade da rota). Exibição dos dados envolvendo a viagem (envolvendo horas e distâncias)
- distra.h: Conjunto de funções que busca implementar o algoritmo de Dijkstra para o cálculo da melhora rota entre os diferentes trajetos.
- matematicas.h: Função que calcula distância percorrida, número de paradas, duração da viagem e horário de chegada a partir da distância, hora de início da viagem e os dados envolvendo o transporte









