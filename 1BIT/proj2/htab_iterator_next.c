/******************************************************************
***         Reseni IJC-DU2, příklad 2), 9.4.2020                ***  
***         Autor: Filip Januška, FIT VUTBR                     ***  
***         Přeloženo: gcc 9.2.1 (Red Hat 9.2.1-1)              ***
******************************************************************/

#include "htab.h"


//find next valid item in hash table
htab_iterator_t htab_iterator_next(htab_iterator_t it)
{
    if (it.t == NULL)
    {
        fprintf(stderr, "error - htab_iterator_next; Invalid hash table inside iterator\n");
        htab_iterator_t iterator;
        iterator.ptr = NULL;
        return iterator;
    }

    struct htab_item *ptr = it.ptr;
    size_t index = it.idx;

    if (ptr != NULL)
    {
        ptr = ptr->next;
    }

    while(ptr == NULL)
    {
        ++index;
        if (index >= htab_bucket_count(it.t))
        {
            return htab_end(it.t);
        }

        ptr = it.t->data[index];
    }



    it.ptr = ptr;
    it.idx = index;

    return it;

}
