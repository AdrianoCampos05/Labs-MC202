#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 200 
#define MAX_LINE_LEN 201

//#include "llrbTree.h"


#ifndef MAX_NAME_LEN
#define MAX_NAME_LEN 200
#endif

typedef struct _rb_node *p_node;

enum color{BLACK, RED};

struct _rb_node
{
    char *name;
    char type;
    enum color color;
    p_node left, right;
};


/*"Cria" uma árvore vazia.
____________________
Retorna (p_node):
---- NULL*/
p_node new_tree(void);


/*Insere uma variável em uma árvore.
____________
Parâmetros:
---- p_node root: a raiz da árvore
---- char *name: o nome da variável
---- char type: primeira letra do tipo (i, d ou c)
______________
Retorna (p_node):
---- ponteiro para a raiz da árvore modificada*/
p_node insert(p_node root, char *name, char type);


/*Busca uma variável e devolve seu tipo
____________
Parâmetros:
---- p_node tree: a árvore
---- char *name: nome da variável
________________
Retorna (char):
---- 'i': tipo int
---- 'd': tipo double
---- 'c': tipo char
---- '\0': variável não encontrada*/
char search(p_node tree, char *name);


/*Destrói uma árvore.
Libera os nós e as string de nome.
____________
Parâmetro:
---- p_node tree: a árvore*/
void destroy(p_node tree);



p_node new_tree()
{
    return NULL;
}


/*Cria um nó novo.
Salva uma cópia da string do nome*/
p_node new_node(char *name, char type)
{
    p_node node = malloc(sizeof(struct _rb_node));
    node->name = malloc(MAX_NAME_LEN);
    node->left = node->right = NULL;
    node->color = RED;
    strcpy(node->name, name);
    node->type = type;
    return node;
}


int is_red(p_node root)
{
    return (root && root->color == RED);
}


int is_black(p_node root)
{
    return !is_red(root);
}


p_node rotate_left(p_node root)
{
    p_node x = root->right;
    root->right = x->left;
    x->left = root;
    x->color = root->color;
    root->color = RED;
    return x;
}


p_node rotate_right(p_node root)
{
    p_node x = root->left;
    root->left = x->right;
    x->right = root;
    x->color = root->color;
    root->color = RED;
    return x;
}


void lift_red(p_node root)
{
    root->color = RED;
    root->left->color = BLACK;
    root->right->color = BLACK;
}


p_node rec_insert(p_node root, char *name, char type)
{
    p_node node;
    if (root == NULL)
    {
        node = new_node(name, type);
        return node;
    }

    if (strcmp(name, root->name) < 0)
        root->left = rec_insert(root->left, name, type);
    else
        root->right = rec_insert(root->right, name, type);

    // Correções
    if (is_red(root->right) && is_black(root->left))
        root = rotate_left(root);
    if (is_red(root->left) && is_red(root->left->left))
        root = rotate_right(root);
    if (is_red(root->left) && is_red(root->right))
        lift_red(root);

    return root;
}


p_node insert(p_node root, char *name, char type)
{
    root = rec_insert(root, name, type);
    root->color = BLACK;
    return root;
}


char search(p_node tree, char *name)
{
    int dif = 1;
    while (dif)
    {
        if (tree == NULL)
            return '\0';
        dif = strcmp(name, tree->name);
        if (dif < 0)
            tree = tree->left;
        else if (dif > 0)
            tree = tree->right;
    }

    return tree->type;
}


void destroy(p_node tree)
{
    if (tree == NULL)
        return;
    destroy(tree->left);
    destroy(tree->right);
    free(tree->name);
    free(tree);
}







///////////////////////////

/*Determina se a string é o nome de um tipo.
Reconhece os tipos int, double e char.
____________
Parâmetro:
---- char *type: a string
______________
Retorna (int):
---- 0: a string não representa um tipo
---- 1: a string representa um tipo*/
int is_type(char *type)
{
    return !(strcmp(type, "int") && strcmp(type, "double") && strcmp(type, "char"));
}


/*Determina se a string é o nome de um tipo.
Reconhece os tipos int, double e char.
____________
Parâmetro:
---- char *type: a string
______________
Retorna (const char*):
---- 0: a string não representa um tipo
---- 1: a string representa um tipo*/
const char *type_str(char type)
{
    switch (type)
    {
        case 'i':
            return "int";
        case 'd':
            return "double";
        case 'c':
            return "char";
        default:
            return NULL;
    }
}


