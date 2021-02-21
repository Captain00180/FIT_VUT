#include <stdio.h>
#include <stdlib.h>
#include <string.h>




int main(int argc, char *argv[]){

    if(argc < 2)
    {
        return 0;
    }

    int b_delim = 0;

    if(strcmp(argv[1], "-d") == 0)
    {
        if(argc < 3)
        {
            return 1;
        }
        b_delim = 1;
    }

    if(argc < 4)
    {
        return 0;
    }

    //Parse the command

    if(strcmp(argv[3], "irow") == 0)
    {
        printf("irow\n");
    }




}
