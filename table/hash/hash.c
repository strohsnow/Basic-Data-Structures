#include <stdlib.h>
#include <string.h>
#include <limits.h>

int hash_int(const int key)
{
    int hash = INT_MAX;
    for (int i = 0; i < sizeof(key); ++i)
        hash = 37 * hash + ((key >> 8 * i) & 0xff);

    return abs(hash);
}

int hash_str(const char *key)
{
    int hash = INT_MAX;
    for (int i = 0; i < strlen(key); ++i)
        hash = 37 * hash + key[i];

    return abs(hash);
}