/******************************************************************
***         Reseni IJC-DU2, příklad 1), 9.4.2020                ***  
***         Autor: Filip Januška, FIT VUTBR                     ***  
***         Přeloženo: gcc 9.2.1 (Red Hat 9.2.1-1)              ***
******************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

long int NumOfLines(FILE *file);

int main(int argc, char *argv[])
{
	//start counting from beginning or end - 1=end, 0=beginning
	int start_from = 1;
	FILE *file = stdin;	
	long int print_from = 10;
	int over_limit = 0;

	if ( argc > 4)
	{
		fprintf(stderr, "error: invalid arguments\n");
		return 1;
	}
	
	//process program options, if some given
	for (int i = 1; i < argc; ++i)
	{
		//option -n
		if ( (strcmp(argv[i], "-n") == 0) )
		{
			++i;
			//no argument after -n
			if( argc <= i )
			{
				fprintf(stderr, "error: '-n' option requires a valid integer argument\n");
				return 1;
			}

			int offset = 0;

			if ( argv[i][0] == '+' || argv[i][0] == '-')
			{
				if (argv[i][0] == '+')
				{
					start_from = 0;
				}
				
				offset = 1;	
			}
	
			for (size_t j = offset; j < strlen(argv[i]) ; ++j)
			{
				if (!isdigit(argv[i][j]))
				{
					fprintf(stderr, "error: '%s' is not a valid positive integer\n", argv[i]);
					return 1;
				}
			}

			char * temp_lines = malloc( sizeof(char) * (strlen(argv[i]) - offset) );
			if (temp_lines == NULL)
			{
				fprintf(stderr, "malloc error\n");
				return 1;
			}

			memmove(temp_lines, (argv[i]+offset), (strlen(argv[i]) - offset) );

			//number after -n without '+' or '-'
			print_from = strtol(temp_lines, NULL, 10);
			free(temp_lines);
			if (print_from == 0)
			{
				fprintf(stderr, "error: number following '-n' must be greater than 0\n");
				return 1;
			}

		}
		else
		{
			file = fopen(argv[i], "r");
			if ( file == NULL)
			{
				fprintf(stderr, "error: '%s' is not a valid filename\n", argv[i]);
				return 1;
			}
		}
	}
	
	long int n_lines = NumOfLines(file);
	
	char line[1024];
	long int line_index = 0;

	while(fgets(line, 1024, file) != NULL)
	{
		
		++line_index;
		//start_from == 0 -> count from beginning
		if (!start_from)
		{
			if (line_index >= print_from)
			{
				printf("%s", line);
			}

		}
		//start_from == 1 -> count from end
		else if (start_from)
		{
			if (n_lines - line_index < print_from)
			{
				printf("%s", line);
			}
		}
		if (strlen(line) == 1023 && line[1022] != '\n')
		{
			if (!over_limit)
			{
				fprintf(stderr, "error: line contains more than 1023 characters... Skipping the rest\n");
			}
			printf("\n");
			char temp = fgetc(file);
			while (temp != EOF && temp != '\n')
			{
				temp = fgetc(file);
			}
		}
	}
	fclose(file);

}



long int NumOfLines(FILE *file)
{
	long int counter = 0;
	char c = fgetc(file);
	while(c != EOF)
	{
		if (c == '\n')
		{
			++counter;
		}
		c = fgetc(file);
	}
	rewind(file);
	return counter;
}
