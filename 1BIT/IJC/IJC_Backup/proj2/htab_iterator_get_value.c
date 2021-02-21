#include "htab.h"


htab_value_t htab_iterator_get_value(htab_iterator_t it)
{
    if (!htab_iterator_valid(it))
    {
        fprintf(stderr, "error - htab_iterator_get_value: Invalid iterator\n");
        return -42;
    }

    return it.ptr->value;


}