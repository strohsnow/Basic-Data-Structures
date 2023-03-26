#ifndef QUEUE_CIRCULAR_LIST_H
#define QUEUE_CIRCULAR_LIST_H

typedef struct Node
{
    int info;
    struct Node *next;
}
Node;

typedef struct Queue
{
    Node *tail;
}
Queue;

Queue *queue_create();

void queue_destroy(Queue *);

int queue_push(Queue *, const int);

int queue_pop(Queue *, int *);

void queue_print(const Queue *);

#endif
