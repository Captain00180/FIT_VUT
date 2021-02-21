/******************************************************************
***                      ppm.h  	                        ***  
***         Reseni IJC-DU1, příklad b), 15.3.2020               ***  
***         Autor: Filip Januška, FIT                           ***  
***         Přeloženo: gcc 9.2.1 (Red Hat 9.2.1-1)              ***
***         Popis souboru : Modul definujíci funkce pro  	***
***	    načtení dat ze souboru formátu .ppm (P6)		***
******************************************************************/
#ifndef PPM_H
#define PPM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bitset.h"
#include "error.h"


struct ppm {
        unsigned xsize;
        unsigned ysize;
        char data[];    
     };

struct ppm * ppm_read(const char * filename);

void ppm_free(struct ppm *p);


#endif
