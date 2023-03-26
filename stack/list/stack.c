#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

Stack *stack_create()
{
    Stack *stack = (Stack *) calloc(1, sizeof(Stack));

    return stack;
}

void stack_destroy(Stack *stack)
{
    Node *node = stack->top, *node_prev = NULL;
    while (node != NULL)
    {
        node_prev = node;
        node = node->next;
        free(node_prev);
    }
    free(stack);
}

int stack_push(Stack *stack, const int info)
{
    Node *new = (Node *) calloc(1, sizeof(Node));
    if (new == NULL)
        return 1;

    new->info = info;
    new->next = stack->top;

    stack->top = new;

    return 0;
}

int stack_pop(Stack *stack, int *info)
{
    if (stack->top == NULL)
        return 1;

    *info = stack->top->info;

    Node *top = stack->top;
    stack->top = top->next;
    free(top);

    return 0;
}

void stack_print(const Stack *stack)
{
    if (stack->top == NULL)
        return;

    Node *node = stack->top;
    while (node != NULL)
    {
        printf("%d ", node->info);
        node = node->next;
    }
    printf("\n");
}
