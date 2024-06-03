#include <stdlib.h>
#include <string.h>
#include "llrbTree.h"


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
