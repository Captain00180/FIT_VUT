/******************************************************************
***         Reseni IJC-DU2, příklad 2), 9.4.2020                ***  
***         Autor: Filip Januška, FIT VUTBR                     ***  
***         Přeloženo: gcc 9.2.1 (Red Hat 9.2.1-1)              ***
******************************************************************/

#include "htab.h"

//returns size of htab_item pointer array stored in hash table
size_t htab_bucket_count(const htab_t * t)
{
    if (t == NULL)
    {
        fprintf(stderr, "error - htab_bucket_count: Invalid hash table\n");
        return 0;
    }
    return t->arr_size;
}

