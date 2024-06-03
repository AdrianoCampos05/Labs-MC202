#ifndef LIST_H
#define LIST_H

typedef struct node *p_node;

struct node
{
    char *title;
    p_node next;
};


/*Cria uma lista vazia.
____________________________
Retorna:
p_node: um ponteiro NULL*/
p_node new_list();


/*Cria um novo nó.
_________________________________________
Parâmetro:
----char *title: o título guardado no nó
_____________________________________
Retorna:
----p_node: um ponteiro para o nó*/
p_node new_node(char *title);


/*Insere um título no ínicio de uma lista.
______________________________________
Parâmetros:
----p_node list: ponteiro para a lista
----char *title: o título inserido
_____________________________________________
Retorna:
----p_node: ponteiro para a lista atualizada*/
p_node insert_first(p_node list, char *title);


/*Insere um título no final de uma lista.
______________________________________
Parâmetros:
----p_node list: ponteiro para a lista
----char *title: o título inserido
_____________________________________________
Retorna:
----p_node: ponteiro para a lista atualizada*/
p_node insert_last(p_node list, char *title);


/*Insere um título após um outro título na lista.
Se o título não for encontrado, insere no começo da lista
______________________________________
Parâmetros:
----p_node list: ponteiro para a lista
----char *title: o título inserido
----char *prev_title: o título após o
qual o novo título deve ser inserido
_____________________________________________
Retorna:
----p_node: ponteiro para a lista atualizada*/
p_node insert_after(p_node list, char *title, char *prev_title);


/*Remove um título de uma lista.
______________________________________
Parâmetros:
----p_node list: ponteiro para a lista
----char *title: o título removido
_____________________________________________
Retorna:
----p_node: ponteiro para a lista atualizada*/
p_node remove_title(p_node list, char *title);


/*Libera a memória ocupada por uma lista.
A memória das strings também é liberada.
______________________________________
Parâmetro:
----p_node list: ponteiro para a lista*/
void destroy_list(p_node);

#endif