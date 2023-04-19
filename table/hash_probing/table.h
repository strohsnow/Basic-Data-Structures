#ifndef TABLE_H
#define TABLE_H

#include "../hash/hash.h"

enum TableErrors
{
    OK,
    DUPLICATE_KEY,
    KEY_NOT_FOUND,
    TABLE_OVERFLOW
};

typedef struct Item
{
    char *info;
}
Item;

typedef struct KeySpace
{
    int busy;
    int key;
    Item *data;
}
KeySpace;

typedef struct Table
{
    KeySpace *ks;
    int msize;
}
Table;

int table_find(const Table *, const int);
int table_insert(Table *, const int, const char *);
int table_delete(Table *, const int);

#endif