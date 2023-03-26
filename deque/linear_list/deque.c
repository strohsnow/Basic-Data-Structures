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
    Node *node = deque->head, *node_prev = NULL;
    while (node != NULL)
    {
        node_prev = node;
        node = node->next;
        free(node_prev);
    }
    free(deque);
}

int deque_push_front(Deque *deque, const int info)
{
    Node *new = (Node *) calloc(1, sizeof(Node));
    if (new == NULL)
        return 1;

    new->info = info;
    new->prev = NULL;

    if (deque->head == NULL)
        deque->head = deque->tail = new;
    else
    {
        new->next = deque->head;
        deque->head->prev = new;
        deque->head = new;
    }

    return 0;
}

int deque_push_back(Deque *deque, const int info)
{
    Node *new = (Node *) calloc(1, sizeof(Node));
    if (new == NULL)
        return 1;

    new->info = info;
    new->next = NULL;

    if (deque->head == NULL)
        deque->head = deque->tail = new;
    else
    {
        new->prev = deque->tail;
        deque->tail->next = new;
        deque->tail = new;
    }

    return 0;
}

int deque_pop_front(Deque *deque, int *info)
{
    if (deque->head == NULL)
        return 1;

    *info = deque->head->info;

    Node *head = deque->head;
    deque->head = head->next;
    free(head);

    if (deque->head == NULL)
        deque->tail = NULL;
    else
        deque->head->prev = NULL;

    return 0;
}

int deque_pop_back(Deque *deque, int *info)
{
    if (deque->head == NULL)
        return 1;

    *info = deque->tail->info;

    Node *tail = deque->tail;
    deque->tail = tail->prev;
    free(tail);

    if (deque->tail == NULL)
        deque->head = NULL;
    else
        deque->tail->next = NULL;

    return 0;
}

void deque_print(const Deque *deque)
{
    if (deque->head == NULL)
        return;

    Node *node = deque->head;
    while (node != NULL)
    {
        printf("%d ", node->info);
        node = node->next;
    }
    printf("\n");
}
