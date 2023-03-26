#ifndef QUEUE_ARRAY_H
#define QUEUE_ARRAY_H

typedef struct Queue
{
    int head, tail;
    int size, capacity;
    int *array;
}
Queue;

Queue *queue_create(const int);

void queue_destroy(Queue *);

int queue_push(Queue *, const int);

int queue_pop(Queue *, int *);

void queue_print(const Queue *);

#endif
