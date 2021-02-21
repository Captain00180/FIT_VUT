/* Filip Januska
    xjanus11	*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

#define I0 pow(10, -12)         //konstanta - zaverny saturacni proud
#define Ut 0.0258563            //konstanta - tepelne napeti
//vypis chybovych hlaseni
#define ERROR_MSG fprintf(stderr, "error: invalid arguments\n");        


double calc(double Up, double u0, double r);
double diode (double u0, double r, double eps);
char read (char *input, double *output);
int check_valid (char *string);

int main(int argc, char *argv[])
{
    if (argc != 4)                  //kontrola poctu argumentov
    {
        ERROR_MSG
        return 1;
    }
    for (size_t i = 1; i < 4; i++)              //kontrola platnosti argumentov (prazdny retazec, hodnota NaN)
    {
        if (argv[i][0] == '\0')
        {
            ERROR_MSG
            return 2;
        }
        if (check_valid(argv[i]) == 1)
        {
            ERROR_MSG
            return 3;
        }
    }
    double u0, odpor, eps;
    //ulozit vstupne argumenty do vytvorenych premennych, skontrolovat, ci neobsahuju neciselne znaky
    if (read(argv[1], &u0) != 0 || read(argv[2], &odpor) != 0 || read(argv[3], &eps) != 0 )
    {
        ERROR_MSG       //ukoncit program ak v nejakom argumente sa nachadza  neciselny znak
        return 4;
    }

    if (u0 < 0 || odpor <= 0 || eps <= 0 )      //ziadne z cisel nemoze byt zaporne, u0 jedine moze byt 0
    {
        ERROR_MSG
        return 5;
    }

    double result = diode(u0, odpor, eps);
    printf("Up=%g V\n", result);
    printf("Ip=%g A\n", I0 * (exp(result / Ut) - 1));		//rovnica pre Ip odvodena z 1.Kirch. zakona a Schockleyhovej rovnice
    return 0;
  
}

double calc(double Up, double u0, double r)     		//vypocita hodnotu rovnice v bode Up
{
    return (I0 * (exp(Up / Ut) - 1)) - ((u0 - Up) / r);			//rovnica pre Up odvodena z 1.Kirch. zakona, Schockleyhovej rovnice a Ohmovho zakona
}

double diode (double u0, double r, double eps)      //hlada hodnotu 'Up' s presnostou vysledku 'eps'
{
    double upper = u0;				//horna hranica intervalu
    double lower = 0;				//dolna hranica intervalu
    double middle = (upper + lower) / 2;	//stred intervalu
    double last_middle;
    while ((fabs(upper - lower)) > eps)
    {
        middle = (upper + lower) / 2;
        if (middle == last_middle)              //ak sa hodnota 'middle' (Up) nezmenila od minulej iteracie,  ukoncit cyklus
        {
            break;
        }
        if (calc(middle, u0, r) * calc(lower, u0, r) < 0)       //ak sa nulovy bod nachadza medzi 'middle' a 'lower'
        {
            upper = middle;
        }
        else if (calc(middle, u0, r) * calc(upper, u0, r) < 0)  //ak sa nulovy bod nachadza medzi 'middle' a 'upper'
        {
            lower = middle;
        }
        last_middle = middle;

    }
    return middle;
}
int check_valid(char *string)                       //kontroluje ci retazec nie je "NaN"
{
    for (size_t i = 0; i < strlen(string); i++)
    {
        string[i] = tolower(string[i]);
    }
    if (strcmp(string, "nan") == 0 || strcmp(string, "-nan") == 0)
    {
        return 1;
    }
    return 0;
}

 char read(char *input, double *output)     //vracia ukazatel z funkcie strtod. Prazdny ukazatel == uspesne strtod
{
    char *fail;
    *output = strtod(input, &fail);
   return *fail;
}