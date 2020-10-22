/**********************************************************************
 * 		 	       proj2.c				                              *
 * 		    	    IOS Projekt 2			                          *
 * 		     Autor: Filip Januska, xjanus11		                      *
 * 		     	FIT VUT Brno,  2019/2020		                      *
**********************************************************************/


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



/*************************************************************************
                           GLOBAL VARIABLES
 *************************************************************************/
//  semaphores
sem_t *turnstile = NULL;
sem_t *registration = NULL;
sem_t *all_checked = NULL;
sem_t *confirmation = NULL;
sem_t  *print_mutex = NULL;

//  shared memory variables
int *mutex = NULL;
int *immigrant_index = NULL;
int *entered = NULL;
int *registered = NULL;
int *all_imm = NULL;
int *judge_waiting = NULL;
int *action_counter = NULL;

//  global file pointer
FILE * file = NULL;


/*************************************************************************
                            FUNCTIONS
 *************************************************************************/
//      gets and checks parameters
int get_params(int argc, char *argv[], int *PI, int* IG, int *JG, int *IT, int *JT)
{
    if (argc != 6)
    {
        fprintf(stderr, "error: invalid number of program parameters\n");
        return -1;
    }

    //  check all arguments for non-digit characters
    //  arguments should be only positive integers
    for (int i = 1; i < argc; ++i)
    {
        for (size_t j = 0; j < strlen(argv[i]); ++j)
        {
            if (!isdigit( argv[i][j] ))
            {// non-digit character found
                fprintf(stderr, "error: '%s' is not a valid positive integer\n", argv[i]);
                return -1;
            }
        }
    }

    *PI = strtol(argv[1], NULL, 10);
    *IG = strtol(argv[2], NULL, 10);
    *JG = strtol(argv[3], NULL, 10);
    *IT = strtol(argv[4], NULL, 10);
    *JT = strtol(argv[5], NULL, 10);

    if (*PI < 1 || *IG < 0 || *IG > 2000 || *JG < 0 || *JG > 2000 || *IT < 0 || *IT > 2000 || *JT < 0 || *JT > 2000)
    {
        fprintf(stderr, "error: invalid parameter value\n");
        return -1;
    }

    return 0;


}

//  custom sleep function
int my_sleep(int max)
{
    //random number from interval <0, max>
    int n = rand() % (max + 1);

    //nanosleep structure
    struct timespec s_time;
    //ammount of seconds
    s_time.tv_sec = n / 1000;
    //ammount of nanoseconds
    s_time.tv_nsec = (n - 1000 * s_time.tv_sec) * 1000000;

    if (nanosleep(&s_time, NULL) < 0)
    {// nanosleep error
        fprintf(stderr, "error: nanosleep failed\n");
        return 1;
    }

    return 0;
}

//writes action message to output file
void write_f(char * format, ...)
{
    //wait for write priority
    sem_wait(print_mutex);

    va_list args;
    va_start(args, format);

    (*action_counter)++;
    fprintf(file, "%d:\t", *action_counter);
    fflush(file);

    vfprintf(file, format, args);
    fflush(file);

    va_end(args);

    sem_post(print_mutex);
}


//semaphore and memory cleanup
void cleanup()
{
    //semaphores
    sem_close(turnstile);
    sem_unlink("/xjanus11.ios.proj2.turnstile");
    sem_close(registration);
    sem_unlink("/xjanus11.ios.proj2.registration");
    sem_close(all_checked);
    sem_unlink("/xjanus11.ios.proj2.all_checked");
    sem_close(confirmation);
    sem_unlink("/xjanus11.ios.proj2.confirmation");
    sem_close(print_mutex);
    sem_unlink("/xjanus11.ios.proj2.print_mutex");

    //shared memory
    munmap(mutex, sizeof(mutex));
    munmap(immigrant_index, sizeof(immigrant_index));
    munmap(entered, sizeof(entered));
    munmap(all_imm, sizeof(all_imm));
    munmap(registered, sizeof(registered));
    munmap(judge_waiting, sizeof(judge_waiting));
    munmap(action_counter, sizeof(action_counter));
}




/*************************************************************************
                    JUDGE PROCESS FUNCTION
 *************************************************************************/

