/******************************************************************
***                      steg-decode.c	                        ***  
***         Reseni IJC-DU1, příklad b), 15.3.2020               ***  
***         Autor: Filip Januška, FIT                           ***  
***         Přeloženo: gcc 9.2.1 (Red Hat 9.2.1-1)              ***
***         Popis souboru : Program pro načtení dat 		***
***	    ze souboru formátu .ppm (P6) a nalezení 		***
***	    skryté zprávy zakódované v souboru			***
******************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#include "erastothenes.h"
#include "bitset.h"
#include "ppm.h"


int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		error_exit("Chybne argumenty programu\n");
	}
	struct ppm *buffer = ppm_read(argv[1]);

	if (buffer == NULL)
	{
		error_exit("Exiting program...\n");
	}
	
	bitset_alloc(ppm_primes, 3 * (buffer->xsize) * (buffer->ysize));
	Erastothenes(ppm_primes);

	char c = 0;
	int counter = 0;
	int ls_bit = 0;
	bool null_char = false;
	for (bitset_index_t i = 23; i < bitset_size(ppm_primes); ++i)
	{
		
		if (!bitset_getbit(ppm_primes, i))
		{
			ls_bit = buffer->data[i] & 1U;
			c |= ls_bit << counter;
			++counter;
		}
		if (counter == CHAR_BIT)
		{
			if (c == '\0')
			{
				printf("\n");
				null_char = true;
				break;
			}
			printf("%c", c);
			counter = 0;
			c = 0;
		}
	}
	if (!null_char)
	{
		bitset_free(ppm_primes);
		ppm_free(buffer);
		error_exit("error: Chybny format souboru\n");
	}
	bitset_free(ppm_primes);
	ppm_free(buffer);
} 