/*Imprime mensagem de erro para símbolo indefinido
_____________
Parâmetros:
---- int line: o número da linha
---- char name: o símbolo*/
void undef_error(int line, char *name)
{
    printf("Linha %d: o símbolo %s não foi definido.\n", line, name);
}


/*Imprime mensagem de erro para operações com tipos diferentes.
_____________
Parâmetros:
---- int line: o número da linha
---- char *var1: primeira variável
---- char *var2: segunda variável
---- char type1: letra do tipo (i, d, c) de var1
---- char type2: letra do tipo (i, d, c) de var2
---- char operator: operador*/
void arithmetic_error(int line, char *var1, char *var2, char type1, char type2, char operator)
{
    printf("Linha %d: tipos incompatíveis: %s (%s) %c %s (%s).\n",
        line, var1, type_str(type1), operator, var2, type_str(type2));
}


/*Imprime mensagem de erro para atribuição do tipo errado.
_____________
Parâmetros:
---- int line: o número da linha
---- char *var: a variável
---- char var_type: a letra do tipo (i, d, c) esperado
---- char value_type: a letra do tipo (i, d, c) recebido*/
void assignment_error(int line, char *var, char var_type, char value_type)
{
    printf("Linha %d: tipos incompatíveis: o símbolo %s espera %s, obteve %s.\n",
        line, var, type_str(var_type), type_str(value_type));
}


/*Imprime todas as variáveis declaradas
Também imprime seus respectivos tipos.
Segue a ordem lexicográfica.
____________
Parâmetro:
---- p_node namespace: árvore com as variáveis*/
void print_variables(p_node namespace)
{
    if (namespace == NULL)
        return;
    print_variables(namespace->left);
    printf("%s %s\n", namespace->name, type_str(namespace->type));
    print_variables(namespace->right);
}


/*Encontra possíveis erros e imprime a mensagem adequada.
______________________________________________
Parâmetros:
---- int line_no: número da linha
---- p_node namespace: árvore de variáveis
---- char *var1: variável atribuida
---- char *var2: primeiro operando
---- char *var3: segundo operando
---- char operator: operador
_________________________
Retorna (int):
---- 0: não há erros
---- 1: var1 indefinida
---- 2: var2 indefinida
---- 3: var3 indefinida
---- 4: operação ilegal
---- 5: atribuição ilegal*/
int check_for_errors(int line_no, p_node namespace, char *var1, char *var2, char *var3, char operator)
{
    char type1, type2, type3;

    type1 = search(namespace, var1);
    if (type1 == '\0')
    {
        undef_error(line_no, var1);
        return 1;
    }

    type2 = search(namespace, var2);
    if (type2 == '\0')
    {
        undef_error(line_no, var2);
        return 2;
    }

    type3 = search(namespace, var3);
    if (type3 == '\0')
    {
        undef_error(line_no, var3);
        return 3;
    }

    if (type2 != type3)
    {
        arithmetic_error(line_no, var2, var3, type2, type3, operator);
        return 4;
    }

    if (type1 != type2)
    {
        assignment_error(line_no, var1, type1, type2);
        return 5;
    }

    return 0;
}


/*Analisa uma linha de código.
Salva variáveis declaradas.
Detecta e imprime possíveis erros.
_____________
Parâmetros:
---- int line_no: número da linha
---- char *line_text: a linha
---- p_node namespace: árvore de variáveis passada por referência
______________
Retorna (int):
---- o código do primeiro erro encontrado
---- 0 se não há erros na linha*/
int check_line(int line_no, char *line_text, p_node *namespace)
{
    char var1[MAX_NAME_LEN], var2[MAX_NAME_LEN], var3[MAX_NAME_LEN], type[7];
    char operator, parentheses;  // Parenteses diferenciam funções de variáveis

    if (sscanf(line_text, "%s = %s %[+-/*%] %[^;]", var1, var2, &operator, var3) == 4)
    {
        return check_for_errors(line_no, *namespace, var1, var2, var3, operator);
    }

    if (sscanf(line_text, "%6s %[^;(]%[(]", type, var1, &parentheses) == 2 && is_type(type))
    {
        *namespace = insert(*namespace, var1, type[0]);
    }

    return 0;
}


int main()
{
    p_node namespace = new_tree();
    char line_text[MAX_LINE_LEN];
    int line_no = 1, has_type_errors = 0;

    while (fgets(line_text, MAX_LINE_LEN, stdin))
    {
        has_type_errors = check_line(line_no, line_text, &namespace) || has_type_errors;
        line_no++;
    }

    if (!has_type_errors)
        printf("Não há erros de tipo.\n");
    print_variables(namespace);
    destroy(namespace);
    return 0;
}