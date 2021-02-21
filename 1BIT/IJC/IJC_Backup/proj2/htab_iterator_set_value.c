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