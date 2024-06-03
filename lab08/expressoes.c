#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree_and_stack.h"


/*Verifica se um caracter é um operador.
______________________
Parâmetro:
---- char c: o caracter
______________________________
Retorna (int):
---- 0: se não é um operador
---- 1: se for é operador*/
int is_operator(char c)
{
    switch (c)
    {
        case '>':
        case '<':
        case '{':
        case '}':
        case '&':
        case '|':
        case '=':
        case '!':
            return 1;
        default:
            return 0;
    }
}


/*Verifica se um caracter é um digito de 0 a 9.
______________________
Parâmetro:
---- char c: o caracter
___________________________
Retorna (int):
---- 0: se não é um dígito
---- 1: se é um dígito*/
int is_digit(char c)
{
    return (c >= '0' && c <= '9');
}


/*Verifica se um caracter é uma constante numérica ou lógica.
______________________
Parâmetro:
---- char c: o caracter
________________________________
Retorna (int):
---- 0: se não é uma constante
---- 1: se é uma constante*/
int is_const(char c)
{
    return (c == 'T' || c == 'F' || is_digit(c));
}


/*Determina o primeiro digito é maior que o segundo
______________________________
Parâmetro:
---- char a: primeiro símbolo
---- char b: segundo símbolo
____________________________________________________________
Retorna (int):
---- 0: se a <= b ou algum dos símbolos não é um dígito
---- 1: se a > b e ambos são dígitos*/
int gt(char a, char b)
{
    if (is_digit(a) && is_digit(b))
        return (a > b);
    return 0;
}


/*Determina o primeiro digito é maior ou igual ao segundo
______________________________
Parâmetro:
---- char a: primeiro símbolo
---- char b: segundo símbolo
___________________________________________________________
Retorna (int):
---- 0: se a < b ou algum dos símbolos não é um dígito
---- 1: se a >= b e ambos são dígitos*/
int ge(char a, char b)
{
    if (is_digit(a) && is_digit(b))
        return (a >= b);
    return 0;
}


/*Cria uma pilha com os caracteres lidos.
Para quando encontra um '\\n'.
___________________________
Retorna (p_stack):
---- ponteiro para a pilha*/
p_stack stack_input()
{
    char input;
    p_stack stack = new_stack();
    scanf("\n%c", &input);
    while (input != '\n')
    {
        push(stack, input);
        scanf("%c", &input);
    }

    return stack;
}


/*Cria a árvore da expressão empilhada;
________________________________________________________
Parâmetro:
---- p_stack stack: pilha de caracteres
____________________________
Retorna (p_tree):
---- ponteiro para a árvore*/
p_tree build_tree(p_stack stack)
{
    char c = pop(stack);
    p_tree tree = new_tree(c);
    if (!is_operator(c))
        return tree;
    right_attach(tree, build_tree(stack));
    left_attach(tree, build_tree(stack));
    return tree;
}


/*Cria a string da expressão em notação infixa.
____________________________________________________________
Parâmetros:
---- p_tree tree: árvore da expressão
---- int len: o tamanho da expressão em notação posfixa
_________________________
Retorna (char*):
---- string da expressão*/
char *infix_str(p_tree tree, int len)
{
    char *left, *right, *outer = malloc(3 * len);
    char aux[4] = {' ', ' ', ' ', '\0'};

    if (is_operator(tree->val))
    {
        // Abre parênteses
        outer[0] = '(';
        outer[1] = '\0';

        // Lê o primeiro operando
        left = infix_str(tree->left, len - 2);
        strcat(outer, left);
        free(left);

        // Lê a operação
        aux[1] = tree->val;
        strcat(outer, aux);

        // Lê o segundo operando
        right = infix_str(tree->right, len - 2);
        strcat(outer, right);
        free(right);

        // Fecha parênteses
        aux[0] = ')';
        aux[1] = '\0';
        strcat(outer, aux);
    }

    else
    {
        outer[0] = tree->val;
        outer[1] = '\0';
    }

    return outer;
}


/*Verifica se uma simplificação no nó é possível.
Se for, libera os filhos e altera o valor do nó.
NÃO chamar caso o nó não tenha filhos.
______________________
Parâmetro:
---- p_tree tree: o nó*/
void trim(p_tree tree)
{
    char new_val = '\0';
    char l = tree->left->val;
    char r = tree->right->val;

    // Algum operando tem que ser const/variável p/ simplificar
    if (is_operator(l) && is_operator(r))
        return;

    switch (tree->val)
    {
        case '>':
            if (l == '0' || r == '9' || l == r || ge(r, l))
                new_val = 'F';
            else if (gt(l, r))
                new_val = 'T';
            break;
        case '<':
            if (l == '9' || r == '0' || l == r || ge(l, r))
                new_val = 'F';
            else if (gt(r, l))
                new_val = 'T';
            break;
        case '{':
            if (l == '0' || r == '9' || l == r || ge(r, l))
                new_val = 'T';
            else if (gt(l, r))
                new_val = 'F';
            break;
        case '}':
            if (l == '9' || r == '0' || l == r || ge(l, r))
                new_val = 'T';
            else if (gt(r, l))
                new_val = 'F';
            break;
        case '&':
            if (l == 'F' || r == 'F')
                new_val = 'F';
            else if (l == 'T' && r == 'T')
                new_val = 'T';
            break;
        case '|':
            if (l == 'T' || r == 'T')
                new_val = 'T';
            else if (l == 'F' && r == 'F')
                new_val = 'F';
            break;
        case '=':
            if (l == r)
                new_val = 'T';
            else if (is_const(l) && is_const(r) && l != r)
                new_val = 'F';
            break;
        case '!':
            if (l == r)
                new_val = 'F';
            else if (is_const(l) && is_const(r) && l != r)
                new_val = 'T';
    }

    if (new_val == '\0')
        return;  // Nenhuma simplificação foi possível
    tree->val = new_val;
    destroy_tree(tree->left);
    destroy_tree(tree->right);
    tree->left = NULL;
    tree->right = NULL;
}


/*Simplifica a árvore da expressão.
A árvore original é perdida.
______________________________________
Parâmetros:
---- p_tree tree: árvore da expressão
__________________________
Retorna (p_tree):
---- a árvore simplificada*/
p_tree simplified(p_tree tree)
{
    if (!is_operator(tree->val))
        return tree;
    tree->left = simplified(tree->left);
    tree->right = simplified(tree->right);
    trim(tree);
    return tree;
}


int main()
{
    p_stack stack;
    p_tree tree;
    char* expression;
    int len, no_of_expressions;
    scanf("%d", &no_of_expressions);

    for (int i = 0; i < no_of_expressions; i++)
    {
        if (i != 0)
            printf("\n");

        // Constrói a árvore
        stack = stack_input();
        tree = build_tree(stack);
        destroy_stack(stack);

        // Imprime a expressão
        len = count_nodes(tree);
        expression = infix_str(tree, len);
        printf("%s\n", expression);
        free(expression);

        // Simplifica e imprime a expressão
        tree = simplified(tree);
        len = count_nodes(tree);
        expression = infix_str(tree, len);
        printf("%s\n", expression);

        free(expression);
        destroy_tree(tree);
    }
    return 0;
}
