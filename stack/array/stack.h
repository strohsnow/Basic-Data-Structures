#ifndef STACK_ARRAY_H
#define STACK_ARRAY_H

typedef struct Stack
{
    int top;
    int capacity;
    int *array;
}
Stack;

Stack *stack_create(const int);

void stack_destroy(Stack *);

int stack_push(Stack *, const int);

int stack_pop(Stack *, int *);

void stack_print(const Stack *);

#endif
