#include <stdlib.h>
#include "tree_and_stack.h"


// ÁRVORES //

p_tree new_tree(char val)
{
    p_tree tree = malloc(sizeof(struct _bin_node));
    tree->val = val;
    tree->left = NULL;
    tree->right = NULL;
    return tree;
}


p_tree left_attach(p_tree root, p_tree left)
{
    root->left = left;
    return root;
}


p_tree right_attach(p_tree root, p_tree right)
{
    root->right = right;
    return root;
}


int count_nodes(p_tree root)
{
    if (root == NULL)
        return 0;
    return count_nodes(root->left) + count_nodes(root->right) + 1;
}


void destroy_tree(p_tree root)
{
    if (root == NULL)
        return;
    destroy_tree(root->left);
    destroy_tree(root->right);
    free(root);
}



// PILHAS //

p_stack new_stack()
{
    p_stack stack = malloc(sizeof(struct _bin_node));
    stack->right = NULL;
    return stack;
}

void push(p_stack stack, char value)
{
    p_stack new_node = malloc(sizeof(struct _bin_node));
    new_node->val = value;
    new_node->right = stack->right;
    stack->right = new_node;
}


char pop(p_stack stack)
{
    char value;
    p_stack next = stack->right;
    if (next == NULL)
        return '\0';

    stack->right = next->right;
    value = next->val;
    free(next);
    return value;
}


void destroy_stack(p_stack stack)
{
    if (stack == NULL)
        return;
    destroy_stack(stack->right);
    free(stack);
}
