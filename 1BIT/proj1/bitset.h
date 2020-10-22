/******************************************************************
***                     bitset.h                                ***  
***         Reseni IJC-DU1, příklad a), 15.3.2020               ***  
***         Autor: Filip Januška, FIT                           ***  
***         Přeloženo: gcc 9.2.1 (Red Hat 9.2.1-1)              ***
***         Popis souboru : Knihovna definujíci funkce		***
***	    a makra pro práci s bitovími poli			***
******************************************************************/


#ifndef BITSET_H
#define BITSET_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include <math.h>
#include "error.h"



typedef unsigned long *bitset_t;

typedef unsigned long bitset_index_t;



#define UL_SIZE (sizeof(bitset_index_t) * CHAR_BIT)



#define bitset_create(jmeno_pole, velikost) do{bitset_index_t jmeno_pole[velikost / UL_SIZE + ((velikost % UL_SIZE) ? 2 : 1 )] = {[0] = velikost, 0};\
		static_assert (velikost > 1 && velikost < ULONG_MAX, "error: bitset_create Chybna velikost pole \n");} while(0)


#define bitset_alloc(jmeno_pole, velikost) do {\
    assert(velikost > 1 && velikost < ULONG_MAX);\
    bitset_index_t * jmeno_pole = malloc( (ceil( (long double) velikost / UL_SIZE + ((velikost % UL_SIZE) ? 2 : 1))) * sizeof(bitset_index_t));\
    if (jmeno_pole == NULL){\
        error_exit("bitset_alloc: Chyba pri alokaci pamati\n");\
    }\
    jmeno_pole[0] = velikost;\
    for (bitset_index_t i = 1; i < ceil( (long double) velikost / UL_SIZE + 1); ++i){\
        jmeno_pole[i] = 0;\
    }\
    }while (0)
\



#ifdef USE_INLINE

inline bitset_index_t bitset_size(bitset_t jmeno_pole)
{
	return jmeno_pole[0];
}

#else
#define bitset_size(jmeno_pole) jmeno_pole[0]

#endif


#ifdef USE_INLINE

inline void bitset_setbit(bitset_t jmeno_pole, bitset_index_t index, bool vyraz)
	{
	if (index >= bitset_size(jmeno_pole)){
		error_exit("bitset_setbit: Index %lu mimo rozsahu 0..%lu",
			       	(bitset_index_t) index, (bitset_index_t) bitset_size(jmeno_pole) - 1);
	}
	bitset_index_t insert = index % UL_SIZE;
	insert = 1L << insert;
	if (vyraz){
		jmeno_pole[1 +  index / UL_SIZE] |= insert;
	}
	else if(!vyraz){
		insert = ~insert;
		jmeno_pole[1 + index / UL_SIZE] &= insert;
	}
}
#else
#define bitset_setbit(jmeno_pole, index, vyraz) do{\
	if (index >= bitset_size(jmeno_pole)){\
		error_exit("bitset_setbit: Index %lu mimo rozsahu 0..%lu",\
			       	(bitset_index_t) index, (bitset_index_t) bitset_size(jmeno_pole) - 1);\
	}\
	bitset_index_t insert = index % UL_SIZE;\
	insert = 1L << insert;\
	if (vyraz){\
		jmeno_pole[1 +  index / UL_SIZE] |= insert;\
	}\
	else if(!vyraz){\
		insert = ~insert;\
		jmeno_pole[1 + index / UL_SIZE] &= insert;\
	}\
}while (0)

#endif


#ifdef USE_INLINE
inline int bitset_getbit(bitset_t jmeno_pole, bitset_index_t index)
	{
		return (index < bitset_size(jmeno_pole)) ? !!(jmeno_pole[1 + index/UL_SIZE] & 1L << (index % UL_SIZE))\
		: (error_exit("bitset_getbit: Index %lu mimo rozsahu 0..%lu", (bitset_index_t) index, (bitset_index_t) bitset_size(jmeno_pole) -1) , 0);
	}
#else
#define bitset_getbit(jmeno_pole,index)(\
	       	(index < bitset_size(jmeno_pole)) ? !!(jmeno_pole[1 + index/UL_SIZE] & 1L << (index % UL_SIZE))\
		: (error_exit("bitset_getbit: Index %lu mimo rozsahu 0..%lu", (bitset_index_t) index, (bitset_index_t) bitset_size(jmeno_pole) -1) , 0)\
		)\

#endif



#ifdef USE_INLINE
inline void bitset_free(bitset_t jmeno_pole)
	{
		free(jmeno_pole);
		jmeno_pole = NULL;
	}
#else
#define bitset_free(jmeno_pole)do{\
    free(jmeno_pole);\
    jmeno_pole = NULL;\
    }while(0)

#endif
#endif


