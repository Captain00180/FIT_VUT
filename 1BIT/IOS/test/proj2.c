
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <time.h>
#include <sys/wait.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>


  
int main(int argc, char *argv[])
{

	if (argc != 6)
	{
		fprintf(stderr, "error: invalid number of parameters\n");
		return -1;
	}
	
	int PI=0;
	int IG=0;
	int JG=0;
        int IT=0;
        int JT=0;

	for (int i = 1; i < argc; ++i)
	{
		for (size_t j = 0; j < strlen(argv[i]) ; ++j)
		{
			if (!isdigit(argv[i][j]))
			{
				fprintf(stderr, "error: '%s' is not a valid positive integer\n", argv[i]);
				return -1;
			}
		}

	}		
	
	PI = strtol(argv[1], NULL, 10);
	IG = strtol(argv[2], NULL, 10);
	JG = strtol(argv[3], NULL, 10);
	IT = strtol(argv[4], NULL, 10);
	JT = strtol(argv[5], NULL, 10);



	struct timespec s_time;
	s_time.tv_sec = PI / 1000 ;
	s_time.tv_nsec = (PI - 1000 * s_time.tv_sec) * 1000000;

        printf("Seconds : %ld \n mSecods: %ld\n", s_time.tv_sec, s_time.tv_nsec / 1000000);


	if (nanosleep(&s_time, NULL) < 0)
	{
		printf("sleep error\n");
		return 1;
	}
			


	printf("%d %d %d %d %d\n", PI, IG, JG, IT, JT);


}	
