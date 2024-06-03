#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "stack.h"
#include "worker.h"


int main()
{
    int queue_size, stack_size, parts_left;
    p_worker sorter, packer;
    p_queue conveyor;
    p_stack pile;

    scanf("%d %d", &queue_size, &stack_size);
    scanf("%d", &parts_left);

    sorter = new_worker('s');
    packer = new_worker('p');
    conveyor = new_queue(queue_size);
    pile = new_stack(stack_size);
    

    int clock = 0, delay = 0, incoming_parts = parts_left;
    char part_size[8];
    int part_type;

    // Esteira+, Pilha+, Pilha-
    int changes[3] = {0, 0, 0};
    
    printf("##### Simulação\n");
    while (parts_left > 0)
    {
        // Empacotador guarda a peça...
        if (is_done(packer))
        {
            destroy_part(drop(packer));
            parts_left--;
            changes[2] = 1;
        }
        // ...e tenta pega outra
        if (is_free(packer))
        {
            grab(packer, pop(pile));
        }


        // Classificador passa a peça...
        if (is_done(sorter) && !stack_full(pile))
        {
            push(pile, drop(sorter));
            changes[1] = 1;
        }
        // ...e tenta pegar outra
        if (is_free(sorter))
        {
            grab(sorter, dequeue(conveyor));
        }


        // Próxima peça entra
        if (incoming_parts > 0)
        {
            if (queue_full(conveyor))
            {
                delay++;
            }
            else
            {
                scanf("\n%s", part_size);
                scanf("%d", &part_type);
                enqueue(conveyor, new_part(part_size[0], part_type));
                incoming_parts--;
                changes[0] = 1;
            }
        }


        // Tempo passa
        clock++;
        tick(packer);
        tick(sorter);


        // Resumo é impresso
        printf("Min. %d: Classificação (+%d,-%d) | Embalagem (+%d,-%d).\n",
            clock, changes[0], changes[1], changes[1], changes[2]);
        
        changes[0] = changes[1] = changes[2] = 0;
    }

    printf("Tempo atraso: %d.", delay);
    destroy_queue(conveyor);
    destroy_stack(pile);
    destroy_worker(sorter);
    destroy_worker(packer);
    return 0;
}