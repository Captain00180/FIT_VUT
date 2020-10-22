/******************************************************************
***                     bitset.c                                ***  
***         Reseni IJC-DU1, příklad a), 15.3.2020               ***  
***         Autor: Filip Januška, FIT                           ***  
***         Přeloženo: gcc 9.2.1 (Red Hat 9.2.1-1)              ***
***         Popis souboru : Knihovna definujíci 		***
***	    inline funkce pro práci s bitovími poli		***`
******************************************************************/


#include "bitset.h"
#ifdef USE_INLINE
extern inline bitset_index_t bitset_size(bitset_t jmeno_pole);
extern inline void bitset_free(bitset_t jmeno_pole);
extern inline void bitset_setbit(bitset_t jmeno_pole, bitset_index_t index, bool vyraz);
extern inline int bitset_getbit(bitset_t jmeno_pole, bitset_index_t index);
#endif
