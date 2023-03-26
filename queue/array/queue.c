#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

Queue *queue_create(const int capacity)
{
    Queue *queue = (Queue *) calloc(1, sizeof(Queue));

    queue->head = queue->tail = queue->size = 0;
    queue->capacity = capacity;

    queue->array = (int *) calloc(queue->capacity, sizeof(int));

    return queue;
}

void queue_destroy(Queue *queue)
{
    free(queue->array);
    free(queue);
}

int queue_push(Queue *queue, const int info)
{
    if (queue->size == queue->capacity)
        return 1;

    queue->array[queue->tail] = info;
    queue->tail = (queue->tail + 1) % queue->capacity;
    ++queue->size;

    return 0;
}

int queue_pop(Queue *queue, int *info)
{
    if (queue->size == 0)
        return 1;

    *info = queue->array[queue->head];
    queue->head = (queue->head + 1) % queue->capacity;
    --queue->size;

    return 0;
}

void queue_print(const Queue *queue)
{
    if (queue->size == 0)
        return;

    for (int i = queue->head, j = 0; j < queue->size; i = (i + 1) % queue->capacity, ++j)
        printf("%d ", queue->array[i]);
    printf("\n");
}
