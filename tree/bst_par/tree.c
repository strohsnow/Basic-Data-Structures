#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

Node *tree_find(Tree *tree, const int key)
{
    Node *ptr = tree->root;
    while (ptr != NULL)
    {
        if (ptr->key == key)
            return ptr;

        if (key < ptr->key)
            ptr = ptr->left;
        else 
            ptr = ptr->right;
    }

    return NULL;
}

int tree_insert(Tree *tree, const int key, const char *info)
{
    Node *ptr = tree->root;
    Node *par = NULL;
    while (ptr != NULL)
    {
        if (ptr->key == key)
            return 1;
        
        par = ptr;

        if (key < ptr->key)
            ptr = ptr->left;
        else
            ptr = ptr->right;
    }

    Node *new = malloc(sizeof *new);

    new->key = key;
    new->info = strdup(info);
    new->left = new->right = NULL;
    new->parent = par;

    if (par == NULL)
        tree->root = new;
    else if (key < par->key)
        par->left = new;
    else
        par->right = new;
    
    return 0;
}

int tree_delete(Tree *tree, const int key)
{
    Node *ptr = tree->root;
    while (ptr != NULL)
    {
        if (ptr->key == key)
            break;

        if (key < ptr->key)
            ptr = ptr->left;
        else
            ptr = ptr->right;
    }

    if (ptr == NULL)
        return 1;

    Node *par = ptr->parent;

    if (ptr->right == NULL)
    {
        if (par == NULL)
        {
            tree->root = ptr->left;
            if (tree->root != NULL)
                tree->root->parent = par;
        }
        else if (ptr == par->left)
        {
            par->left = ptr->left;
            if (par->left != NULL)
                par->left->parent = par;
        }
        else /* ptr == par->right */
        {
            par->right = ptr->left;
            if (par->right != NULL)
                par->right->parent = par;
        }
    }
    else
    {
        Node *right = ptr->right;
        if (right->left == NULL)
        {
            right->left = ptr->left;
            if (right->left != NULL)
                right->left->parent = right;

            if (par == NULL)
                tree->root = right;
            else if (ptr == par->left)
                par->left = right;
            else /* ptr = par->right */
                par->right = right;

            right->parent = par;
        }
        else
        {
            Node *succ = right->left;
            while (succ->left != NULL)
                succ = succ->left;
            right = succ->parent;

            right->left = succ->right;
            if (right->left != NULL)
                right->left->parent = right;

            succ->left = ptr->left;
            if (succ->left != NULL)
                succ->left->parent = succ;

            succ->right = ptr->right;
            succ->right->parent = succ;

            if (par == NULL)
                tree->root = succ;
            else if (ptr == par->left)
                par->left = succ;
            else /* ptr == par->right */
                par->right = succ;

            succ->parent = par;
        }
    }

    free(ptr->info);
    free(ptr);

    return 0;
}