void judge(int imm_count, int delay_JG, int delay_JT)
{
    //repeat confirmation process until all immigrants have been confirmed
    while(imm_count > 0){
        my_sleep(delay_JG);
        //enter after a random delay

        /*************************************************************************/

        write_f("JUDGE:\twants to enter\n");
        //wait to enter
        sem_wait(turnstile);

        write_f("JUDGE:\tenters:\t %d: %d: %d\n",  *entered, *registered, *all_imm);

        /*************************************************************************/

        if (*entered != *registered && *entered != 0)
        {// wait for all immigrants to register
            *judge_waiting = 1;
            write_f("JUDGE:\twaits for imm:\t %d: %d: %d\n",  *entered, *registered, *all_imm);
            sem_wait(all_checked);
        }
        *judge_waiting = 0;

        /*************************************************************************/

        write_f("JUDGE:\tstarts confirmation:\t %d: %d: %d\n",  *entered, *registered, *all_imm);

        int n_of_registered = *registered;

        //sleep for <0, JT>
        my_sleep(delay_JT);

        *entered = 0;
        *registered = 0;

        write_f("JUDGE:\tends confirmation:\t %d: %d: %d\n",  *entered, *registered, *all_imm);

        imm_count -= n_of_registered;
        for (int i = 0; i < n_of_registered; ++i)
        {//confirm all registered immigrants
            sem_post(confirmation);
        }

        /*************************************************************************/

        //sleep for <0, JT>
        my_sleep(delay_JT);

        /*************************************************************************/

        //exit building
        write_f("JUDGE:\tleaves:\t %d: %d: %d\n",  *entered, *registered, *all_imm);
        sem_post(turnstile);
    }

    //  close judge process
    write_f("JUDGE:\tfinishes\n");

    exit(0);
}




/*************************************************************************
                    IMMIGRANT PROCESS FUNCTION
 *************************************************************************/
void immigrant(int IT)
{
    srand(time(0));
    //set immigrant ID
    int index = (*immigrant_index) +  1;
    (*immigrant_index) ++;

    write_f("IMM %d:\tstarts\n",  index);

    /*************************************************************************/

    //wait for the turnstile semaphore (entering the building)
    sem_wait(turnstile);
    (*entered)++;
    (*all_imm)++;

    write_f("IMM %d:\tenters:\t %d: %d: %d\n",  index, *entered, *registered, *all_imm);

    //enter the building
    sem_post(turnstile);

    /*************************************************************************/

    //wait for registration
    sem_wait(registration);
    (*registered)++;

    write_f("IMM %d:\tchecks:\t %d: %d: %d\n",  index, *entered, *registered, *all_imm);

    //open only if all immigrants are registered and judge is waiting for all immigrants to register
    if (*entered == *registered && *judge_waiting == 1)
    {
        sem_post(all_checked);
    }

    sem_post(registration);

    /*************************************************************************/

    //wait to be confirmed
    sem_wait(confirmation);

    write_f("IMM %d:\twants certificate:\t %d: %d: %d\n",  index,  *entered, *registered, *all_imm);

    //  getting certificate
    my_sleep (IT);

    write_f("IMM %d:\tgot certificate:\t %d: %d: %d\n",   index, *entered, *registered, *all_imm);

    /*************************************************************************/

    //leave the building
    sem_wait(turnstile);
    (*all_imm)--;

    write_f("IMM %d:\tleaves:\t %d: %d: %d\n",  index, *entered, *registered, *all_imm);

    sem_post(turnstile);

    /*************************************************************************/

    //close the immigrant process


    exit(0);

}




/*************************************************************************
                    IMMIGRANT PROCESS GENERATOR FUNCTION
 *************************************************************************/
void generate(int immigrants, int IG, int IT)
{

    //generate 'immigrants' number of immigrant processes
    for (int i = 0; i < immigrants; ++i)
    {
        //generate an immigrant after a random delay
        my_sleep(IG);
        pid_t PID = fork();
        if (PID < 0)
        {// fork() error
            fprintf(stderr, "error: process generation unsuccessful\n");
            cleanup();
            fclose(file);
            exit(1);
        }
        if ( PID == 0)
        {// newly born immigrant process
            immigrant(IT);
        }
    }

    /*************************************************************************/

    //wait for all the immigrants to finish before closing the generator process
    for (int i = 0; i < immigrants; ++i)
    {
        wait(NULL);
    }

    exit(0);
}




