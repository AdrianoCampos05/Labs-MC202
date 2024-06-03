#include <stdlib.h>
#include "stack.h"

p_stack new_stack(int max_size)
{
    p_stack s = malloc(sizeof(struct _stack_base));
    s->next = NULL;
    s->max_size = max_size;
    s->used_size = 0;
    return s;
}


int stack_empty(p_stack s)
{
    return (s->next == NULL);
}


int stack_full(p_stack s)
{
    return (s->used_size >= s->max_size);
}


int push(p_stack s, p_part part)
{
    if (stack_full(s))
        return 1;
    p_node node = malloc(sizeof(struct _stack_node));
    node->part = part;
    node->next = s->next;
    s->next = node;
    s->used_size++;
    return 0;
}


p_part pop(p_stack s)
{
    p_part part;
    p_node temp_node;
    if (stack_empty(s))
        return NULL;
    temp_node = s->next;
    s->next = temp_node->next;
    part = temp_node->part;
    free(temp_node);
    s->used_size--;
    return part;
}


/*Destri recursivamente uma sequência de nós.
Não destrói possíveis partes restantes.*/
void _destroy_nodes(p_node node)
{
    if (node == NULL)
        return;
    _destroy_nodes(node->next);
    free(node);
}


void destroy_stack(p_stack s)
{
    _destroy_nodes(s->next);
    free(s);
}
