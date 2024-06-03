#ifndef WORKER_H
#define WORKER_H

#include "part.h"

enum Status{BUSY, FREE};

typedef struct _worker *p_worker;

struct _worker
{
    char type;
    enum Status status;
    int time_spent;
    p_part part;
};


/*Cria um novo trabalhador.
____________________________________
Parâmetro:
---- char type: tipo de trabalhador 
's' - sorter (classificador)
'p' - packer (embalador)
______________________________________
Retorna (p_worker):
---- um ponteiro para o trabalhador*/
p_worker new_worker(char type);


/*Transfere uma peça para o trabalhador
Se a peça não for NULL, muda seu status para BUSY.
__________________________________________
Parâmetros:
---- p_worker w: ponteiro para o trabalhador
---- p_part part: ponteiro para a peça
________________________________________
Retorna (int):
---- 0 se a peça recebida é NULL
---- 1 se a peça é pega com sucesso*/
int grab(p_worker w, p_part part);


/*Solta a peça segurada pelo trabalhador.
Muda seu status para FREE.
_______________________________________________
Parâmetros:
---- p_worker w: ponteiro para o trabalhador
_______________________________________
Retorna (p_part):
---- a peça segurada (pode ser NULL)*/
p_part drop(p_worker w);


/*Checa se o trabalhador concluiu o trabalho na peça atual.
_______________________________________________
Parâmetros:
---- p_worker w: ponteiro para o trabalhador
________________________________________
Retorna (int):
---- 0 se o trabalhador já está livre ou ainda não acabou
---- 1 se o trabalho já foi termindado
---- -1 se o tipo do trabalhador for inválido*/
int is_done(p_worker w);


/*Checa se o trabalhador está livre.
_______________________________________________
Parâmetro:
---- p_worker w: ponteiro para o trabalhador
________________________
Retorna (int):
---- 0 se está ocupado
---- 1 se está livre*/
int is_free(p_worker w);


/*Faz um minuto passar no relógio do trabalhador.
_______________________________________________
Parâmetro:
---- p_worker w: ponteiro para o trabalhador*/
void tick(p_worker w);


/*Libera a memória ocupada pelo trabalhador.
NÃO libera a peça segurada por ele.
_______________________________________________
Parâmetro:
---- p_worker w: ponteiro para o trabalhador*/
void destroy_worker(p_worker w);

#endif