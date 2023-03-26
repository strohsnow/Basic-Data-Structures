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
    Node *node = queue->head, *node_prev = NULL;
    while (node != NULL)
    {
        node_prev = node;
        node = node->next;
        free(node_prev);
    }
    free(queue);
}

int queue_push(Queue *queue, const int info)
{
    Node *new = (Node *) calloc(1, sizeof(Node));
    if (new == NULL)
        return 1;

    new->info = info;
    new->next = NULL;

    if (queue->head == NULL)
        queue->head = new;
    else
        queue->tail->next = new;

    queue->tail = new;

    return 0;
}

int queue_pop(Queue *queue, int *info)
{
    if (queue->head == NULL)
        return 1;

    *info = queue->head->info;

    Node *head = queue->head;
    queue->head = head->next;
    free(head);

    if (queue->head == NULL)
        queue->tail = NULL;

    return 0;
}

void queue_print(const Queue *queue)
{
    if (queue->head == NULL)
        return;

    Node *node = queue->head;
    while (node != NULL)
    {
        printf("%d ", node->info);
        node = node->next;
    }
    printf("\n");
}
