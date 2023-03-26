#ifndef STACK_LIST_H
#define STACK_LIST_H

typedef struct Node
{
    int info;
    struct Node *next;
}
Node;

typedef struct Stack
{
    Node *top;
}
Stack;

Stack *stack_create();

void stack_destroy(Stack *);

int stack_push(Stack *, const int);

int stack_pop(Stack *, int *);

void stack_print(const Stack *);

#endif
