#include <stdlib.h>
#include "worker.h"


p_worker new_worker(char type)
{
    p_worker w = malloc(sizeof(struct _worker));
    w->type = type;
    w->status = FREE;
    w->time_spent = 0;
    w->part = NULL;
    return w;
}


int grab(p_worker w, p_part part)
{
    if (part != NULL)
    {
        w->part = part;
        w->status = BUSY;
        w->time_spent = 0;
        return 1;
    }
    return 0;
}


p_part drop(p_worker w)
{
    w->status = FREE;
    return w->part;
}


int is_done(p_worker w)
{
    if (w->status == FREE)
        return 0;
    switch (w->type)
    {
        case 's':
            return (w->time_spent >= w->part->size);
        case 'p':
            return (w->time_spent >= w->part->pckg_time);
    }
    return -1;  // Algo deu errado
}


int is_free(p_worker w)
{
    return (w->status == FREE);
}


void tick(p_worker w)
{
    w->time_spent++;
}


void destroy_worker(p_worker w)
{
    free(w);
}