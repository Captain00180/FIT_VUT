/******************************************************************
***         Reseni IJC-DU2, příklad 2), 9.4.2020                ***  
***         Autor: Filip Januška, FIT VUTBR                     ***  
***         Přeloženo: gcc 9.2.1 (Red Hat 9.2.1-1)              ***
******************************************************************/

#include <stdlib.h>
#include "htab.h"

htab_t *htab_init(size_t n)         // konstruktor tabulky
{
    htab_t *ptr = malloc(sizeof(struct htab) + sizeof(struct htab_item *) * n);

    if (ptr == NULL){
        return ptr;
    }

    for (size_t i = 0; i < n; ++i )
    {
        ptr->data[i] = NULL;
    }
    ptr->size = 0;
    ptr->arr_size = n;
    return ptr;

}
