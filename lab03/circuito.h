#ifndef CIRCUITO_H
#define CIRCUITO_H

typedef struct
{
    int id;
    int players;
    int *strokes;
} circuito;

/*Cria e retorna um novo circuito com um número players de jogadores*/
circuito new_circ(int players);

/*Atribui a circ->id um inteiro fornecido pelo terminal.*/
void scan_id(circuito *circ);

/*Preenche o vetor circ->strokes com os inteiros fornecidos pelo terminal.
Os valores devem ser separados por espaços.*/
void scan_strokes(circuito *circ);

/*Lê e atribui o id e os números de jogadas fornecidos pelo terminal*/
void scan_info(circuito *circ);

/*Calcula e retorna o total de jogadas no circuito*/
int total_strokes(circuito *circ);

/*Libera a memória alocada pelo circuito no endereço circ.
Só deve ser chamada se o circuito não for mais ser acessado.*/
void delete_circ(circuito *circ);

#endif