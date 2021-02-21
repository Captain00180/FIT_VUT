/*______Filip  Januska_____
  ________xjanus11________ */

#include <stdio.h>
#include <string.h>

void convert_to_number(const char *string, char *return_string);
void remove_newline(char *string);
int read(char *string);

int main(int argc, char *argv[])
{
    char riadok_1[101];
    char riadok_2[101];
    int found = 0;
    char converted_riadok_1[101];
    char converted_riadok_2[101];

    if (argc > 2)		//ak bolo zadanych viacero retazcov, ukoncit program s chybovym hlasenim
    {
        fprintf(stderr, "Chybny pocet argumentu\n");
        return 1;
    }

    if (argc < 2) 		    //ak nebol zadany retazec na vyhladanie, vypise cely zoznam a ukonci program
    {
        while (read(riadok_1) != 0 && read(riadok_2) != 0)
        {
            remove_newline(riadok_1);
            remove_newline(riadok_2);
            printf("%s, %s\n", riadok_1, riadok_2);
        }
        return 0;
    }

    while (1)
    {
        if (read(riadok_1) == 0 || read(riadok_2) == 0)         //ak sa nepodari nacitat riadok, ukoncit program
        {
            if (found == 0)
            {
                printf("Not found\n");
            }
            return 0;
        }
        remove_newline(riadok_1);
        remove_newline(riadok_2);
        strcpy(converted_riadok_1, "");
        strcpy(converted_riadok_2, "");
        convert_to_number(riadok_1, converted_riadok_1);
        convert_to_number(riadok_2, converted_riadok_2);
        if (strstr(converted_riadok_1, argv[1]) != NULL || strstr(converted_riadok_2, argv[1]) != NULL) {
            printf("%s, %s\n", riadok_1, riadok_2);           //ak program najde zhodu, vypise obidva riadky zaznamu
            found = 1;
        }
    }
}

//kazde pismeno zo 'string' zapise do 'return_string' ako cislo, ktore dany znak reprezentuje ('abc' = 2, 'def' = 3..)
void convert_to_number (const char *string, char *return_string) {
    for (size_t i = 0; i < strlen(string); i++) {
        char x = string[i];
    					 //podla ASCII hodnoty znaku kontroluje, ci je pismeno velke alebo male 
	 if (64 < x && x < 91) {                         
//ak je znakom velke pismeno, konvertovat na male (male a velke pismena su v ASCII od seba vzdialene o 32 pozici
	    x += 32;
        }
        if (96 < x && x < 123){				//podla ASCII hodnoty znaku zapise do 'return_string' cislo
            if (x < 100) {		
                strncat(return_string, "2", 1);	//abc
            } else if (x < 103) {
                strncat(return_string, "3", 1);	//def
            } else if (x < 106) {
                strncat(return_string, "4", 1);	//ghi
            } else if (x < 109) {
                strncat(return_string, "5", 1);	//jkl
            } else if (x < 112) {
                strncat(return_string, "6", 1);	//mno
            } else if (x < 116) {
                strncat(return_string, "7", 1);	//prqs
            } else if (x < 119) {
                strncat(return_string, "8", 1);	//tuv
            } else if (x < 123) {
                strncat(return_string, "9", 1);	//wxyz
            }
        }
        else if (x == '+') {
            strncat(return_string, "0", 1);
        }
        else if (x != ' ')         //ak znak nie je pismeno, '+' ani medzera, zapise ho do 'return_string' bez zmeny
        {
            int len = strlen(return_string);
            return_string[len++] = x;
            return_string[len] = '\0';
        }
    }
}

//nahradi '\r' a '\n' znak nulovym znakom (odstranenie newline znaku kvoli vypisu na jeden riadok)
void remove_newline(char *string){
for (size_t i = 0; i < strlen(string); i++)
    {
        if (string[i] == '\r' || string[i] == '\n')
        {
            string[i] = '\0';
        }
    }
}


//nacita riadok zo vstupu
//ak riadok obsahuje viac nez 100 znakov, 'ukroji' riadok na 100 znakov
//kazdy znak po 100. znaku je povazovany za neplatne data, pokracuje v dalsom riadku
int read(char *string)
{
    char temp = '\0';
    if (fgets(string, 101, stdin) == NULL)
    {
        return 0;
    }
    if (strlen(string) == 100)				
    {
        do{
            temp = fgetc(stdin);			//kazdy znak po 100. znaku zahodi, az po koniec riadku
        } while(temp != '\n');
    }
    return 1;
}
