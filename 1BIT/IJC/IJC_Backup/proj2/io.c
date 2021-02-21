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
