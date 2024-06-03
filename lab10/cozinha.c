#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "survivor.h"

#define MAX_NAME_LEN 16
#define MAX_DISH_LEN 26


/*Lê e registra os pedidos da rodada*/
void read_orders(int no_of_orders, p_heap heap, p_survivor *survivors)
{
    int id, key_delta;
    char type, *dish;
    for (int i = 0; i < no_of_orders; i++)
    {
        scanf(" %1[na]%*s %d", &type, &id);
        
        // Novo pedido
        if (type == 'n')
        {
            dish = malloc(MAX_DISH_LEN);
            scanf(" %[^\n]", dish);
            set_dish(survivors[id], dish);
            insert(heap, new_item(id, survivors[id]->key));
        }

        // Alteração
        else
        {
            scanf("%d", &key_delta);
            add_to_key(heap, id, key_delta);
        }
    }
}


int main()
{
    int pan_no, survivor_no;
    scanf("%d %d", &pan_no, &survivor_no);
    p_survivor *survivors = malloc(survivor_no * sizeof(p_survivor));
    
    // Declaração dos sobreviventes
    char *name, *surname;
    int key;
    for (int i = 0; i < survivor_no; i++)
    {
        name = malloc(MAX_NAME_LEN);
        surname = malloc(MAX_NAME_LEN);
        scanf(" %s %s %d", name, surname, &key);
        survivors[i] = new_survivor(i, key, name, surname);
    }

    p_heap heap = new_heap(survivor_no);
    int no_of_orders;
    Item item;

    // Pedidos
    scanf(" %d", &no_of_orders);
    read_orders(no_of_orders, heap, survivors);
    for (int round = 1; !(heap_empty(heap) && no_of_orders == 0); round++)
    {   
        printf("---- rodada %d ----\n", round);
        
        for (int i = 0; i < pan_no && !heap_empty(heap); i++)
        {
            item = pop(heap);
            print_info(survivors[item.id], item.key);
        }

        if (no_of_orders != 0)
        {
            scanf(" %d", &no_of_orders);
            read_orders(no_of_orders, heap, survivors);
        }
    }
    
    for (int i = 0; i < survivor_no; i++)
        destroy_survivor(survivors[i]);
    free(survivors);
    destroy_heap(heap);
    return 0;
}