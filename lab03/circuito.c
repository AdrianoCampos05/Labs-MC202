#include <stdio.h>
#include <stdlib.h>
#include "circuito.h"

circuito new_circ(int players)
{
    circuito circ;
    circ.players = players;
    circ.strokes = malloc(players * sizeof(int));

    if (circ.strokes == NULL)
        exit(-1);
    return circ;
}

void scan_id(circuito *circ)
{
    scanf("%d", &circ->id);
}

void scan_strokes(circuito *circ)
{
    for (int i = 0; i < circ->players; i++)
        scanf("%d", circ->strokes + i);
}

void scan_info(circuito *circ)
{
    scan_id(circ);
    scan_strokes(circ);
}

int total_strokes(circuito *circ)
{
    int sum  = 0;
    for (int i = 0; i < circ->players; i++)
        sum += circ->strokes[i];
    return sum;
}

void delete_circ(circuito *circ)
{
    free(circ->strokes);
    circ->strokes = NULL;  // Evita double free
}
