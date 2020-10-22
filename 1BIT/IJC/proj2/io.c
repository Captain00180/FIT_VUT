/******************************************************************
***         Reseni IJC-DU2, příklad 2), 9.4.2020                ***  
***         Autor: Filip Januška, FIT VUTBR                     ***  
***         Přeloženo: gcc 9.2.1 (Red Hat 9.2.1-1)              ***
******************************************************************/

#include "io.h"

int get_word(char *s, int max, FILE *f)
{
    char c = fgetc(f);
    //fast forward to first non-space character
    while(isspace(c))
    {
        c = fgetc(f);
    }

    if (c == EOF)
    {
        return EOF;
    }

    int counter = 0;
    while(!isspace(c) && c != EOF && counter < (max - 1) )
    {

        s[counter++] = c;

        if (counter < (max - 1)) {
            c = fgetc(f);
        }

    }

    s[counter] = '\0';

    return strlen(s);
}
