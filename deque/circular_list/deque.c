#include <stdio.h>
#include <stdlib.h>
#include "deque.h"

Deque *deque_create()
{
    Deque *deque = (Deque *) calloc(1, sizeof(Deque));

    return deque;
}

void deque_destroy(Deque *deque)
{
    if (deque->tail == NULL)
    {
        free(deque);
        return;
    }

    Node *node = deque->tail->next, *node_prev = NULL;
    while (node != deque->tail)
    {
        node_prev = node;
        node = node->next;
        free(node_prev);
    }
    free(node);
    free(deque);
}

int deque_push_front(Deque *deque, const int info)
{
    Node *new = (Node *) calloc(1, sizeof(Node));
    if (new == NULL)
        return 1;

    new->info = info;
    
    if (deque->tail == NULL)
    {
        new->prev = new;
        new->next = new;
        deque->tail = new;
    }
    else
    {
        new->prev = deque->tail;
        new->next = deque->tail->next;
        deque->tail->next->prev = new;
        deque->tail->next = new;
    }

    return 0;
}

int deque_push_back(Deque *deque, const int info)
{
    Node *new = (Node *) calloc(1, sizeof(Node));
    if (new == NULL)
        return 1;

    new->info = info;
    
    if (deque->tail == NULL)
    {
        new->prev = new;
        new->next = new;
    }
    else
    {
        new->prev = deque->tail;
        new->next = deque->tail->next;
        deque->tail->next->prev = new;
        deque->tail->next = new;
    }

    deque->tail = new;

    return 0;
}

int deque_pop_front(Deque *deque, int *info)
{
    if (deque->tail == NULL)
        return 1;

    *info = deque->tail->next->info;

    if (deque->tail == deque->tail->next)
    {
        free(deque->tail);
        deque->tail = NULL;
    }
    else
    {
        Node *head = deque->tail->next;
        head->next->prev = deque->tail;
        deque->tail->next = head->next;
        free(head);
    }

    return 0;
}

int deque_pop_back(Deque *deque, int *info)
{
    if (deque->tail == NULL)
        return 1;

    *info = deque->tail->info;

    if (deque->tail == deque->tail->next)
    {
        free(deque->tail);
        deque->tail = NULL;
    }
    else
    {
        Node *tail = deque->tail;
        deque->tail = tail->prev;
        deque->tail->next = tail->next;
        deque->tail->next->prev = deque->tail;
        free(tail);
    }

    return 0;
}

void deque_print(const Deque *deque)
{
    if (deque->tail == NULL)
        return;

    Node *node = deque->tail->next;
    do
    {
        printf("%d ", node->info);
        node = node->next;
    }
    while (node != deque->tail->next);
    printf("\n");
}
