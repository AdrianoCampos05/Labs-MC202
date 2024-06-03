#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"


p_node new_list()
{
    return NULL;
}


p_node new_node(char *title)
{
    p_node node = malloc(sizeof(struct node));
    if (!node)
        exit(-1);
    node->title = title;
    return node;
}


p_node insert_first(p_node list, char *title)
{
    p_node node = new_node(title);
    node->next = list;
    return node;
}


p_node insert_last(p_node list, char *title)
{
    p_node node = new_node(title); 
    p_node current = list;
    node->next = NULL;
    if (!list)
        return node;
    while (current->next)
        current = current->next;
    current->next = node;
    return list;
}


p_node insert_after(p_node list, char *title, char *prev_title)
{
    p_node node = new_node(title); 
    p_node current = list;
    if (!list)
        return node;
    while (strcmp(current->title, prev_title))
    {
        current = current->next;
        if (!current)
        {
            node->title = title;
            node->next = list;
            return node;
        }
    }
    node->next = current->next;
    current->next = node;
    return list;
}


p_node remove_title(p_node list, char *title)
{
    p_node prev, current = list;
    if (!list)
        return list;

    if (!strcmp(list->title, title))
    {
        current = list->next;
        free(list->title);
        free(list);
        return current;
    }
    
    while (strcmp(current->title, title))
    {
        prev = current;
        current = current->next;
        if (!current)
            return list;
    }
    
    prev->next = current->next;
    free(current->title);
    free(current);
    return list;
}


void destroy_list(p_node list)
{
    p_node next;
    while (list)
    {
        next = list->next;
        free(list->title);
        free(list);
        list = next;
    }
}
