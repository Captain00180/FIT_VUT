/******************************************************************
***                      primes.c                               ***  
***         Reseni IJC-DU1, příklad a), 15.3.2020               ***  
***         Autor: Filip Januška, FIT                           ***  
***         Přeloženo: gcc 9.2.1 (Red Hat 9.2.1-1)              ***
***         Popis příkladu : Vytvořit program, který            *** 
***         využije bitové pole a Erastenovo sito pro výpis     ***
***         posledních 10 prvočísel menších než zadané číslo.   ***
******************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <limits.h>
#include <stdarg.h>
#include <time.h>

#ifndef USE_INLINE
#include "bitset.h" 
#endif


#include "erastothenes.h"
int main()
{
	clock_t start;
        start = clock();
		
	bitset_create(pole,500000000)
	Erastothenes(pole);

	bitset_index_t primes[10] = {0};
	
	int counter = 0;
	//Find last 10 prime numbers 
	for (bitset_index_t  i = bitset_size(pole) - 1; counter < 10; --i)
	{
		if (!bitset_getbit(pole, i))
			{
				primes[counter] = i;
				++counter;
			}
	}
	
	//print found primes in ascending order
	for (int i = 9; i >= 0; --i)
	{
		printf("%lu\n", primes[i]);
	}

	fprintf(stderr, "\nTime=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);
	
	return 0;
}
