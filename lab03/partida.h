#ifndef PARTIDA_H
#define PARTIDA_H
#include "circuito.h"

typedef struct
{
    float cost;
    int id;
    int players;
    int no_of_circs;
    int equipment;
    circuito *circs;
} partida;

/*Cria e retorna uma nova partida com código id*/
partida new_game(int id);

/*Lê um inteiro no terminal.
Registra o inteiro como número de circuitos na partida*/
void scan_no_of_circs(partida *game);

/*Lê um inteiro no terminal.
Registra o inteiro como número de jogadores na partida*/
void scan_players(partida *game);

/*Lê um inteiro no terminal.
Registra o inteiro como número de equipamentos alugados na partida*/
void scan_equipment(partida *game);

/*Lê uma sequência de inteiros no terminal
Para cada circuito, sendo n o número de jogadores, devem ser fornecidos:
----um código de identificação
----n inteiros correspondentes ao número de jogadas de cada jogador
Informações de um mesmo circuito devem ser fornecidas em sequência.
Tanto espaços quando quebras de linha podem separar os inteiros.*/
void scan_circuits(partida *game);

/*Calcula e atribui o valor do aluguel da partida
Só deve ser chamada depois das funções scan_player e scan_equipment*/
void update_cost(partida *game);

/*Retorna o código do circuito com o maior total de jogadas*/
int hardest_circ(partida game);

/*Devolve o total de jogadas do player-ésimo jogador na partida.
O primeiro jogador é o jogador 0.*/
int player_total(partida game, int player);

/*Imprime o número de jogadores, de circuitos e de equipamentos*/
void print_pce(partida game);

/*Imprime o custo do aluguel da partida.
Só deve ser chamada depois da função update_cost.*/
void print_cost(partida game);

/*Imprime qual foi o circuito com maior total de jogadas na partida*/
void print_hardest_circ(partida game);

/*Imprime o total de jogadas de cada jogador na partida*/
void print_player_totals(partida game);

/*Imprime todas as informações da partida na ordem:
----Código da partida
----Número de jogadores
----Número de circuitos
----Números de equipamentos
----Valor do aluguel
----Número de jogadas por jogador
----Circuito mais difícil*/
void print_summary(partida game);

/*Libera o vetor game->circs.
A memória alocada por cada circuito também é liberada.
Só deve ser chamada se a partida não for mais ser acessada.*/
void delete_game(partida *game);

#endif