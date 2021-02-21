#include "htab.h"

// move iterator to first item in hash table
htab_iterator_t htab_begin(const htab_t * t)
{
    if (t == NULL || htab_bucket_count(t) == 0 )
    {
        fprintf(stderr, "error - htab_begin: Invalid hash table\n");
        htab_iterator_t iterator;
        iterator.ptr = NULL;
        return iterator;
    }

    size_t arr_size = htab_bucket_count(t);
    struct htab_item *ptr;
    size_t index = 0;

    for (; index < arr_size; ++index)
    {
        ptr = t->data[index];
        if (ptr != NULL)
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
