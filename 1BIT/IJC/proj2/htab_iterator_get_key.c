/******************************************************************
***         Reseni IJC-DU2, příklad 2), 9.4.2020                ***  
***         Autor: Filip Januška, FIT VUTBR                     ***  
***         Přeloženo: gcc 9.2.1 (Red Hat 9.2.1-1)              ***
******************************************************************/

#include "htab.h"

htab_key_t htab_iterator_get_key(htab_iterator_t it)
{
    if (!htab_iterator_valid(it))
    {
        fprintf(stderr, "error - htab_iterator_get_key: Invalid iterator\n");
        return NULL;
    }

    return it.ptr->key;

}
