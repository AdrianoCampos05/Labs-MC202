#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "list.h"

#define STR_MAX 50

typedef struct node* p_node;

struct node
{
    char *title;
    p_node next;
};


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




///////
/*Remove o espaço no começo e o \n no final de um título*/
void format_str(char *str)
{
    int i;
    if (str[0] == '\0')
        return;
    for (i = 1; str[i] != '\n' && str[i] != '\0'; i++)
        str[i - 1] = str[i];
    str[i - 1] = '\0';
}

/*Imprime a lista de livros*/
void print_list(p_node list)
{
    if (!list)
        return;
    for (;list->next; list = list->next)
        printf("%s, ", list->title);
    printf("%s\n", list->title);
}


int main()
{
    int state = 1;  // Controla onde o próximo título será inserido
    char command[10], *title = NULL, *prev_title = NULL;
    p_node list = new_list();
    while (scanf("%s", command) != EOF)
    {
        if (!strcmp(command, "inicio"))
            state = 1;
        
        else if (!strcmp(command, "final"))
            state = 2;
        
        else if (!strcmp(command, "imprimir"))
            print_list(list);
        
        else
        {
            title = malloc(STR_MAX);
            fgets(title, STR_MAX, stdin);
            format_str(title);
            
            if (!strcmp(command, "adicionar"))
            {    
                switch (state)
                {
                    case 0:
                        list = insert_after(list, title, prev_title);
                        break;
                    case 1:
                        list = insert_first(list, title);
                        break;
                    case 2:
                        list = insert_last(list, title);
                }
                prev_title = title;
                state = 0;
            }
            
            else
            {
                list = remove_title(list, title);
                free(title);
            }
        }
    }
    destroy_list(list);
    return 0;
}