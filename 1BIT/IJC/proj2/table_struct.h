/******************************************************************
***         Reseni IJC-DU2, příklad 2), 9.4.2020                ***  
***         Autor: Filip Januška, FIT VUTBR                     ***  
***         Přeloženo: gcc 9.2.1 (Red Hat 9.2.1-1)              ***
******************************************************************/

#ifndef HASH_STRUCT_H
#define HAST_STRUCT_H



struct htab_item
{
    const char * key;
    int value;
    struct htab_item *next;
};

struct htab    // neúplná deklarace struktury - uživatel nevidí obsah
{
    unsigned int size;
    unsigned int arr_size;
    struct htab_item *data[];
};

#endif
