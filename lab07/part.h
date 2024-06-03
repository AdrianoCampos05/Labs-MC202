#ifndef PART_H
#define PART_H


enum Size{SMALL=1, MED=2, LARGE=3};

typedef struct _part *p_part;

struct _part
{
    enum Size size;
    int pckg_time;
};


/*Cria uma nova peça.
__________________________________________________________________
Parâmetros:
---- char size: a primeira letra do tamanho da peça (p, m ou g)
---- int type: o tipo da peça
______________________________________
Retorna:
---- um ponteiro para a peça criada*/
p_part new_part(char size, int type);


/*Libera a memória ocupada por uma peça.
___________________________________
Parâmetro:
---- p_part: ponteiro para a peça*/
void destroy_part(p_part part);

#endif