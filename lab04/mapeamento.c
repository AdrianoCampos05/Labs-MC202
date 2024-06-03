#include <stdio.h>
#include <stdlib.h>

/*Cria uma matriz quadrada de inteiros.
A matriz é dinamicamente alocada e precisa ser liberada.
______________________________________________________
Parâmetros:
----int order: o número de linhas/colunas da matriz
_____________________________________
Retorna:
----int**: um ponteiro para a matriz*/
int** create_grid(int order)
{
    int **grid = malloc(order * sizeof(int*));
    if (!grid)
        exit(-1);
    for (int i = 0; i < order; i++)
    {
        grid[i] = malloc(order * sizeof(int));
        if (!grid[i])
            exit(-1);
    }
    
    return grid;
}


/*Libera a memória alocada por uma matriz.
_____________________________________________
Parâmetros:
----int **grid: o endereço da matriz
----int order: o número de linhas/colunas da matriz*/
void delete_grid(int **grid, int order)
{
    for (int i = 0; i < order; i++)
        free(grid[i]);
    free(grid);
}


/*Preenche uma matriz com inteiros fornecidos via terminal
_____________________________________________________________
Parâmetros:
----int **grid: o endereço da matriz
----int order: o número de linhas/colunas da matriz*/
void fill_grid(int **grid, int order)
{
    for (int i = 0; i < order;  i++)
        for (int j = 0; j < order; j++)
            scanf("%d", grid[i] + j);
}


/*Imprime os conteúdos de uma matriz
_______________________________________
Parâmetros:
----int **grid: o endereço da matriz
----int order: o número de linhas/colunas da matriz*/
void print_grid(int **grid, int order)
{
    for (int i = 0; i < order; i++)
    {
        for (int j = 0; j < order; j++)
            printf("%d\t", grid[i][j]);
        printf("\n");
    }
}


/*Calcula a soma dos elementos de uma linha de uma matriz.
O primeiro e o último elemento da linha NÂO são incluidos.
_____________________________________________________
Parâmetros:
----int **grid: o endereço da matriz
----int row: o número da linha, começando pelo 0
----int order: o número de linhas/colunas da matriz
___________________________
Retorna:
----int: A soma calculada*/
int mid_row_sum(int **grid, int row, int order)
{
    int sum = 0;
    for (int i = 1; i < order - 1; i++)
        sum += grid[row][i];
    return sum;
}


/*Calcula a soma dos elementos de uma coluna de uma matriz.
O primeiro e o último elemento da coluna NÂO são incluidos.
_____________________________________________________
Parâmetros:
----int **grid: o endereço da matriz
----int col: o número da coluna, começando pelo 0
----int order: o número de linhas/colunas da matriz
___________________________
Retorna:
----int: A soma calculada*/
int mid_col_sum(int **grid, int col, int order)
{
    int sum = 0;
    for (int i = 1; i < order - 1; i++)
        sum += grid[i][col];
    return sum;
}


/*Altera o valor de uma entrada dr uma matriz
_____________________________________________________
Parâmetros:
----int **grid: o endereço da matriz
----int row: o número da linha, começando pelo 0
----int col: o número da coluna, começando pelo 0
----int order: o número de linhas/colunas da matriz*/
void change_value(int **grid, int row, int column, int value)
{
    grid[row][column] = value;
}


/*Retorna uma submatriz de uma matriz quadrada.
A ordem da submatriz é um a menos que a da matriz original.
NÂO libera a matriz original.
_______________________________________________________________
Parâmetros:
----int **grid: o endereço da matriz
----int row_0: o número da primeira linha herdada
----int col_0: o número da primeira coluna herdada
----int order: o número de linhas/colunas da matriz original
_________________________________________
Retorna:
----int**: um ponteiro para a submatriz*/
int** smaller_grid(int **grid, int row_0, int col_0, int order)
{
    int **new_grid = create_grid(order - 1);
    for (int i = 0; i < order - 1; i++)
        for (int j = 0; j < order - 1; j++)
            new_grid[i][j] = grid[i + row_0][j + col_0];
    return new_grid;
}


/*Retorna a submatriz com a maior soma de elementos
A ordem da submatriz é um a menos que a da matriz original.
NÂO libera a matriz original.
_______________________________________________________________
Parâmetros:
----int **grid: o endereço da matriz
----int order: o número de linhas/colunas da matriz original
_________________________________________
Retorna:
----int**: um ponteiro para a submatriz
*/
int** priority_grid(int **grid, int order)
{
    int row_0 = 0, col_0 = 0;  // menor[0][0] = maior[row_0][col_0]
    int l_sum, r_sum, t_sum, b_sum;  // Somas sem os cantos
    int  max, q2, q3, q4; 

    l_sum = mid_col_sum(grid, 0, order);  // Soma coluna esquerda
    r_sum = mid_col_sum(grid, order - 1, order);  // Soma coluna direita
    t_sum = mid_row_sum(grid, 0, order);  // Soma linha superior
    b_sum = mid_row_sum(grid, order - 1, order);  // Soma linha inferior

    max = l_sum + t_sum + grid[0][0];  //Borda superior esquerda
    q2 = r_sum + t_sum + grid[0][order - 1];  // Borda superior direita
    q3 = l_sum + b_sum + grid[order - 1][0];  // Borda inferior esquerda
    q4 = r_sum + b_sum + grid[order - 1][order - 1];  // Borda inferior direita

    if (q2 > max)
    {
        col_0 = 1;
        max = q2;
    }

    if (q3 > max)
    {
        row_0 = 1;
        col_0 = 0;
        max = q3;
    }

    if (q4 > max)
    {
        row_0 = 1;
        col_0 = 1;
    }

    return smaller_grid(grid, row_0, col_0, order);
}

int main()
{
    int order, alt = 1;
    int alt_row, alt_col, alt_val;
    int **grid, **aux_grid;
    
    scanf("%d", &order);
    grid = create_grid(order);
    fill_grid(grid, order);

    printf("Quadras:\n");
    print_grid(grid, order);
    
    while (1)
    {
        aux_grid = priority_grid(grid, order);
        delete_grid(grid, order);
        grid = aux_grid;
        order--;
        
        printf("\nConjuntos que precisam de atenção:\n");
        print_grid(grid, order);
        
        if (order <= 1)
            break;
        
        scanf("%d", &alt);
        
        if (!alt)
            break;
        
        scanf("%d %d %d", &alt_row, &alt_col, &alt_val);
        change_value(grid, alt_row, alt_col, alt_val);
    }

    delete_grid(grid, order);
    return 0;
}