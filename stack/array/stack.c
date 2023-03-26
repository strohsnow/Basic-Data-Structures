#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

Stack *stack_create(const int capacity)
{
    Stack *stack = (Stack *) calloc(1, sizeof(Stack));

    stack->capacity = capacity;
    stack->top = 0;
    stack->array = (int *) calloc(stack->capacity, sizeof(int));

    return stack;
}

void stack_destroy(Stack *stack)
{
    free(stack->array);
    free(stack);
}

int stack_push(Stack *stack, const int info)
{
    if (stack->top == stack->capacity)
        return 1;

    stack->array[stack->top++] = info;

    return 0;
}

int stack_pop(Stack *stack, int *info)
{
    if (stack->top == 0)
        return 1;

    *info = stack->array[--stack->top];

    return 0;
}

void stack_print(const Stack *stack)
{
    if (stack->top == 0)
        return;

    for (int i = 0; i < stack->top; ++i)
        printf("%d ", stack->array[i]);
    printf("\n");
}
