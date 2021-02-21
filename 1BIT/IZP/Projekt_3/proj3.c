/*  Filip Januska
      xjanus11
		  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define UP_DOWN 2
#define LEFT 0
#define RIGHT 1
#define MOD(a,b) ((((a)%(b))+(b))%(b))          //spravny zvysok po deleni - bez zapornych cisel
#define INDEX r * map->cols + c
#define ARG_ERR {\
                fprintf(stderr, "error: invalid arguments\n");\
                return 1;\
                }

typedef struct {
    int rows;
    int cols;
    unsigned char *cells;
} Map;

int check_first_border(Map *map, int r, int c);
char check_if_num(char *string, int *x);
int check_borders(Map *map);
int read_file(FILE *file, int *r, int *c, char **string);
void map_cstr(Map *map, int r, int c, char *string);
void map_dcstr(Map *map);
bool is_border(Map *map, int r, int c, int border);
int start_border(Map *map, int r, int c, int leftright);
int get_direction (int r, int c, int leftright);
void find_path(Map *map, int r, int c, int leftright);

int main(int argc, char *argv[]){

    int leftright = 0;                  //ruka, ktora sa ma sledovat
    bool test = false;
    int name_pos = 4;                  //pozicia nazvu suboru v argumentoch
    if (argc == 1){                  //ziadne argumenty
        ARG_ERR
    }
    else if (strcmp(argv[1], "--help") == 0 && argc == 2){          //help
        printf("Pre spustenie testu mapy, zadajte:\n --test [nazov_suboru.txt]\n"
               "Pre najdenie cesty pomocou pravidla pravej ruky, zadajte:\n --rpath [riadok] [stlpec] [nazov_suboru.txt]\n"
               "Pre najdenie cesty pomocou pravidla lavej ruky, zadajte:\n --lpath [riadok] [stlpec] [nazov_suboru.txt]\n");
        return 0;
    }
    else if (strcmp(argv[1], "--test") == 0 && argc == 3){          //test
       test = true;
       name_pos = 2;                                        //pozicia nazvu suboru v argumentoch
    }
    else if (strcmp(argv[1], "--rpath") == 0 && argc == 5){          //prava ruka
        leftright = -1;
    }
    else if (strcmp(argv[1], "--lpath") == 0 && argc == 5){          //lava ruka
        leftright = 1;
    }
    else{
        ARG_ERR
    }

    FILE * file = fopen(argv[name_pos], "r");            //otvorit a skontrolovat otvorenie suboru z argumentov
    if (file == NULL){
        ARG_ERR
    }

    Map map;

    int rows, cols;                                             //pocet riadkov a stlpcov
    char *string = NULL;                                        //pomocny retazec
    if (read_file(file, &rows, &cols, &string) != 0){            //kontrola udajov v mape
        printf("Invalid\n");
        return 2;
    }
    fclose(file);

    map_cstr(&map, rows, cols, string);
    if (map.cells == NULL){                      //kontrola alokacie pamate
        fprintf(stderr, "error: malloc fail\n");
        return 3;
    }

    if (check_borders(&map) == 1){           //kontrola susediacich policok
        printf("Invalid\n");
        return 2;
    }
    if (test)                       //ak bol spusteny iba test, program sa ukonci
    {
        free(string);
        map_dcstr(&map);
        printf("Valid\n");
        return 0;
    }

    int r, c;
    //kontrola ci su argumenty cisla a ci argumenty spadaju do rozmedzia pola
    if ((check_if_num(argv[2], &r) != 0) || check_if_num(argv[3], &c) != 0 || r < 1 || c < 1 || r > map.rows || c > map.cols){
        ARG_ERR
    }
    r--;    //uprava r a c kvoli indexovaniu - uzivatel pocita index od 1, program od 0
    c--;
    if (check_first_border(&map, r, c) == 1){        //kontrola ci sa v zadanom policku da do mapy vstupit
        ARG_ERR
    }
    find_path(&map, r, c, leftright);
    map_dcstr(&map);
    free(string);
    return 0;
}

char check_if_num(char *string, int *x)
{
    char *fail;
    *x = strtol(string, &fail, 10);
    return *fail;
}

int check_borders(Map *map)                         //kontrola susediacich hranic
{
    int r = map->rows;
    int c = map->cols;
    for (int i = 0; i < (r*c); i++) {
        if ((i % c) == (c-1))               //preskocit posledne polia v riadkoch
        {
            continue;
        }
        // kontrola pravej hranice s lavou hranicou susediaceho pola
        if((is_border(map, i / c, i % c, RIGHT) != (is_border(map, (i+1) / c, (i+1) % c, LEFT))))
        {
            return 1;
        }
        if (i < c || i >= (r*c) - c){       //preskocit prvy a posledny riadok
            continue;
        }
        else                             //parne i == horna hranica | neparne i == dolna hranica
        {
            if (i % 2 == 0)         //parne polia - kontrola hornej hranice s dolnou hranicou pola o riadok vyssie
            {
                if ((is_border(map, i / c, i % c, UP_DOWN) != (is_border(map, (i-c) / c, (i-c) % c, UP_DOWN))))
                {
                    return 1;
                }
            }
            else        //neparne polia = kontrola dolnej hranice s hornou hranicou pola o riadok nizsie
            {
                if ((is_border(map, i / c, i % c, UP_DOWN) != (is_border(map, (i+c) / c, (i+c) % c, UP_DOWN))))
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int read_file (FILE *file, int *r, int *c, char **string)       //skontroluje platnost mapy v subore, ulozi hodnoty do premennych
{
    if (fscanf(file, "%d %d", r, c) != 2)                       //pocet riadkov a stlpcov
    {
        return 1;
    }
    int size = *r * *c;
    if ((*string = (char *) malloc(1 + sizeof(char) * size)) == NULL)       //alokacia pamata pre pomocny retazec
    {
        return 1;
    }
    char x = '\0';
    int counter = 0;
    while ((x = fgetc(file)) != EOF)                    //nacitanie jednotlivych znakov
    {
        if (x != ' ' && x != '\r' && x != '\n')
        {
            if (!isdigit(x))                        //kontrola, ci znak je cislica
            {
                return 1;
            }
            counter++;
            if (counter > size || x < '0' || x > '7')        //prilis moc prvkov alebo zla hodnota cisla
            {
                return 1;
            }
            strncat(*string, &x, 1);
            strncat(*string, "\0", 1);
        }
    }
    if (counter < size)             //malo prvkov
    {
        return 1;
    }
    return 0;
}

void map_cstr(Map *map, int r, int c, char *string)         //konstruktor mapy
{
    map->rows = r;
    map->cols = c;
    map->cells = malloc(1 + sizeof(char) * r * c);
    if (map->cells != NULL)
    {
        memcpy(map->cells, string, r*c + 1);
    }

}

void map_dcstr(Map *map)                //dekonstruktor mapy
{
    free(map->cells);
    map->cells = NULL;
}

bool is_border(Map *map, int r, int c, int border)          //kontrola typu zadanej hranice
{
    return ((1<<border) & (map->cells[INDEX]));             //border: 0-lava, 1-prava, 2-hore/dole
}

int check_first_border(Map *map, int r, int c)
{
    if (r != 0 && r+1 != map->rows && c != 0 && c+1 != map->cols){       //ak zadane policko nie je na kraji
        return 1;
    }
    if (r == 0 && c == 0){                                      //lavy horny roh
        return (is_border(map, r, c, UP_DOWN) && is_border(map, r, c, LEFT));
    }
    if (r == 0 && c+1 == map->cols){                              //pravy horny roh
        if ((r % 2) != (c % 2)){                                    //ak roh nema pristupnu hornu hranicu
            return is_border(map, r, c, RIGHT);
        }
        return (is_border(map, r, c, UP_DOWN) && is_border(map, r, c, RIGHT));
    }
    if (r+1 == map->rows && c == 0){                            //lavy dolny roh
        if ((r % 2) == (c % 2)){                                //ak roh nema pristupnu dolnu hranicu
            return is_border(map, r, c, LEFT);
        }
        return (is_border(map, r, c, UP_DOWN) && is_border(map, r, c, LEFT));
    }
    if (r+1 == map->rows && c+1 == map->cols){                  //pravy dolny roh
        if ((r % 2) == (c % 2)){                                //ak roh nema pristupnu dolnu hranicu
            return is_border(map, r, c, RIGHT);
        }
        return (is_border(map, r, c, UP_DOWN) && is_border(map, r, c, RIGHT));
    }

    if (r == 0 ){        //v prvom riadku ak nema policko hornu hranicu
        if (c%2 == 1) {
            return 1;
        }
        return is_border(map, r, c, UP_DOWN);
    }
    if (r+1 == map->rows){        //v poslednom riadku, ak policko nema dolnu hranicu
        if (c%2 == r%2) {
            return 1;
        }
        return is_border(map, r, c, UP_DOWN);
    }
    if (c == 0 ){                               //prvy stlpec, kontrola lavej hranice
        return is_border(map, r, c, LEFT);
    }
    if (c+1 == map->cols){                      //posledny stlpec, kontrola pravej hranice
        return is_border(map, r, c, RIGHT);
    }
    return 0;
}

int start_border(Map *map, int r, int c, int leftright)         //udanie pociatocnej hranice
{
    int direction = get_direction(r, c, leftright);

    if ((r == 0 || r+1 == map->rows) && (c == 0 || c+1 == map->cols)) {     //kontrola rohovych policok
        if (!(is_border(map, r, c, UP_DOWN))) {                             //kontrola vstupu cez hornu/dolnu hranicu
            return MOD((UP_DOWN + direction), 3);
        }
        if (r == 0 && c == 0) {                                         //vlavo hore
            if (!(is_border(map, r, c, LEFT)))
                return MOD((LEFT + direction), 3);
        }
        if (r == 0 && c + 1 == map->cols) {                             //vpravo hore
            if (!(is_border(map, r, c, RIGHT))) {
                return MOD((RIGHT + direction), 3);
            }
        }
        if (r + 1 == map->rows && c == 0) {                     // vlavo dole
            if (!(is_border(map, r, c, LEFT))) {
                return MOD((LEFT + direction), 3);
            }
        }
        if (r + 1 == map->rows && c + 1 == map->cols) {            //vpravo dole
            if (!(is_border(map, r, c, RIGHT))) {
                return MOD((RIGHT + direction), 3);
            }
        }
    }
    if (c == 0){                        //policka vlavo
        return MOD((LEFT + direction), 3);
    }
    if (c+1 == map->cols){                 //policka vpravo
        return MOD((RIGHT + direction), 3);
    }
    if (r == 0 || r+1 == map->rows){        //policka hore a dole
        return MOD((UP_DOWN + direction), 3);
    }
    return 0;

}

int get_direction (int r, int c, int leftright)
{
    int direction = leftright;                  //-1 = right, 1 = left
    if ((r%2) == (c%2)){                //podla typu trojuholnika - spica hore alebo spica dole
        direction *= -1;
    }
    return direction;
}

void find_path(Map *map, int r, int c, int leftright)
{
    int steps[2][3][3] = {                              //sada krokov, ktore sa mozu vykonat
            {{-1, 0}, {1, 0}, {0, +1}},
            {{-1, 0}, {1, 0}, {0, -1}},
            };
    int border_change[3] = {1, -1, 0};                  //zmena hranice vystupneho policka na hranicu vstupneho policka
    int border = start_border(map, r, c, leftright);
    int direction = get_direction(r, c, leftright);
    int *step;
    while(r >= 0 && c>= 0 && r+1 <= map->rows && c+1 <= map->cols)                //kym je vnutri mapy
    {
        printf("%d,%d\n", r+1, c+1);
        while(is_border(map, r, c, border))                                    //pokial je policko stena, posuvaj policko
        {
            border = MOD(border + direction, 3);
        }
        step = steps[(r%2) == (c%2)][border];                                   //sprav krok, na zaklade rotacie policka a hranice
        c += step[0];
        r += step[1];
        direction = get_direction(r, c, leftright);                             //novy smer policka
        border += border_change[border];                                        //vstupna hranica noveho policka
        border = MOD(border + direction, 3);                             //prva hranica na kontrolu noveho policka
    }
}
