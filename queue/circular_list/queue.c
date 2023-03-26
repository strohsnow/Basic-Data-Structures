#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

Queue *queue_create()
{
    Queue *queue = (Queue *) calloc(1, sizeof(Queue));

    return queue;
}

void queue_destroy(Queue *queue)
{
    if (queue->tail == NULL)
    {
        free(queue);
        return;
    }

    Node *node = queue->tail->next, *node_prev = NULL;
    while (node != queue->tail)
    {
        node_prev = node;
        node = node->next;
        free(node_prev);
    }
    free(node);
    free(queue);
}

int queue_push(Queue *queue, const int info)
{
    Node *new = (Node *) calloc(1, sizeof(Node));
    if (new == NULL)
        return 1;

    new->info = info;
    
    if (queue->tail == NULL)
        new->next = new;
    else
    {
        new->next = queue->tail->next;
        queue->tail->next = new;
    }

    queue->tail = new;

    return 0;
}

int queue_pop(Queue *queue, int *info)
{
    if (queue->tail == NULL)
        return 1;

    *info = queue->tail->next->info;

    if (queue->tail == queue->tail->next)
    {
        free(queue->tail);
        queue->tail = NULL;
    }
    else
    {
        Node *head = queue->tail->next;
        queue->tail->next = head->next;
        free(head);
    }

    return 0;
}

void queue_print(const Queue *queue)
{
    if (queue->tail == NULL)
        return;

    Node *node = queue->tail->next;
    do
    {
        printf("%d ", node->info);
        node = node->next;
    }
    while (node != queue->tail->next);
    printf("\n");
}
