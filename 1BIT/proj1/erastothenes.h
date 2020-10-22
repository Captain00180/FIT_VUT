/******************************************************************
***                      erastothenes.h                         ***  
***         Reseni IJC-DU1, příklad a), 15.3.2020               ***  
***         Autor: Filip Januška, FIT                           ***  
***         Přeloženo: gcc 9.2.1 (Red Hat 9.2.1-1)              ***
***         Popis souboru : Algoritmus "Eratostenovo sito" 	***
***	    pro nalezení prvočísel pomocí bitového pole	***
******************************************************************/
#ifndef ERAS_H
#define ERAS_H

#include <stdio.h>
#include <stdlib.h>

#include "bitset.h"


void Erastothenes(bitset_t pole);

#endif
