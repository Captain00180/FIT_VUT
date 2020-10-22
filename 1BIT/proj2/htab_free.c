/******************************************************************
***         Reseni IJC-DU2, příklad 2), 9.4.2020                ***  
***         Autor: Filip Januška, FIT VUTBR                     ***  
***         Přeloženo: gcc 9.2.1 (Red Hat 9.2.1-1)              ***
******************************************************************/

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
