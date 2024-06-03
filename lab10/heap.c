#include <stdlib.h>
#include "heap.h"
#include <stdio.h>


p_heap new_heap(int max_len)
{
    p_heap h = malloc(sizeof(struct Heap));
    h->items = malloc(max_len * sizeof(Item));
    h->pos = malloc(max_len * sizeof(int));
    h->len = 0;
    h->max_len = max_len;
    return h;
}


Item new_item(int id, int key)
{
    Item i;
    i.id = id;
    i.key = key;
    return i;
}


/*Troca dois itens*/
void _item_swap(Item *a, Item *b)
{
    Item temp = *a;
    *a = *b;
    *b = temp;
}

/*Troca dois inteiros*/
void _int_swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}


/*Diz se a prioridade de a é maior que a de b*/
int _item_gt(Item a, Item b)
{
    return (a.key > b.key || (a.key == b.key && a.id < b.id));
}


/*Sobe o item na posição k*/
void _move_up(p_heap h, int k)
{
    if (k <= 0) return;

    int parent = (k + 1)/2 - 1;
    if (_item_gt(h->items[k], h->items[parent]))
    {
        _item_swap(h->items + k, h->items + parent);
        _int_swap(h->pos + h->items[k].id, 
            h->pos + h->items[parent].id);
        _move_up(h, parent);
    }
}


/*Desce o item na posição k*/
void _move_down(p_heap h, int k)
{
    int child = 2*k + 1;
    if (child >= h->len)
        return;

    if (child + 1 < h->len && _item_gt(h->items[child + 1], h->items[child]))
    {
        child++;  // Filho direito existe e é maior
    }

    if (_item_gt(h->items[child], h->items[k]))
    {
        _item_swap(h->items + k, h->items + child);
        _int_swap(h->pos + h->items[k].id, 
            h->pos + h->items[child].id);
        _move_down(h, child);
    }
}


void insert(p_heap h, Item i)
{
    if (h->len >= h->max_len) return;
    h->items[h->len] = i;
    h->pos[i.id] = h->len;
    _move_up(h, h->len); 
    h->len++;
}


Item pop(p_heap h)
{
    Item out = h->items[0];
    _item_swap(h->items, h->items + h->len - 1);
    _int_swap(h->pos + h->items[0].id, h->pos + h->items[h->len - 1].id);
    h->len--;
    _move_down(h, 0);
    return out;
}


void add_to_key(p_heap h, int id, int value)
{
    h->items[h->pos[id]].key += value;
    if (value > 0)
        _move_up(h, h->pos[id]);
    else
        _move_down(h, h->pos[id]);
}


int heap_empty(p_heap h)
{
    return (h->len == 0);
}


void destroy_heap(p_heap h)
{
    free(h->items);
    free(h->pos);
    free(h);
}
