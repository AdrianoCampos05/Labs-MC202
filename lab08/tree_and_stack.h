#ifndef __TREEANDSTACK_H__
#define __TREEANDSTACK_H__

typedef struct _bin_node *p_tree;
typedef struct _bin_node *p_stack;


/* Nó que guarda um char e ponteiros para dois outros nós.

Para árvores:
    ponteiros chamam p_tree
Para pilhas:
    ponteiros chamam p_stack

Os dois "tipos" de ponteiro são idênticos;
os nomes apenas esclarecem como a estrutura está sendo utilizada.
*/
struct _bin_node
{
    char val;
    struct _bin_node *left;
    struct _bin_node *right;
};



//// FUNÇÕES DE ÁRVORE ////

/*Cria uma nova árvore binária com filhos NULL.
___________________________________
Parâmetro:
---- char val: o valor salvo na raiz
____________________________
Retorna (p_tree):
---- ponteiro para a árvore*/
p_tree new_tree(char val);


/*Libera a memória ocupada por uma árvore.
__________________________________
Parâmetros:
---- p_tree root: a raiz da árvore*/
void destroy_tree(p_tree root);


/*Adiciona uma sub-árvore à esquerda da raiz.
________________________________________
Parâmetros:
---- p_tree root: a raiz
---- p_tree left: a sub-árvore esquerda
_________________________
Retorna (p_tree):
---- ponteiro para a raiz*/
p_tree left_attach(p_tree root, p_tree left);


/*Adiciona uma sub-árvore à direita raiz.
_______________________________________
Parâmetros:
---- p_tree root: a raiz
---- p_tree right: a sub-árvore direita
_________________________
Retorna (p_tree):
---- ponteiro para a raiz*/
p_tree right_attach(p_tree root, p_tree right);


/*Conta o número de nós não NULL de uma árvore.
__________________________________
Parâmetro:
---- p_tree root: a raiz da árvore
_________________________
Retorna (int):
---- o número de nós*/
int count_nodes(p_tree root);



//// FUNÇÕES DE PILHA ////



/*Cria uma nova pilha vazia.
____________________________
Retorna (p_tree):
---- ponteiro para a pilha*/
p_stack new_stack();


/*Insere um valor em uma pilha.
________________________________
Parâmetros:
---- p_stack stack: a pilha
---- char value: o valor inserido*/
void push(p_stack stack, char value);


/*Remove o elemento no topo da pilha.
____________________________
Parâmetro:
---- p_stack stack: a pilha
________________________________
Retorna (char):
---- o valor removido
---- '\0' caso a pilha esteja vazia*/
char pop(p_stack stack);


/*Libera a memória ocupada por uma pilha
NÃO usar em árvores binárias; vaza memória
____________________________
Parâmetro:
---- p_stack stack: a pilha*/
void destroy_stack(p_stack stack);

#endif