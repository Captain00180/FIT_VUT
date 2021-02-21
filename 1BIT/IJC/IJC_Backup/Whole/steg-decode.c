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


		
	bitset_alloc(ppm_primes, 3 * (buffer->xsize) * (buffer->ysize));

	Erastothenes(ppm_primes);

	char c = 0;
	int counter = 0;
	for (bitset_index_t i = 23; i < bitset_size(ppm_primes); ++i)
	{
		if (!bitset_getbit(ppm_primes, i))
		{
			c |= ((buffer->data[i]) & 1U) << counter;
			++counter;
		}
		if (counter == CHAR_BIT)
		{
			if (c == '\0')
			{
				putchar('\n');
				break;
			}
			printf("%c", c);
			counter = 0;
			c = 0;
		}
	}


	bitset_free(ppm_primes);
	


/*
	printf("ERAS------------\n\n\n");
	bitset_alloc(ppm_primes, 3 * buffer->xsize * buffer->ysize);
	char message[bitset_size(ppm_primes)];
	message[0] = 0;
	message[1] = '\0';

	bitset_index_t index = 0;
	int counter = 0;
	for (bitset_index_t i = 22; i < bitset_size(ppm_primes); ++i)
	{
		if (!bitset_getbit(ppm_primes, i))
		{
			int least_sig_bit = (buffer->data[i] & 1U);
			message[index] |= (least_sig_bit << counter);
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
ZZ
	printf("SIZE----%d\n\n", strlen(message));
	for (size_t i = 0; i < strlen(message); ++i)
	{
	//	if(message[i] > -1)
			printf("%d : %d - %c \n ",i, message[i],  message[i]);
	}

	bitset_free(ppm_primes);


	*/
} 
