/******************************************************************
***                      error.h	                        ***  
***         Reseni IJC-DU1, příklad a), 15.3.2020               ***  
***         Autor: Filip Januška, FIT                           ***  
***         Přeloženo: gcc 9.2.1 (Red Hat 9.2.1-1)              ***
***         Popis souboru : Modul definujíci funkce pro	***
***	    hlášení chyb 					***
******************************************************************/
#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>


void warning_msg(const char *fmt, ...);

void error_exit(const char *fmt, ...);


#endif
