#include <stdlib.h>
#include <string.h>
#include "table.h"

KeySpace *table_find(const Table *table, const int key)
{
    for (KeySpace *p = table->first; p != NULL; p = p->next)
        if (p->key == key)
            return p;

    return NULL;
}

int table_insert(Table *table, const int key, const char *info)
{
    if (table_find(table, key) != NULL)
        return DUPLICATE_KEY;

    KeySpace *new = (KeySpace *) malloc(sizeof(KeySpace));
    new->key = key;
    new->data = (Item *) malloc(sizeof(Item));
    new->data->info = strdup(info);
    
    new->next = table->first;
    table->first = new;

    return OK;
}

int table_delete(Table *table, const int key)
{
    KeySpace *ptr = table->first, *ptr_prev;
    while (ptr != NULL && ptr->key != key)
    {
        ptr_prev = ptr;
        ptr = ptr->next;
    }

    if (ptr == NULL)
        return KEY_NOT_FOUND;

    if (ptr == table->first)
        table->first = table->first->next;
    else
        ptr_prev->next = ptr->next;

    free(ptr->data->info);
    free(ptr->data);
    free(ptr);

    return OK;
}
