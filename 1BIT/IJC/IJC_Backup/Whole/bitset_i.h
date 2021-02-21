#ifndef BITSET_H
#define BITSET_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include <math.h>


typedef unsigned long *bitset_t;

typedef unsigned long bitset_index_t;


void error_exit(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);
	exit(1);
}

#define UL_SIZE (sizeof(bitset_index_t) * CHAR_BIT)



#define bitset_create(jmeno_pole, velikost) bitset_index_t jmeno_pole[velikost / UL_SIZE + ((velikost % UL_SIZE) ? 2 : 1 )] = {[0] = velikost, 0};\
		static_assert (velikost > 1, "error: bitset_create Velikost pole mus byt vetsi nez 1\n");\


#define bitset_alloc(jmeno_pole, velikost)\
	static_assert(velikost > 1,  "error: bitset_alloc Velikost pole musi byt vetsi nez 1\n");\
	assert(velikost < ULONG_MAX);\
	bitset_index_t size = ceil( (long double) velikost / UL_SIZE + 1);\
	bitset_index_t * jmeno_pole = malloc(size * sizeof(bitset_index_t));\
	if (jmeno_pole == NULL){\
		fprintf(stderr, "bitset_alloc: Chyba alokace pameti");\
		return 1;\
	}\
	jmeno_pole[0] = velikost;\
	for (bitset_index_t i = 1; i < size; ++i){\
		jmeno_pole[i] = 0;\
	}\

#define bitset_free(jmeno_pole)\
	free(jmeno_pole);\
	jmeno_pole = NULL;\

#define bitset_size(jmeno_pole) jmeno_pole[0]

#define bitset_setbit(jmeno_pole, index, vyraz){\
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
}\



#define bitset_getbit(jmeno_pole, index) (\
	       	(index < bitset_size(jmeno_pole)) ? (jmeno_pole[1 + index/UL_SIZE] & 1L << (index % UL_SIZE))\
		: (error_exit("bitset_getbit: Index %lu mimo rozsahu 0..%lu", (bitset_index_t) index, (bitset_index_t) bitset_size(jmeno_pole) -1) , 0)\
		)\

#endif


