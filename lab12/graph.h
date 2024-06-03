#ifndef __GRAPH_H__
#define __GRAPH_H__

typedef unsigned char u8;

typedef struct Graph *p_graph;


/*Representação de um grafo não direcionado.
Membros:
---- int n: número de vértices
---- int size: tamanho (em bytes) da "matriz" de adjacência
---- u8 *edges: "matriz" de adjacência 
É apenas a parte triangular superior da matriz, condensada em um array.
Cada bit representa uma aresta.*/
struct Graph
{
    int n, size;
    u8 *edges;
};


/*Cria um novo grafo
___________
Parâmetro:
---- int expct_n: número esperado de vértices.
Se for ultrapassado, é necessário realocar a matriz de adjacência.
___________________
Retorna (p_graph):
---- ponteiro para o grafo*/
p_graph new_graph(int expct_n);


/*Destrói um grafo
___________
Parâmetro:
---- p_graph g: o grafo*/
void destroy_graph(p_graph g);


/*Adiciona um novo vértice ao grafo
Se necessário, aloca mais memória para as arestas.
___________
Parâmetro:
---- p_graph g: o grafo

obs: o número dos vértices corresponde à sua ordem de criação.
o primeiro vértice criado é o vértice 0, o segundo é o vértice 1, etc.*/
void create_vertex(p_graph g);


/*Conecta dois vértices.
____________
Parâmetros:
---- p_graph g: o grafo
---- v1, v2: os números dos vértices*/
void create_edge(p_graph g, int v1, int v2);


/*Conecta dois vértices.
____________
Parâmetros:
---- p_graph g: o grafo
---- v1, v2: os números dos vértices*/
void remove_edge(p_graph g, int v1, int v2);


/*Diz se há aresta entre dois vértices.
____________
Parâmetros:
---- p_graph g: o grafo
---- v1, v2: os números dos vértices
_____________
Retorna (int):
---- 0 se a aresta não existe
---- 1 se a aresta existe*/
int has_edge(p_graph g, int v1, int v2);


/*Separa os vértices do grafo em componentes conexas.
___________
Parâmetro:
---- p_graph g: o grafo
______________
Retorna (*int):
---- array que indica a componente conexa de cada vértice
arr[v1] == arr[v2] se existe caminho de v1 até v2.
Precisa ser liberado manualmente.*/
int *get_components(p_graph g);


/*Encontra o caminho mais curto de v1 até v2.
Caso haja mais de uma opção, prioriza caminhos que terminam com vértices mais antigos.
____________
Parâmetros:
---- p_graph g: o grafo
---- int v1: início do caminho
---- int v2: final do caminho
______________
Retorna (*int):
---- array com os vértices do caminho
Em iterações, parar ao encontrar v2; índices posteriores não são inicializados.
Precisa ser liberado manualmente.*/
int *shortest_path(p_graph g, int v1, int v2);


#endif //__GRAPH_H__