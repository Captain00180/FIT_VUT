#ifndef HASH_STRUCT_H
#define HAST_STRUCT_H



struct htab_item
{
    const char * key;
    unsigned int value;
    struct htab_item *next;
};

struct htab    // neúplná deklarace struktury - uživatel nevidí obsah
{
    unsigned int size;
    unsigned int arr_size;
    struct htab_item *data[];
};

#endif