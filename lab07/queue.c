#include <stdlib.h>
#include "queue.h"

p_queue new_queue(int max_len)
{
    p_queue q = malloc(sizeof(struct _queue));
    q->parts = malloc(max_len * sizeof(struct part*));
    q->start = 0;
    q->end = 0;
    q->len = 0;
    q->max_len = max_len;
    return q;
}


int queue_empty(p_queue q)
{
    return (q->len <= 0);
}


int queue_full(p_queue q)
{
    return (q->len >= q->max_len);
}


int enqueue(p_queue q, p_part part)
{
    if (queue_full(q))
        return 1;
    q->parts[q->end] = part;
    q->end = (q->end + 1) % q->max_len;
    q->len++;
    return 0;
}


p_part dequeue(p_queue q)
{
    if (queue_empty(q))
        return NULL;
    p_part temp = q->parts[q->start];
    q->start = (q->start + 1) % q->max_len;
    q->len--;
    return temp;
}


void destroy_queue(p_queue q)
{
    free(q->parts);
    free(q);
}
