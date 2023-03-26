#ifndef DEQUE_CIRCULAR_LIST_H
#define DEQUE_CIRCULAR_LIST_H

typedef struct Node
{
    int info;
    struct Node *prev, *next;
}
Node;

typedef struct Deque
{
    Node *tail;
}
Deque;

Deque *deque_create();

void deque_destroy(Deque *);

int deque_push_front(Deque *, const int);

int deque_push_back(Deque *, const int);

int deque_pop_front(Deque *, int *);

int deque_pop_back(Deque *, int *);

void deque_print(const Deque *);

#endif
