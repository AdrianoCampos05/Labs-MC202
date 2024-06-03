#ifndef __HEAP_H__
#define __HEAP_H__

typedef struct
{
    int key;
    int id;
} Item;

struct Heap
{
    int len;
    int max_len;
    Item *items;
    int *pos;   //posição de cada id em items
};

typedef struct Heap *p_heap;

/*Cria um max heap binário vazio.
Guarda dados do tipo Item.
___________
Parâmetro:
---- int max_size: tamanhom máximo do heap
__________________
Retorna (p_heap):
---- ponteiro para o heap*/
p_heap new_heap(int max_size);


/*Cria um item que pode ser inserido em um heap.
___________
Parâmetro:
---- int id: código do item
---- int key: chave (prioridade) do item
_______________
Retorna (Item):
---- o item*/
Item new_item(int id, int key);


/*Insere um item em um heap.
____________
Parâmetros:
---- p_heap h: o heap
---- Item i: o item (com id e chave já definidos)*/
void insert(p_heap h, Item i);


/*Retira e devolve o item de maior prioridade do heap.
___________
Parâmetro:
---- p_heap h: o heap
_______________
Retorna (Item):
---- o item de maior prioridade*/
Item pop(p_heap h);


/*Adiciona um valor à chave de um item do heap.
____________
Parâmetros:
---- p_heap h: o heap
---- int id: o código do item
---- int value: o valor adicionado*/
void add_to_key(p_heap h, int id, int value);


/*Diz se um heap está vazio.
___________
Parâmetro:
---- p_heap h: o heap
_____________
Retorna (int):
---- 0: se há algum item
---- 1: se está vazio*/
int heap_empty(p_heap h);


/*Destrói um heap.
___________
Parâmetro:
---- p_heap h: o heap*/
void destroy_heap(p_heap h);


#endif //__HEAP_H__