#ifndef PPM_H
#define PPM_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
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
