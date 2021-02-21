#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#include "erastothenes.h"
#include "bitset.h"
#include "ppm.h"


int main()
{
	struct ppm *buffer = ppm_read("du1-obrazek.ppm");

	if (buffer == NULL)
	{
		exit(1);
	}

	printf("%d - %d\n", buffer->xsize, buffer->ysize);

/*	for (unsigned i = 0; i < ((buffer->xsize) * (buffer->ysize) * 3); ++i)
	{
		printf("%d ----  %d\n", i, buffer->data[i]);

	}
*/
	bitset_alloc(ppm_primes, 3 * buffer->xsize * buffer->ysize);

	Erastothenes(ppm_primes);

	bitset_alloc(message, bitset_size(ppm_primes));
	
	bitset_index_t counter = 0;
	for (bitset_index_t i = 23; i < bitset_size(ppm_primes); ++i)
	{
		if (!bitset_getbit(ppm_primes, i))
		{
			bitset_setbit(message, counter, (buffer->data[i]) & 1U);
			++counter;
		}
	}

	for (bitset_index_t j = 0; j < bitset_size(message); j += 7)
	{
		char c = (bitset_getbit(message, j ) << 0) |
			 (bitset_getbit(message, j + 1) << 1) |
			 (bitset_getbit(message, j + 2) << 2) |
			 (bitset_getbit(message, j + 3) << 3) |
			 (bitset_getbit(message, j + 4) << 4) |
			 (bitset_getbit(message, j + 5) << 5) |
			 (bitset_getbit(message, j + 6) << 6) |
			 (bitset_getbit(message, j + 7) << 7) ;
		printf("%c  ", c % 127);
		if (c == '\0')
		{

			printf("   %d ende\n", j);
			break;
		}
	}

	bitset_free(message);


	

/*	printf("ERAS------------\n\n\n");

	char message[bitset_size(ppm_primes)];
	message[0] = 0;
	message[1] = '\0';

	bitset_index_t index = 0;
	int counter = 0;
	for (bitset_index_t i = 22; i < bitset_size(ppm_primes); ++i)
	{
		if (!bitset_getbit(ppm_primes, i))
		{
			int least_sig_bit = (buffer->data[i] & 1);
			message[index] |= least_sig_bit << counter;
			counter ++;
		
			if (counter == 7)
			{
				counter = 0;
				index ++;
				message[index] = 0;
				message[index + 1] = '\0';
			}
		}
	}

	printf("SIZE----%d\n\n", strlen(message));
	for (int i = 0; i < strlen(message); ++i)
	{
		if(message[i] > -1)
			printf("%d - %c \n ",message[i],  message[i]);
	}
*/	
	bitset_free(ppm_primes);
} 
