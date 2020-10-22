/******************************************************************
***         Reseni IJC-DU2, příklad 2), 9.4.2020                ***  
***         Autor: Filip Januška, FIT VUTBR                     ***  
***         Přeloženo: gcc 9.2.1 (Red Hat 9.2.1-1)              ***
******************************************************************/

#include "htab.h"


//find last item in hash table
htab_iterator_t htab_end(const htab_t * t)
{
    if ( t == NULL ||  htab_bucket_count(t) == 0)
    {
        fprintf(stderr, "error - htab_end: Invalid hash table\n");
        htab_iterator_t iterator;
        iterator.ptr = NULL;
        return iterator;
    }


    size_t index = htab_bucket_count(t) - 1;
    struct htab_item *ptr;

    for (; index >= 0; --index)
    {
        ptr = t->data[index];
        //find last item in last bucket
        if (ptr != NULL)
        {
            ptr = ptr->next;
            while (ptr != NULL)
            {
                ptr = ptr->next;
            }
            break;
        }
        if (index == 0)
        {
            break;
        }
    }
    htab_iterator_t iterator;
    iterator.ptr = ptr;
    iterator.t = t;
    iterator.idx = index;
    return iterator;
}