/*************************************************************************
                            MAIN PROGRAM
 *************************************************************************/
int main(int argc, char *argv[])
{

    /***********************************************************
                        PROCESSING PARAMETERS
     ***********************************************************/

    int PI = 0;
    int IG = 0;
    int JG = 0;
    int IT = 0;
    int JT = 0;

    if (get_params(argc, argv, &PI, &IG, &JG, &IT, &JT) !=  0)
    {
        return 1;
    }


    /*************************************************************
                SEMAPHORE AND MEMORY INITIALIZATION
     *************************************************************/

    srand(time(0));

    //map shared memory variables so that all child processes may use them

    mutex = mmap(NULL, sizeof(*(mutex)), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    immigrant_index = mmap(NULL, sizeof(*(immigrant_index)), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    entered= mmap(NULL, sizeof(*(entered)), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    registered = mmap(NULL, sizeof(*(registered)), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    all_imm = mmap(NULL, sizeof(*(all_imm)), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    judge_waiting = mmap(NULL, sizeof(*(judge_waiting)), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    action_counter = mmap(NULL, sizeof(*(action_counter)), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    if (mutex == MAP_FAILED || immigrant_index == MAP_FAILED || entered == MAP_FAILED  ||
        registered == MAP_FAILED || all_imm == MAP_FAILED || judge_waiting == MAP_FAILED || action_counter == MAP_FAILED )
    {   //mmap error
        fprintf(stderr, "error: mmap failed\n");
        return 1;
    }

    //initialize shared memory variables
    *immigrant_index = 0;
    *mutex = 0;
    *entered = 0;
    *registered = 0;
    *all_imm = 0;
    *judge_waiting = 0;
    *action_counter = 0;

    //create semaphores
    turnstile = sem_open("/xjanus11.ios.proj2.turnstile", O_CREAT | O_EXCL, 0666, 1);
    registration = sem_open("/xjanus11.ios.proj2.registration", O_CREAT | O_EXCL, 0666, 1);
    all_checked = sem_open("/xjanus11.ios.proj2.all_checked", O_CREAT | O_EXCL, 0666, 0);
    confirmation = sem_open("/xjanus11.ios.proj2.confirmation", O_CREAT | O_EXCL, 0666, 0);
    print_mutex = sem_open("/xjanus11.ios.proj2.print_mutex", O_CREAT | O_EXCL, 0666, 1);

    if (turnstile == SEM_FAILED || registration == SEM_FAILED || all_checked == SEM_FAILED || confirmation == SEM_FAILED || print_mutex == SEM_FAILED)
    {//semaphore error
        fprintf(stderr, "error: semaphore creation unsuccessful\n");
        cleanup();
        return 1;
    }

    //  create/open output file
    file = fopen("proj2.out", "w");
    if (file == NULL)
    {// file error
        fprintf(stderr, "error: could not create output file\n");
        cleanup();
        return 1;
    }


    /******************************************************
                    PROCESS GENERATION
     ******************************************************/

    //create the generator process
    pid_t GID = fork();
    if (GID < 0)
    {// fork() error
        fprintf(stderr, "error: process generation unsuccessful\n");
        cleanup();
        fclose(file);
        return 1;

    }
    if (GID == 0)
    {
        //generator process
        generate(PI, IG, IT);
    }

    //main program
    else
    {
        //create judge process
        pid_t JID = fork();
        if(JID < 0)
        {// fork() error
            fprintf(stderr, "error: process generation unsuccessful\n");
            cleanup();
            fclose(file);
            return 1;
        }
        if (JID == 0)
        {// judge process
            judge(PI, JG, JT);
        }
        else
        {//     main program    //

            //wait for the generator and judge processes to finish
            waitpid(GID, NULL, 0);
            waitpid(JID, NULL, 0);
        }
    }


    cleanup();
    fclose(file);
    return 0;

}
