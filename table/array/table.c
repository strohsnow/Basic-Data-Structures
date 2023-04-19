#include <stdlib.h>
#include <string.h>
#include "table.h"

int table_find(const Table *table, const int key)
{
    for (int i = 0; i < table->msize; ++i)
        if (table->ks[i].busy && table->ks[i].key == key)
            return i;

    return -1;
}

int table_insert(Table *table, const int key, const char *info)
{
    if (table_find(table, key) >= 0)
        return DUPLICATE_KEY;

    if (table->msize >= table->csize)
    {
        table_garbage_collector(table);
        if (table->msize >= table->csize)
            return TABLE_OVERFLOW;
    }
    
    table->ks[table->csize].busy = 1;
    table->ks[table->csize].key = key;
    table->ks[table->csize].data = (Item *) malloc(sizeof(Item));
    table->ks[table->csize].data->info = strdup(info);

    ++table->csize;

    return OK;
}

int table_delete(Table *table, const int key)
{
    int i = table_find(table, key);
    if (i < 0)
        return KEY_NOT_FOUND;
    
    table->ks[i].busy = 0;

    return OK;
}

void table_garbage_collector(Table *table)
{
    int j = 0;
    for (int i = 0; i < table->csize; ++i)
    {
        if (table->ks[i].busy)
        {
            if (j == i)
            {
                ++j;
                continue;
            }

            table->ks[j].busy = 1;
            table->ks[j].key = table->ks[i].key;
            table->ks[j].data = (Item *) malloc(sizeof(Item));
            table->ks[j].data->info = strdup(table->ks[i].data->info);

            ++j;
        }

        table->ks[i].busy = 0;
        free(table->ks[i].data->info);
        free(table->ks[i].data);
        table->ks[i].data = NULL;
    }

    table->csize = j;
}