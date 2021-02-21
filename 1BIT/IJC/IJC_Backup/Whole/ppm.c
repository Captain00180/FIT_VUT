#include "ppm.h"

struct ppm * ppm_read(const char * filename)
{
	FILE *file = fopen(filename, "rb");
	if (file == NULL)
	{
		warning_msg("ppm_read: NAZOV Chyba pri cteni souboru \n");
		return NULL;
	}
	
	char ppm_fmt[10];
		
	fscanf(file, "%s",ppm_fmt);	//skip format specifier 'P6'
	


	unsigned xsize = 0;
	unsigned ysize = 0;

	fscanf(file, "%u", &xsize);
	fscanf(file, "%u", &ysize);

	if (xsize == 0 || ysize == 0)
	{	
		fclose(file);
		printf("%d : %d \n", xsize, ysize);
		warning_msg("ppm_read: SIZE Chyba pri cteni souboru \n");
		return NULL;
	}
	
	int RGB_max = 0;

	fscanf(file, "%d", &RGB_max);	//skip RGB max value specifier ('255' is implied)

	fgetc(file);			//skip newline before fread()
	struct ppm *buffer = malloc((2 * sizeof(unsigned)) + (3 * xsize * ysize));
	if (buffer == NULL)
	{
		fclose(file);
		error_exit("ppm_read: Chyba pri alokaci pamati \n");
	}

	fread(&buffer->data, sizeof(char), 3 * xsize * ysize, file);



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

