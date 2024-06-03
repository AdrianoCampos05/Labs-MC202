#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

#define bytes(n) ((n-1)/8+1) //Bytes necessários para guardar n bits


p_graph new_graph(int expct_n)
{
    p_graph g = malloc(sizeof(struct Graph));
    g->n = 0;

    g->size = bytes((expct_n * (expct_n - 1)) / 2);
    g->edges = calloc(g->size, 1);

    return g;
}


void destroy_graph(p_graph g)
{
    free(g->edges);
    free(g);
}


void create_vertex(p_graph g)
{
    g->n++;
    int size_needed = bytes((g->n * (g->n - 1))/2);
    if (size_needed <= g->size)
        return;  //Já há espaço o suficiente

    //Não há espaço o suficiente
    g->edges = realloc(g->edges, size_needed);
    for (int i = g->size; i < size_needed; i++)  //Inicializa a memória nova
        g->edges[i] = 0;
    g->size = size_needed;
}


/*Converte as coordenadas [row][col] a uma forma
compatível com a matriz de adjacência condensada.
____________
Parâmetros:
int row: a linha da matriz completa
int col: a coluna da matriz completa
int *rem: endereço a ser sobrescrito

obs: é necessário que row < col
_____________
Retorna (int):
---- O índice do array de adjacência que contém a posição [row][col]
Em rem, registra qual bit da posição devolvida corresponde a [row][col]
0 corresponde ao bit menos significativo, 7 ao mais significativo*/
int __index(int row, int col, int *rem)
{
    int pos = (col*col - col)/2 + row;
    *rem = pos % 8;  //remainder
    return pos / 8;
}


void create_edge(p_graph g, int v1, int v2)
{
    int rem, i;
    if (v1 < 0 || v2 < 0 || v1 >= g->n || v2 >= g->n)  //vértice inválido
        return;
    if (v1 < v2)
        i = __index(v1, v2, &rem);
    else
        i = __index(v2, v1, &rem);

    g->edges[i] |= 1 << rem;  //rem-ésimo bit menos significativo de g->edges[i] = 1
}


void remove_edge(p_graph g, int v1, int v2)
{
    int rem, i;
    if (v1 < 0 || v2 < 0 || v1 >= g->n || v2 >= g->n)  //vértice inválido
        return;
    if (v1 < v2)
        i = __index(v1, v2, &rem);
    else
        i = __index(v2, v1, &rem);
    
    g->edges[i] &= ~(1 << rem);  //rem-ésimo bit menos significativo de g->edges[i] = 0
}


/*Retorna o valor de uma aresta.
____________
Parâmetros:
---- p_graph g: o grafo
---- v1, v2: os números dos vértices

obs: é necessário que v1 < v2
_____________
Retorna (int):
---- 0 se a aresta não existe
---- alguma potência de 2 se a aresta existe*/
int __edge(p_graph g, int v1, int v2)
{
    int rem, i = __index(v1, v2, &rem);
    return g->edges[i] & (1 << rem);
}


int has_edge(p_graph g, int v1, int v2)
{
    if (v1 == v2 || v1 < 0 || v2 < 0 || v1 >= g->n || v2 >= g->n)
        return 0;
    if (v1 < v2)
        return __edge(g, v1, v2) && 1;
    return __edge(g, v2, v1) && 1; 
}


/*Busca em profundidade.
Encontra todos os vértices conectados a v
Em comp, muda os índices dos vértices encontrados para comp_no*/
void __dfs(p_graph g, int v, int *comp, int comp_no)
{
    for (int i = 0; i < g->n; i++)
        if (comp[i] == 0 && has_edge(g, v, i))
        {
            comp[i] = comp_no;
            __dfs(g, i, comp, comp_no);
        }
}


int *get_components(p_graph g)
{
    int *comp = calloc(g->n, sizeof(int)); //Componente a qual cada vértice pertence
    int comp_no = 1;  //Componente conexa atual
    for (int i = 0; i < g->n; i++)
        if (comp[i] == 0)
        {
            comp[i] = comp_no;
            __dfs(g, i, comp, comp_no);
            comp_no++;
        }
    return comp;
}


/*Busca em largura
Retorna um array que representa o menor caminho de v1 a v2
Se i está no caminho, arr[i] vem imediatamente antes de i no caminho.
arr[v1] == v1*/
int *__bfs(p_graph g, int v1, int v2)
{
    //Cria o vetor de pais
    int *parent = malloc(g->n * sizeof(int)); 
    for (int i = 0; i < g->n; i++)
        parent[i] = -1;
    parent[v1] = v1;

    //Cria a fila
    int q_start = 0, q_end = 1;
    int *queue = malloc(g->n * sizeof(int));
    queue[0] = v1;


    int v;
    while (q_start != q_end)
    {
        v = queue[q_start++];  //desenfileira
        for (int w = 0; w <g->n; w++)
            if (has_edge(g, v, w) && parent[w] == -1)
            {
                parent[w] = v;
                queue[q_end++] = w;  //enfileira w
                if (w == v2)  //Caminho encontrado
                {
                    q_start = q_end;  //Para sair do while
                    break;
                }
            }
    }
    free(queue);
    return parent;
}


int *shortest_path(p_graph g, int v1, int v2)
{
    int *parent = __bfs(g, v2, v1);
    if (parent[v1] == -1)  //
        return NULL;
    
    int *path = malloc(g->n * sizeof(int));
    
    //Transcreve o caminho para path
    int i = 0;
    for (int v = v1; v != v2; v = parent[v])
        path[i++] = v;
    path[i] = v2;

    free(parent);
    return path;
}
