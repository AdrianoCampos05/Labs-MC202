#ifndef MEMORY_H
#define MEMORY_H

typedef struct memory *p_memory;

struct memory
{
    int *data, *indexes;
    int len, used_len, max_vecs, no_of_vecs;
};


/*Cria um novo vetor de memória.
______________________________________________________
Retorna:
----p_memory: um ponteiro para o início da memória*/
p_memory new_memory();


/*Libera o espaço alocado por um vetor de memória.
_________________________________________________
Parâmetro:
----p_memory mem: ponteiro para a memória*/
void destroy_memory(p_memory mem);


/*Guarda uma sequência de inteiros na memória.
Se necessário, dobra o tamanho da memória.
O vetor original NÂO é liberado.
____________________________________________________
Parâmetros:
----p_memory mem: ponteiro para a memória
----int* vec: ponteiro para o vetor com os inteiros
___________________________________________________________________
Retorna:
----int: a posição da memória onde o primeiro número foi salvo*/
int store_vec(p_memory mem, int *vec);


/*Libera o segmento de memória que começa em um dado índice.
Reduz o tamanho da memória pela metade se apenas o primeiro quarto for ocupado.
____________________________________________________
Parâmetros:
----p_memory mem: ponteiro para a memória
----int index: o índice do segmento a ser liberado
*/
void free_index(p_memory mem, int index);


/*Devolve os números salvos em um segmento da memória.
_________________________________________________
Parâmetros:
----p_memory mem: ponteiro para a memória
----int index: o índice do segmento
_____________________________________
Retorna:
----int*: um vetor com os números
Precisa ser liberado manualmente.*/
int *get_vector(p_memory mem, int index);


/*Devolve o número total de espaços (livres e ocupados) na memória.
_________________________________________________
Parâmetros:
----p_memory mem: ponteiro para a memória
_________________________________
Retorna:
----int: o tamanho da memória*/
int get_len(p_memory mem);


/*Devolve o número de espaços ocupados na memória.
_________________________________________________
Parâmetros:
----p_memory mem: ponteiro para a memória
_____________________________________________
Retorna:
----int: a quantidade de espaços ocupados*/
int get_used_len(p_memory mem);

#endif