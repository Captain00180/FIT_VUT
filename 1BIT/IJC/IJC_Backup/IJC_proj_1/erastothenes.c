/******************************************************************
***                      erastothenes.c                         ***  
***         Reseni IJC-DU1, příklad a), 15.3.2020               ***  
***         Autor: Filip Januška, FIT                           ***  
***         Přeloženo: gcc 9.2.1 (Red Hat 9.2.1-1)              ***
***         Popis souboru : Algoritmus "Eratostenovo sito" 	***
***	    pro nalezení prvočísel pomocí bitového pole	***
******************************************************************/
#include "erastothenes.h"

void Erastothenes(bitset_t pole)
{
	bitset_setbit(pole, 0, 1);
	bitset_setbit(pole, 1, 1);
	bitset_index_t max_size = sqrt(bitset_size(pole));
	bitset_index_t array_size = bitset_size(pole);

	for (bitset_index_t i = 2 ; i <= max_size; ++i)
	{
		//found a prime
		if (!bitset_getbit(pole, i))
		{
			//start at i^2 (all numbers less than i^2 have already been checked before)
			for (bitset_index_t j = i * i; j < array_size; j += i )
				{
					bitset_setbit(pole, j, 1);
				}
		}
	}
}			

