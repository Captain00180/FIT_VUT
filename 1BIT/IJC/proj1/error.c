/******************************************************************
***                      error.c	                        ***  
***         Reseni IJC-DU1, příklad a), 15.3.2020               ***  
***         Autor: Filip Januška, FIT                           ***  
***         Přeloženo: gcc 9.2.1 (Red Hat 9.2.1-1)              ***
***         Popis souboru : Modul definujíci funkce pro	***
***	    hlášení chyb 					***
******************************************************************/
#include "error.h"

void warning_msg(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);
}


void error_exit(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);
	exit(1);
}

