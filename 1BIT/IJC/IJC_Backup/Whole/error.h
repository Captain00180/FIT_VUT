#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>


void warning_msg(const char *fmt, ...);

void error_exit(const char *fmt, ...);


#endif
