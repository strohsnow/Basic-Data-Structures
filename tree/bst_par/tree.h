#ifndef TREE_H
#define TREE_H

typedef struct Node
{
    int key;
    char *info;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
}
Node;

typedef struct Tree
{
    Node *root;
}
Tree;

Node *tree_find(Tree *, const int);
int tree_insert(Tree *, const int, const char *);
int tree_delete(Tree *, const int);

#endif