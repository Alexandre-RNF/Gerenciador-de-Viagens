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
...Dados salvos em arquivo. Permitindo que continuem salvos entre sessões
..
### (1) - Cadastrar cidade
...Digitando o nome da cidade
### (2) - Cadastrar trajeto
...Digitando o nome da cidade de origem (Caso não exista, mensagem de erro)
...Digitando o nome da cidade destino (Caso não exista, mensagem de erro
...Digitando o tipo de trajeto('A' para aquático 'T' para terrestre) - (Caso não seja um tipo válido, mensagem de erro)
...Digitando o a distância em km entre essas duas cidades
### (3) - Cadastrar transporte
...Digitando o nome do transporte
...Digitando o tipo do transporte('A' para aquático 'T' para terrestre) - (Caso não seja um tipo válido, mensagem de erro)
...Digitando a capacidade de passageiros
...Digitando a velocidade em km/h
...Digitando a distância entre descansos em km
...Digitando o tempo de descanso em km/h
### (4) - Cadastrar passageiro
...Digitando o nome do passageiro
### (5) - Gestão de viagens
...Criação de viagem
...Escolha de cidade origem (Precisa existir)
...Escolha de cidade destino (Precisa existir)

### (6) - Relatórios
...

## Estrutura do Código 
![Mapa codigo](https://github.com/user-attachments/assets/0e662623-2203-4ee3-b27f-115eac09a090)








