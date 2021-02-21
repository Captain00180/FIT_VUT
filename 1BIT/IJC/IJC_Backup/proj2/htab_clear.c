#include "htab.h"

//clears all hash table items
void htab_clear(htab_t * t)
{
    if (t == NULL || htab_bucket_count(t) == 0 || htab_size(t) == 0 )
    {
        return;
    }

    htab_iterator_t iterator = htab_begin(t);
    htab_iterator_t next_item;

    while(htab_iterator_valid(iterator))
    {
        next_item = htab_iterator_next(iterator);
        htab_erase(t, iterator);
        iterator = next_item;
    }

}
