/******************************************************************
***         Reseni IJC-DU2, příklad 2), 9.4.2020                ***  
***         Autor: Filip Januška, FIT VUTBR                     ***  
***         Přeloženo: gcc 9.2.1 (Red Hat 9.2.1-1)              ***
******************************************************************/

#include "htab.h"

//find item in array
htab_iterator_t htab_find(htab_t * t, htab_key_t key)
{
    if (t == NULL || htab_bucket_count(t) == 0)
    {
        fprintf(stderr, "error - htab_find: Invalid hash table\n");
        htab_iterator_t iterator;
        iterator.ptr = NULL;
        return iterator;
    }
        if (key == NULL || t->size == 0)
    {
        return htab_end(t);
    }

    htab_iterator_t iterator;
    iterator.t = t;
    size_t array_size = htab_bucket_count(t);
    size_t index = (htab_hash_fun(key) % array_size);


    //iterate through the bucket with corresponding index
    if (t->data[index] != NULL)
    {
        iterator.ptr = t->data[index];
        iterator.idx = index;

        while(htab_iterator_valid(iterator) && iterator.idx == index)
        {

            //found
            if (strcmp(key, htab_iterator_get_key(iterator)) == 0)
            {
                htab_iterator_set_value(iterator, (htab_iterator_get_value(iterator) + 1) ) ;
                return iterator;
            }
            iterator = htab_iterator_next(iterator);
        }

    }

    //not found
    iterator = htab_end(t);
    return iterator;


}
