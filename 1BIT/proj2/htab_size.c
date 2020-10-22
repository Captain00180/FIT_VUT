/******************************************************************
***         Reseni IJC-DU2, příklad 2), 9.4.2020                ***  
***         Autor: Filip Januška, FIT VUTBR                     ***  
***         Přeloženo: gcc 9.2.1 (Red Hat 9.2.1-1)              ***
******************************************************************/

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
