#ifndef STACK_H
#define STACK_H

#include "part.h"

typedef struct _stack_base *p_stack;
typedef struct _stack_node *p_node;

struct _stack_base
{
    int max_size;
    int used_size;
    p_node next;
};

struct _stack_node
{
    p_part part;
    p_node next;
};


/*Cria uma nova pilha.
_____________________________________________________________
Parâmetro:
---- int max_size: o máximo de peças que cabem na pilha
_______________________________________
Retorna (p_stack):
---- um ponteiro para a fila*/
p_stack new_stack(int stack_size);


/*Checa se a pilha está vazia.
_______________________________________
Parâmetro:
---- p_stack s: ponteiro para a pilha
____________________________________
Retorna (int):
---- 0 se a pilha tem alguma peça
---- 1 se a pilha está vazia*/
int stack_empty(p_stack s);


/*Checa se a pilhas está cheia.
__________________________________________
Parâmetro:
---- p_stack s: ponteiro para a pilha
___________________________________
Retorna (int):
---- 0 se a pilha tem espaço livre
---- 1 se a pilha está cheia*/
int stack_full(p_stack s);


/*Insere uma peça no topo da pilha.
__________________________________________
Parâmetros:
---- p_stack s: ponteiro para a pilha
---- p_part part: ponteiro para a peça
_________________________________________
Retorna (int):
---- 0 se a peça é inserida com sucesso
---- 1 se a pilha está cheia*/
int push(p_stack s, p_part part);


/*Retira a peça no topo da pilha.
__________________________________________
Parâmetro:
---- p_stack s: ponteiro para a pilha
________________________________________
Retorna (p_part):
---- um ponteiro para a peça retirada
---- NULL se a pilha está vazia*/
p_part pop(p_stack s);


/*Libera a memória ocupada por uma pilha.
NÃO libera possíveis peças restantes.
__________________________________________
Parâmetro:
---- p_stack s: ponteiro para a pilha*/
void destroy_stack(p_stack s);


#endif