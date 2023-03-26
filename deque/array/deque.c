#include <stdio.h>
#include <stdlib.h>
#include "deque.h"

Deque *deque_create(const int capacity)
{
    Deque *deque = (Deque *) calloc(1, sizeof(Deque));

    deque->head = deque->tail = deque->size = 0;
    deque->capacity = capacity;

    deque->array = (int *) calloc(deque->capacity, sizeof(int));

    return deque;
}

void deque_destroy(Deque *deque)
{
    free(deque->array);
    free(deque);
}

int deque_push_front(Deque *deque, const int info)
{
    if (deque->size == deque->capacity)
        return 1;

    if (deque->size != 0)
    {
        if (deque->head == 0)
            deque->head = deque->capacity - 1;
        else
            --deque->head;
    }

    deque->array[deque->head] = info;
    ++deque->size;

    return 0;
}

int deque_push_back(Deque *deque, const int info)
{
    if (deque->size == deque->capacity)
        return 1;

    if (deque->size != 0)
    {
        if (deque->tail == deque->capacity - 1)
            deque->tail = 0;
        else
            ++deque->tail;
    }

    deque->array[deque->tail] = info;
    ++deque->size;

    return 0;
}

int deque_pop_front(Deque *deque, int *info)
{
    if (deque->size == 0)
        return 1;

    *info = deque->array[deque->head];

    if (deque->head != deque->tail)
    {
        if (deque->head == deque->capacity - 1)
            deque->head = 0;
        else
            ++deque->head;
    }

    --deque->size;

    return 0;
}

int deque_pop_back(Deque *deque, int *info)
{
    if (deque->size == 0)
        return 1;

    *info = deque->array[deque->tail];

    if (deque->head != deque->tail)
    {
        if (deque->tail == 0)
            deque->tail = deque->capacity - 1;
        else
            --deque->tail;
    }

    --deque->size;

    return 0;
}

void deque_print(const Deque *deque)
{
    if (deque->size == 0)
        return;

    for (int i = deque->head, j = 0; j < deque->size; i = (i + 1) % deque->capacity, ++j)
        printf("%d ", deque->array[i]);
    printf("\n");
}
