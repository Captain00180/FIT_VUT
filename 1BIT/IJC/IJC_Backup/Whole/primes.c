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

#ifdef USE_INLINE
#include "bitset_i.h"
#endif


#include "erastothenes.h"
#include "ppm.h"

int main()
{
	clock_t start;
        start = clock();
	
	
	bitset_alloc(pole, 500000000);
	assert(pole[0] == 500000000);



	Erastothenes(pole);

	bitset_index_t prime_indices[10] = {0};
/*	
	int counter = 0;
	for (bitset_index_t  i = bitset_size(pole) - 1; counter < 10; --i)
	{
		if (!bitset_getbit(pole, i))
			{
				prime_indices[counter] = i;
				++counter;
			}
	}

	for (int i = 9; i >= 0; --i)
	{
		printf("%lu\n", prime_indices[i]);
	}

*/

	int counter = 0;
	for (bitset_index_t i = 0; i < bitset_size(pole) ; ++i)
	{
		if (!bitset_getbit(pole, i))
		{
			++counter;
		}
	}

	printf("SIZE --- %d \n\n\n", counter);

	fprintf(stderr, "\nTime=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);
	free(pole);


	return 0;
}
