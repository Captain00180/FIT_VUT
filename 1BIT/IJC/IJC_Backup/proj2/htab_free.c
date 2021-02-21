#include "htab.h"

void htab_free(htab_t * t)     // destruktor tabulky
{

    if (t == NULL || t->arr_size == 0)
    {
        return;
    }

    htab_clear(t);

    free(t);
}