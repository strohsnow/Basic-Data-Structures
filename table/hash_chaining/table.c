#include <stdlib.h>
#include <string.h>
#include "table.h"

KeySpace *table_find(const Table *table, const int key)
{
    int i = hash_int(key) % table->msize;
    for (KeySpace *p = table->ks[i]; p != NULL; p = p->next)
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

    int i = hash_int(key) % table->msize;
    new->next = table->ks[i];
    table->ks[i] = new;

    return OK;
}

int table_delete(Table *table, const int key)
{
    int i = hash_int(key) % table->msize;
    KeySpace *ptr = table->ks[i], *ptr_prev;
    while (ptr != NULL && ptr->key != key)
    {
        ptr_prev = ptr;
        ptr = ptr->next;
    }

    if (ptr == NULL)
        return KEY_NOT_FOUND;

    if (ptr == table->ks[i])
        table->ks[i] = table->ks[i]->next;
    else
        ptr_prev->next = ptr->next;

    free(ptr->data->info);
    free(ptr->data);
    free(ptr);

    return OK;
}