#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "htab.h"

#include <assert.h>
int main()
{

    // prime number large enough to work efficiently with large number of words
    // tested on /usr/share/dict/words and KJV Bible
    htab_t *hash_table = htab_init(40009);
    if (hash_table == NULL)
    {
        fprintf(stderr, "error: while allocating memory\n");
        return 1;
    }

    char string[128] = {0};
    int len = 0;
    int wrng_mssg = 0;

    //fill hash table with words from stdin
    while(1)
    {
        len = get_word(string, 128, stdin);
        if (len == EOF)
        {
            break;
        }
        //word overflow
        if (len >= 127)
        {
            //skip to the next whitespace marking end of the current word
            while (!isspace(fgetc(stdin)))
            {}
            if (!wrng_mssg)
            {
                fprintf(stderr, "warning: word longer than 127 characters.\n");
                wrng_mssg = 1;
            }
        }

        htab_iterator_t iterator = htab_lookup_add(hash_table, string);
        if (!htab_iterator_valid(iterator))
        {
            return 1;
        }
    }




    htab_iterator_t iterator = htab_begin(hash_table);

    //print each item in hash table
    while(htab_iterator_valid(iterator))
    {
        printf("%s\t%d\n", htab_iterator_get_key(iterator), htab_iterator_get_value(iterator));
        iterator = htab_iterator_next(iterator);
    }

    htab_free(hash_table);
    return 0;
}
