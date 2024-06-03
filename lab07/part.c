#include <stdlib.h>
#include "part.h"

p_part new_part(char size, int type)
{
    p_part p = malloc(sizeof(struct _part));
    switch (size)
    {
        case 'p':
            p->size = SMALL;
            break;
        case 'm':
            p->size = MED;
            break;
        case 'g':
            p->size = LARGE;
    }
    p->pckg_time = (p->size == SMALL ? type : type + 1); 
    return p;
}

void destroy_part(p_part p)
{
    free(p);
}

