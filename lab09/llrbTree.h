#ifndef LLRBTREE_H
#define LLRBTREE_H

#ifndef MAX_NAME_LEN
#define MAX_NAME_LEN 200
#endif

typedef struct _rb_node *p_node;

enum color{BLACK, RED};

struct _rb_node
{
    char *name;
    char type;
    enum color color;
    p_node left, right;
};


/*"Cria" uma árvore vazia.
____________________
Retorna (p_node):
---- NULL*/
p_node new_tree(void);


/*Insere uma variável em uma árvore.
____________
Parâmetros:
---- p_node root: a raiz da árvore
---- char *name: o nome da variável
---- char type: primeira letra do tipo (i, d ou c)
______________
Retorna (p_node):
---- ponteiro para a raiz da árvore modificada*/
p_node insert(p_node root, char *name, char type);


/*Busca uma variável e devolve seu tipo
____________
Parâmetros:
---- p_node tree: a árvore
---- char *name: nome da variável
________________
Retorna (char):
---- 'i': tipo int
---- 'd': tipo double
---- 'c': tipo char
---- '\0': variável não encontrada*/
char search(p_node tree, char *name);


/*Destrói uma árvore.
Libera os nós e as string de nome.
____________
Parâmetro:
---- p_node tree: a árvore*/
void destroy(p_node tree);

#endif