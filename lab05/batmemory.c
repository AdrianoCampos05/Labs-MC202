#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "memory.h"

typedef struct memory *p_memory;

struct memory
{
    int *data, *indexes;
    int len, used_len, max_vecs, no_of_vecs;
};


p_memory new_memory()
{
    p_memory mem = malloc(sizeof(struct memory));
    mem->data = malloc(8 * sizeof(int));
    mem->indexes = malloc(8 * sizeof(int)); // Os índices de cada vetor, em ordem 
    mem->len = 8;
    mem->used_len = 0;
    mem->max_vecs = 8;
    mem->no_of_vecs = 0;
    return mem;
}

void destroy_memory(p_memory mem)
{
    free(mem->data);
    free(mem->indexes);
    free(mem);
}

/*Retorna uma cópia do vetor com o dobro do tamanho
Libera o vetor original*/
static int *double_len(int *vec, int old_len)
{
    int *new_vec;
    new_vec = malloc(2 * old_len * sizeof(int));
    for (int i = 0; i < old_len; i++)
        new_vec[i] = vec[i];
    free(vec);
    return new_vec;
}


/*Dobra o espaço de memória*/
static void double_memory(p_memory mem)
{
    mem->data = double_len(mem->data, mem->len);
    mem->len *= 2;
}


/*Retorna uma cópia do vetor com o metade do tamanho
Libera o vetor original*/
static int *halve_len(int *vec, int old_len)
{
    int *new_vec;
    new_vec = malloc(old_len * sizeof(int) / 2);

    for (int i = 0; 2 * i < old_len; i++)
        new_vec[i] = vec[i];
    free(vec);
    return new_vec;
}


/*Reduz o espaço de memória pela metade*/
static void halve_memory(p_memory mem)
{
    mem->data = halve_len(mem->data, mem->len);
    mem->len /= 2;
}


/*Insere um número em um vetor ordenado
Preserva a ordenação*/
static int* vec_insert(int *vec, int n, int len)
{
    int i;
    for (i = len - 1; i >= 0 && vec[i] > n; i--)
        vec[i + 1] = vec[i];
    vec[i + 1] = n;
    return vec;
}


/*Remove o elemento em uma dado índice de um vetor*/
static void vec_remove(int *vec, int index, int len)
{
    for (int i = index; i < len; i++)
        vec[i] = vec[i + 1];
}


/*Retorna o índice de um dado elemento de um vetor ordenado
Se não for encontrado, retorna -1
Se o número estiver repetido, retorna o índice de alguma das ocorrências*/
static int search(int *vec, int n, int len)
{
    int start = 0, end = len, mid;
    while (end > start)
    {
        mid = (end + start) / 2;
        if (vec[mid] == n)
            return mid;
        else if (vec[mid] > n)
            end = mid;
        else
            start = mid + 1;
    }
    return -1;
}


/*Retorna o primeiro índice onde é possível alocar size inteiros.
Considera que o tamanho do vetor é ilimitado.*/
static int find_room(p_memory mem, int size)
{
    int i, prev, next;
    if (mem->no_of_vecs == 0)
        return 0;
    next = mem->indexes[0];
    if (size < next)
        return 0;
    for (i = 0; i + 1 < mem->no_of_vecs; i++)
    {
        prev = mem->indexes[i];
        next = mem->indexes[i + 1];
        if (prev + mem->data[prev] + size < next)
            return prev + mem->data[prev] + 1;
    }
    return next + mem->data[next] + 1;
}


int store_vec(p_memory mem, int *vec)
{
    int new_index = find_room(mem, vec[0] + 1);
    while (new_index + vec[0] + 1 > mem->len)
        double_memory(mem);
    
    for (int i = 0; i <= vec[0]; i++)
        mem->data[new_index + i] = vec[i];
    
    if (mem->no_of_vecs >= mem->max_vecs && mem->max_vecs >= 8)
    {
        mem->indexes = double_len(mem->indexes, mem->max_vecs);
        mem->max_vecs *= 2;
    }
    vec_insert(mem->indexes, new_index, mem->no_of_vecs);
    mem->no_of_vecs++;
    mem->used_len += vec[0] + 1;
    return new_index;
}


void free_index(p_memory mem, int index)
{
    int last_index, rel_index = search(mem->indexes, index, mem->no_of_vecs);
    vec_remove(mem->indexes, rel_index, mem->no_of_vecs);
    mem->used_len -= (mem->data[index] + 1);
    mem->no_of_vecs--;
    if (mem->max_vecs > 4 * mem->no_of_vecs && mem->max_vecs > 8)
    {
        mem->indexes = halve_len(mem->indexes, mem->max_vecs);
        mem->max_vecs /= 2;
    }
    last_index = mem->indexes[mem->no_of_vecs - 1];
    while (4*(last_index + mem->data[last_index]) <= mem->len && mem->len > 8)
        halve_memory(mem);
}


int *get_vector(p_memory mem, int index)
{
    int len = mem->data[index] + 1;
    int *vec = malloc(len * sizeof(int));
    for (int i = 0; i < len; i++)
        vec[i] = mem->data[index + i];
    return vec;
}


int get_len(p_memory mem)
{
    return mem->len;
}


int get_used_len(p_memory mem)
{
    return mem->used_len;
}




/*Salva um vetor de inteiros inputados na memória.
Imprime a posição onde o vetor foi salvo.*/
void bat_alloc(p_memory mem)
{
    int size, index, *vec;
    scanf("%d", &size);
    vec = malloc((size + 1) * sizeof(int));
    vec[0] = size;
    for (int i = 1; i <= size; i++)
        scanf("%d", vec + i);
    index = store_vec(mem, vec);
    free(vec);
    printf("%d\n", index);
}


/*Libera o vetor na memória salvo no índice inputado*/
void bat_free(p_memory mem)
{
    int index;
    scanf("%d", &index);
    free_index(mem, index);
}


/*Imprime o vetor na memória salvo no índice inputado*/
void bat_print(p_memory mem)
{
    int index;
    scanf("%d", &index);
    int *vec = get_vector(mem, index);
    for (int i = 0; i < vec[0]; i++)
        printf("%d ", vec[i + 1]);
    printf("\n");
    free(vec);
}


/*Imprime a quantidade de memória em uso e a memória total*/
void bat_uso(p_memory mem)
{
    printf("%d de %d\n", get_used_len(mem), get_len(mem));
}


int main()
{
    int no_of_commands;
    char command[6];

    scanf("%d", &no_of_commands);
    p_memory mem = new_memory(no_of_commands);
    for (int i = 0; i < no_of_commands; i++)
    {
        scanf("\nbat-%s", command);
        if (!strcmp(command, "alloc"))
            bat_alloc(mem);
        else if (!strcmp(command, "free"))
            bat_free(mem);
        else if (!strcmp(command, "uso"))
            bat_uso(mem);
        else
            bat_print(mem);
    }

    destroy_memory(mem);
    return 0;
}
