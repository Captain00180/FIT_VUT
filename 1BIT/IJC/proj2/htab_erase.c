/******************************************************************
***         Reseni IJC-DU2, příklad 2), 9.4.2020                ***  
***         Autor: Filip Januška, FIT VUTBR                     ***  
***         Přeloženo: gcc 9.2.1 (Red Hat 9.2.1-1)              ***
******************************************************************/

#include "htab.h"

//erase item pointed on by iterator
void htab_erase(htab_t * t, htab_iterator_t it)
{
    if (t == NULL || !htab_iterator_valid(it) || t != it.t )
    {
        return;
    }

    //first item in bucket
    if(t->data[it.idx] == it.ptr)
    {
        t->data[it.idx] = it.ptr->next;

        free( (char *) htab_iterator_get_key(it));
        it.ptr->key = NULL;
        free(it.ptr);
        it.ptr = NULL;
    }

    else
    {
        //save pointer to the item being erased
        struct htab_item *cur_item = it.ptr;

        //move iterator to previous item
        it.ptr = t->data[it.idx];
        while(it.ptr->next != cur_item)
        {
            it = htab_iterator_next(it);
        }

        it.ptr->next = cur_item->next;

        free( (char *) htab_iterator_get_key(it));
        cur_item->key = NULL;
        free(cur_item);
        cur_item = NULL;

    }

    t->size -= 1;

}
