#include "erastothenes.h"

void Erastothenes(bitset_t pole)
{
	bitset_setbit(pole, 0, 1);
	bitset_setbit(pole, 1, 1);
	bitset_index_t max_size = sqrt(bitset_size(pole));
	bitset_index_t array_size = bitset_size(pole);

	

	for (bitset_index_t i = 2 ; i <= max_size; ++i)
	{
		
		if (!bitset_getbit(pole, i))
		{
			for (bitset_index_t j = i * i; j < array_size; j += i )
				{
					bitset_setbit(pole, j, 1);
				}
		}
	}
}			

