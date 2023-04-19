#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table.h"

int table_find(const Table *table, const int key)
{
    int start = 0, end = table->csize - 1;
    while (start <= end)
    {
        int middle = (start + end) / 2;
        
        if (table->ks[middle].key == key)
            return middle;

        if (table->ks[middle].key > key)
            end = middle - 1;
        else
            start = middle + 1;
    }

    return -1;
}

int table_insert(Table *table, const int key, const char *info)
{
    if (table_find(table, key) >= 0)
        return DUPLICATE_KEY;

    if (table->csize >= table->msize)
        return TABLE_OVERFLOW;

    int i = table->csize - 1;
    table->ks[i+1].data = (Item *) malloc(sizeof(Item));
    while (i >= 0 && table->ks[i].key > key)
    {
        table->ks[i+1].key = table->ks[i].key;
        table->ks[i+1].data->info = table->ks[i].data->info;

        --i;
    }

    table->ks[i+1].key = key;
    table->ks[i+1].data->info = strdup(info);

    ++table->csize;

    return OK;
}

int table_delete(Table *table, const int key)
{
    int i = table_find(table, key);
    if (i < 0)
        return KEY_NOT_FOUND;
    
    free(table->ks[i].data->info);
    while (i < table->csize - 1)
    {
        table->ks[i].key = table->ks[i+1].key;
        table->ks[i].data->info = table->ks[i+1].data->info;

        ++i;
    }
    free(table->ks[i].data);

    --table->csize;

    return OK;
}