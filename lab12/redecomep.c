#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

#define MAX_VERTICES 20


/*Devolve o primeiro índice de arr em que val aparece.
Se val não aparece, retorna -1.*/
int find(int *arr, int len, int val)
{
    for (int i = 0; i < len; i++)
        if (arr[i] == val)
            return i;
    return -1;
}


/*Imprime se há conexão entre v1 e v2
obs: v1 e v2 são os números dos vértices por ordem de inserção, NÃO seus IDs*/
void print_connection(p_graph g, int v1, int v2)
{
    int *component = get_components(g);
    if (component[v1] == component[v2])
        printf("Existe conexão entre os nós.\n");
    else
        printf("Não existe conexão entre os nós.\n");
    free(component);
}


/*Imprime os IDs dos vértices conectados a cada um dos vértices
obs: v1 e v2 são os números dos vértices por ordem de inserção, NÃO seus IDs*/
void print_comps(p_graph g, int *id)
{
    int *comp = get_components(g);

    for (int i = 0; i < g->n; i++)
    {
        printf("Ponto %d (Pontos diretamente ou indiretamente conectados):", id[i]);
        for (int j = 0; j < g->n; j++)
            if (comp[i] == comp[j])
                printf(" %d", id[j]);
        printf("\n");
    }
    free(comp);
}


/*Imprime o menor caminho do vértice v1 até v2
obs: v1 e v2 são os números dos vértices por ordem de inserção, NÃO seus IDs*/
void print_path(p_graph g, int v1, int v2, int* id)
{
    int *path = shortest_path(g, v1, v2);
    if (path == NULL)
    {
        printf("Não existe conexão entre os nós.\n");
        return;
    }

    for (int i = 0; path[i] != v2; i++)
        printf("%d -> ", id[path[i]]);
    printf("%d\n", id[v2]);
    free(path);
}


int main()
{
    p_graph graph = new_graph(MAX_VERTICES);
    
    //Os ids dos vértices na ordem de inserção
    //Se MAX_VERTICES for muito grande, outra estrutura pode ser mais adequada
    int id[MAX_VERTICES];
    int n = 0;  //número de vértices

    int op_code, loop = 1;
    int v1, v2;
    while (loop)
    {
        scanf(" %d", &op_code);
        switch(op_code)
        {
            case 1:  //cria vértice
                scanf(" %d", &v1);
                id[n++] = v1;
                create_vertex(graph);
                break;
            case 2:  //cria aresta
                scanf(" %d %d", &v1, &v2);
                create_edge(graph, find(id, n, v1), find(id, n, v2));
                break;
            case 3:  //remove aresta
                scanf(" %d %d", &v1, &v2);
                remove_edge(graph, find(id, n, v1), find(id, n, v2));
                break;
            case 4:  //verifica conexão
                scanf(" %d %d", &v1, &v2);
                print_connection(graph, find(id, n, v1), find(id, n, v2));
                break;
            case 5:  //encontra caminho
                scanf(" %d %d", &v1, &v2);
                print_path(graph, find(id, n, v1), find(id, n, v2), id);
                break;
            case 6:  //encontra componentes conexas
                print_comps(graph, id);
                break;
            default:  //encerra o programa
                loop = 0;
        }
    }
    destroy_graph(graph);
    return 0;
}