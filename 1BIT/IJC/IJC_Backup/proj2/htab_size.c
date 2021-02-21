#include "htab.h"

size_t htab_size(const htab_t * t)             // počet záznamů v tabulce
{
    if (t == NULL)
    {
        fprintf(stderr, "error - htab_size: Invalid hash table\n");
        return 0;
    }
    return t->size;
}
