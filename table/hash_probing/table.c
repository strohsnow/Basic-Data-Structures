#include <stdlib.h>
#include <string.h>
#include "table.h"

int table_find(const Table *table, const int key)
{
    int i = hash_int(key) % table->msize, n = 0;
    while (n < table->msize && table->ks[i].busy != 0)
    {
        if (table->ks[i].busy == 1 && table->ks[i].key == key)
            return i;

        i = (i + 1) % table->msize;
        ++n;
    }
        
    return -1;
}

int table_insert(Table *table, const int key, const char *info)
{
    if (table_find(table, key) >= 0)
        return DUPLICATE_KEY;
    
    int i = hash_int(key) % table->msize, n = 0;
    while (n < table->msize && table->ks[i].busy == 1)
    {
        i = (i + 1) % table->msize;
        ++n;
    }

    if (n >= table->msize)
        return TABLE_OVERFLOW;

    table->ks[i].busy = 1;
    table->ks[i].key = key;
    table->ks[i].data = (Item *) malloc(sizeof(Item));
    table->ks[i].data->info = strdup(info);

    return OK;
}

int table_delete(Table *table, const int key)
{
    int i = table_find(table, key);
    if (i < 0)
        return KEY_NOT_FOUND;

    table->ks[i].busy = -1;
    free(table->ks[i].data->info);
    free(table->ks[i].data);

    return OK;
}