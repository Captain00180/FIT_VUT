/******************************************************************
***         Reseni IJC-DU2, příklad 2), 9.4.2020                ***  
***         Autor: Filip Januška, FIT VUTBR                     ***  
***         Přeloženo: gcc 9.2.1 (Red Hat 9.2.1-1)              ***
******************************************************************/

#include "htab.h"

//finds item in hash table. If not found, adds it to the hash table
htab_iterator_t htab_lookup_add(htab_t * t, htab_key_t key)
{

    if (t == NULL || htab_bucket_count(t) == 0)
    {
        fprintf(stderr, "error - htab_lookup_add: Invalid hash table\n");
        return htab_end(t);
    }

    htab_iterator_t iterator = htab_find(t, key);
    //found
    if (iterator.ptr != NULL)
    {
        return iterator;
    }

    //not found, add new item
    else
    {
        size_t key_len = strlen(key);
        size_t idx = (htab_hash_fun(key) % htab_bucket_count(t));
        char *new_str = malloc( (key_len + 1) * sizeof(char));
        //failed malloc
        if (new_str == NULL)
        {
            return htab_end(t);
        }

        strcpy(new_str, key);
        new_str[key_len] = '\0';

        struct htab_item *temp = t->data[idx];      //save pointer to current first element of the bucket
        struct htab_item *new = malloc(sizeof(struct htab_item));
        //failed malloc
        if (new == NULL)
        {
            return htab_end(t);
        }
        new->key = new_str;
        new->value = 1;
        new->next = temp;
        t->data[idx] = new;     //replace the first element

        iterator.idx = idx;
        iterator.t = t;
        iterator.ptr = new;

        t->size += 1;

        return iterator;
    }


}
