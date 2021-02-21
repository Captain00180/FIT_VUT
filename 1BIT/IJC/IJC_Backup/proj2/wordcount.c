#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "htab.h"

int main()
{

    // prime number large enough to work efficiently with large number of words
    // tested on /usr/share/dict/words and KJV Bible
    htab_t *hash_table = htab_init(40009);

    char string[128] = {0};
    int len = 0;
    int wrng_mssg = 0;

    while(1)
    {
        len = get_word(string, 128, stdin);
        if (len == EOF)
        {
            break;
        }

        if (len >= 127)
        {

            while (!isspace(fgetc(stdin)))
            {}
            if (!wrng_mssg)
            {
                fprintf(stderr, "warning: word longer than 127 characters.\n");
                wrng_mssg = 1;
            }
        }

        htab_lookup_add(hash_table, string);

    }


    //for each item in hash table
    htab_iterator_t iterator = htab_begin(hash_table);

    while(htab_iterator_valid(iterator))
    {
        printf("%s\t%d\n", htab_iterator_get_key(iterator), htab_iterator_get_value(iterator));
        iterator = htab_iterator_next(iterator);
    }

    htab_free(hash_table);


}
