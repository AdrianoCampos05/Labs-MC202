#include <stdio.h>
#define MAX 301


int search_vert(char word[], char grid[][MAX], int pos_y, int pos_x, int dir, int rows)
/*A partir da primeira letra, procura o resto da palavra em uma direção vertical
Retorna 1 se a palavra for encontrada, e 0 caso contrário

word: a palavra procurada
grid: a matriz do caça-palavras
pos_y: a linha à qual a primeira letra pertence
pos_x: a coluna à qual a primeira letra pertence
dir: 1 se a busca for para baixo, -1 se a busca for para cima
rows: o número de linhas no caça-palavras*/
{
    pos_y += dir; // A primeira letra já foi verificada
    for (int i = 1; word[i] != '\0'; i++)
    {
        if (pos_y <0 || pos_y >= rows)
            return 0;

        if (word[i] != grid[pos_y][pos_x])
            return 0;
        
        pos_y += dir;
    }
    return 1;
}


int search_hor(char word[], char grid[][MAX], int pos_y, int pos_x, int dir, int columns)
/*A partir da primeira letra, procura o resto da palavra em uma direção horizontal
Retorna 1 se a palavra for encontrada, e 0 caso contrário

word: a palavra procurada
grid: a matriz do caça-palavras
pos_y: a linha à qual a primeira letra pertence
pos_x: a coluna à qual a primeira letra pertence
dir: 1 se a busca for para a direita, -1 se a busca for para a esquerda
columns: o número de colunas no caça-palavras*/
{
    pos_x += dir;
    for (int i = 1; word[i] != '\0'; i++)
    {
        if (pos_x <0 || pos_x >= columns)
            return 0;

        if (word[i] != grid[pos_y][pos_x])
            return 0;
        
        pos_x += dir;
    }
    return 1;
}


int search(char word[], char grid[][MAX], int pos_y, int pos_x, int rows, int columns)
/*A partir da primeira letra, verifica se o resto da palavra pode ser encontrada em alguma direção
Retorna 1 se a palavra for encontrada, e 0 caso contrário

word: a palavra procurada
grid: a matriz do caça-palavras
pos_y: a linha à qual a primeira letra pertence
pos_x: a coluna à qual a primeira letra pertence
dir: 1 se a busca for para baixo, -1 se a busca for para cima
rows: o número de linhas no caça-palavras
columns: o número de colunas no caça-palavras*/
{
    return (search_hor(word, grid, pos_y, pos_x, 1, columns) || search_hor(word, grid, pos_y, pos_x, -1, columns) ||
        search_vert(word, grid, pos_y, pos_x, 1, rows) || search_vert(word, grid, pos_y, pos_x, -1, rows));
}


int is_on_grid(char word[], char grid[][MAX], int rows, int columns)
/*Verifica se a palavra dada está no caça-palavras
Retorna 1 se estiver, e 0 caso contrário

word: a palavra procurada
grid: a matriz do caça-palavras
rows: o número de linhas no caça-palavras
columns: o número de colunas no caça-palavras*/
{   
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            if (grid[i][j] == word[0])
                if (search(word, grid, i, j, rows, columns))
                    return 1;
    return 0;

}


int main()
{
    char grid[MAX][MAX];
    char words[MAX][MAX];

    int i, j, rows, columns, word_num;

    scanf("%d %d %d", &rows, &columns, &word_num);

    for (i = 0; i < rows; i++)
        for (j = 0; j < columns; j++)
            scanf(" %c", &grid[i][j]);

    for (i = 0; i < word_num; i++)
        scanf("\n%s", words[i]);
    
    for (i = 0; i < word_num; i++)
        if (is_on_grid(words[i], grid, rows, columns))
            printf("A palavra %s está no texto!\n", words[i]);
        else
            printf("A palavra %s não está no texto!\n", words[i]);
    
    return 0;
}
