/******************************************************************
***         Reseni IJC-DU2, příklad 2), 9.4.2020                ***  
***         Autor: Filip Januška, FIT VUTBR                     ***  
***         Přeloženo: gcc 9.2.1 (Red Hat 9.2.1-1)              ***
******************************************************************/

#include "htab.h"

htab_value_t htab_iterator_set_value(htab_iterator_t it, htab_value_t val)
{
    if (!htab_iterator_valid(it))
    {
        fprintf(stderr, "error - htab_iterator_set_value: Invalid iterator\n");
        return -42;
    }

    it.ptr->value = val;
    return it.ptr->value;

}
