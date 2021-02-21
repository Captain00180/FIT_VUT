/******************************************************************
***                      ppm.c  	                        ***  
***         Reseni IJC-DU1, příklad b), 15.3.2020               ***  
***         Autor: Filip Januška, FIT                           ***  
***         Přeloženo: gcc 9.2.1 (Red Hat 9.2.1-1)              ***
***         Popis souboru : Modul definujíci funkce pro		***
***	    načtení dat ze souboru formátu .ppm (P6)		***
******************************************************************/
#include "ppm.h"

struct ppm * ppm_read(const char * filename)
{
	FILE *file = fopen(filename, "rb");
	

	if (file == NULL)
	{
		warning_msg("ppm_read: Chyba pri cteni souboru \n");
		return NULL;
	}
	
	char ppm_fmt[10];
			
	fscanf(file, "%s",ppm_fmt);	//format specifier - expect 'P6'
	if (strcmp(ppm_fmt, "P6") != 0)
	{
		fclose(file);
		warning_msg("ppm_read: Chyba formatu souboru \n");
	       	return NULL;
	}		       

	unsigned xsize = 0;
	unsigned ysize = 0;

	fscanf(file, "%u", &xsize);
	fscanf(file, "%u", &ysize);
	if (xsize == 0 || ysize == 0)
	{	
		fclose(file);
		warning_msg("ppm_read: Chyba pri cteni souboru \n");
		return NULL;
	}
	
	int RGB_max = 0;

	fscanf(file, "%d", &RGB_max);	// RGB max value specifier - expect '255'
	if (RGB_max != 255)
	{
		fclose(file);
		warning_msg("ppm_read: Chyba pri cteni souboru\n");
		return NULL;
	}
	fgetc(file);			//skip newline before fread()


	struct ppm *buffer = malloc((2 * sizeof(unsigned)) + (3 * xsize * ysize));
	if (buffer == NULL)
	{
		fclose(file);
		warning_msg("ppm_read: Chyba pri alokaci pamati \n");
		return NULL;
	}

	if( (fread(&buffer->data, sizeof(char), 3 * xsize * ysize, file)) != 3 * xsize * ysize)
	{
		fclose(file);
		ppm_free(buffer);
		warning_msg("ppm_read: Chyba pri cteni souboru\n");
		return NULL;
	}
	
	if (fgetc(file) != EOF)
	{
		error_exit("ppm_read: Chybny format souboru \n");
	}
	buffer->xsize = xsize;
	buffer->ysize = ysize;

	fclose(file);
	return buffer;
}


void ppm_free(struct ppm *p)
{
	free(p);
	p = NULL;
}

