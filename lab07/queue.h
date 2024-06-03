#ifndef QUEUE_H
#define QUEUE_H

#include "part.h"

typedef struct _queue *p_queue;

struct _queue
{
    p_part *parts;
    int start;
    int end;
    int len;
    int max_len;
};


/*Cria uma nova fila.
__________________________________________________________
Parâmetro:
---- int max_len: o máximo de peças que cabem na fila
_______________________________________
Retorna (p_queue):
---- um ponteiro para a fila*/
p_queue new_queue(int max_len);


/*Checa se a fila está vazia.
_____________________________________
Parâmetro:
---- p_queue q: ponteiro para a fila
__________________________________
Retorna (int):
---- 0 se a fila tem alguma peça
---- 1 se a fila está vazia*/
int queue_empty(p_queue q);


/*Checa se a fila está cheia.
_____________________________________
Parâmetro:
---- p_queue q: ponteiro para a fila
_________________________________
Retorna (int):
---- 0 se a fila tem espaço livre
---- 1 se a fila está cheia*/
int queue_full(p_queue q);


/*Insere uma peça no fim da fila.
________________________________________
Parâmetros:
---- p_queue q: ponteiro para a fila
---- p_part part: ponteiro para a peça
_________________________________________
Retorna (int):
---- 0 se a peça é inserida com sucesso
---- 1 se a fila está cheia*/
int enqueue(p_queue q, p_part part);


/*Retira a peça no começo da fila.
_____________________________________
Parâmetros:
---- p_queue q: ponteiro para a fila
________________________________________
Retorna (p_part):
---- um ponteiro para a peça retirada
---- NULL se a fila está vazia*/
p_part dequeue(p_queue q);


/*Libera a memória ocupada por uma fila.
NÃO libera possíveis peças restantes.
_____________________________________
Parâmetro:
---- p_queue q: ponteiro para a fila*/
void destroy_queue(p_queue q);

#endif