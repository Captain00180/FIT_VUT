////////////////////////////////// IJC v. 19.3 /////////////////////////////////
// Kolekce všech příkladů z písemek co jsem kde našel. V první části jsou ty  //
// krátký bait příklady v druhý pak ty delší prográmky. Je možný že jsem se   //
// někde u něčeho přehlídnul nebo kdoví co. Když cokoliv najdete že je blbě   //
// tak to hlašte. Já budu nadávat ale ve skutečnosti jsem rád. Řešení jsou    //
// jenom na oko a jelikož jsem autista tak můžu některý věci dělat jak kokot. //
// A určitě jsou tam někde nějaký chyby který teď nevidim. Sorry. Ale nevěšte //
// mě hned kvůli tomu za koule do průvanu. Děkuji.                            //
////////////////////////////////////////////////////////////////////////////////
// Licence neexistuje jako žádná jiná. Klidně si to vytiskněte, nastříhejte   //
// na pásky, narolujte a dejte si to na záchod jako hajzpapír. Klidně smaž    //
// tuhle hlavičku a vydávej to za svoje ale tak abych si toho nevšimnul.      //
//                                     !!!                                    //
//   Prosba na další generace aby to tady popřípadě rozšířili o nový příklady //
//             zase pro další generace protože takhle to funguje.             //
//                                     !!!                                    //
// U těch dlouhejch příkladů zásadně doporučuju zkusit si to nejdřív napsat   //
// bez pomoci a pak se teprv podívat na řešení. Koukáním se nikdy nikdo nic   //
// nenaučil. Tak je dobrý se v tom trochu pohrabat a zkoušet co a jak se      //
// stane když to a támlecto.                                                  //
////////////////////////////////////////////////////////////////////////////////
// Mělo by to jít zkompilovat přes make. Věci co nejdou tak se nekompilujou.  //
// Moduly jsou zvlášť aby to se to tak odzkoušelo. Na test jsem udělal skript //
// run.sh kterej pustí co je potřeba.                                         //
/////////////////////////////////// Credits ////////////////////////////////////
// + Kubosh           | 19.0 příklady do roku 2019 včetně                     //
//   - Berny12        |   .1 našel nesmyslnou větu                            //
//   - Templarian     |   .2 našel chybku v DELETE_N_BITS                     //
//   - Louda          |   .3 našel chybu v ulong2str                          //
////////////////////////////////////////////////////////////////////////////////

#include <limits.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>

///////////////////////////////// BAIT PŘÍKLADY ////////////////////////////////
//                                                                            //

// Jaký je výsledek výrazu:
char expr1() {
    return *("ABCD" "EFGH" + 4);  // Stringy odělené mezerou se spojí do jednoho. String "vrátí" jenom ukazatel na první znak takže když k němu přičtu 4 tak ukazuju na 5. znak. Dereference mi vrátí daný znak 'E'. Btw samotnej string se uloží do .data read-only
}
                                                                                #if 0
// Jaký je výsledek výrazu:
char expr2() {
    return ("1234" + 1 + "5678")[4];  // Ukazatele nelze sčítat. Střelba do nohy zaručená
}
                                                                                #endif
// Jakou má hodnotu výraz aa[1][1]?
const int aa[3][4] = { { 1, 2, }, { 3, }, { 4, 5, 6 } };
int expr3() {
    return aa[1][1];  // Jelikož je aa globální proměnná tak se pole nuluje proto i zdánlivě neiinicializovaná požoka bude nula. Ta čárka nemá vliv
}

// Jakou má hodnotu výraz aaa[3][1]?
int aaa[3][3] = { { 1, 2, }, { 3, }, { 4, 5, 6 } };
int expr4() {
    //return aaa[3][1];  // Zkompilovat lze protože hranice polí kompilátor nekontroluje. Je to ale samozřejmě přistupování mimo pole. Přistupuju k paměti kam bych neměl může to segfaultnout. Zkuste si to pustit hodí vám to nějaku nesmyslnou hodnotu nebo dostanete po hubě od OSka
    return 69;
}
                                                                                #if 0
// Jaký je výsledek výrazu: 
void *expr5() {
    long double i; 
    long double *p = &i;
    return ((void*)(p+1)) - ((void*)p);  // Aritmetika (odčítání) s void pointerem. Způsob jak se elegantnně střelit do nohy. GCC to umí a bere ho jako 'char *' ale je to prostě C illegal
}
                                                                                #endif
// Jakou hodnotu bude mít sum?
int swit1() {
    int sum = 10;
    for(int i = 0; i < 10; i++) {
        printf("swit1: i:%d sum:%d\n", i, sum);
        switch(i) {                              // Switch skáče na case podle toho jakou hodnotu má i. Od case se prováděj příkazy dokud nenajde break ten ukončí switch. Pokud narazí na continue tak to ovládá venkovní for a ten započne další iteraci. Ty casy lze vidět jako návěští a switch jenom jako goto na ten case. Break je akoby goto na konec switche
            case 4: case 6: case 8: sum++;       // Možnosti 4 6 a 8 vždy přičte 1 a propadávají dál dokud nenajdou break který je až u možnosti 7
            case 7: break;                       // Možnost 7 neudělá nic ale ukonční switch. Continue ovládá for takže v tomhle případě je funkce podobná jako break protože za switchem není další kód
            default: sum--; continue;            // Vše ostatní odečte 1 a skočí na další iteraci foru
        }
    }
    return sum;
}

// Jakou hodnotu bude mít sum?
int swit2() {
    int sum = 0;
    for(int i = 0; i < 8; i++) {
        printf("swit2: i:%d sum:%d\n", i, sum);
        switch(i) {                                 // Princip stejnej jako vejš akorát jinej výsledek
            case 1: case 3: case 5: case 7: sum--;  // Tady se sice odečte sum ale hned zase přičte dál takže se to anuluje
            default: sum++; continue;
            case 6: break;                          // Break je až tady jo takže bacha
        }
    }
    return sum;
}

// Jakou hodnotu bude mít sum?
int swit3() {
    int sum = 10;
    for(int i = 0; i < 9; i++) {
        printf("swit3: i:%d sum:%d\n", i, sum);
        switch(i) {
            case 4: case 6: case 8: sum++;       // Jakmile se jednou dostanu sem 
            case 7: break;                       // tak propadnu až sem a vyskočim
            default: sum--; continue;
        }
        break;                                   // až sem a to vyskočim komplet z cyklu
    }
    return sum;
}

// Co vrátí funkce f1?
size_t f1(float p[9][10]) {
    printf("f1: sizeof(*p)      %ld\n", sizeof(*p));       // Po dereferenci jsem se dostal na pole 10 floatů
    printf("f1: sizeof(p[0])    %ld\n", sizeof(p[0]));
    printf("f1: sizeof(p[0][0]) %ld\n", sizeof(p[0][0]));  // Zde už je jenom float
    printf("f1: sizeof(float)   %ld\n", sizeof(float));    
    printf("f1: sizeof(p)       %ld\n", sizeof(p));        // Když je pole parametr funkce tak se "první pole" automaticky přetypuje na ukazatel. p je ve skutečnosti: 'float (*p)[10]'. U jednorozměrného pole by to bylo jenom: 'float *p'
    printf("f1: sizeof(float *) %ld\n", sizeof(float *));
    
    return sizeof(*p);                                     // Bacha do dopovědi psát "sizeof(float) * 10" protože float může bejt různě velkej na různejch systémech atd.
    //return sizeof(p);                                      // Objevila se i tadle varianta. Odpověď "sizeof(float *)" protože je to jenom ukazatel
}

// Jakou hodnotu vrátí funkce f2()?
int f2(void) {
    char str[10] = "ABCD";          // Pole 10 charů {'A', 'B', 'C', 'D', \0, ...bordel}
    char *s[10] = { str, "EFGH" };  // Pole 10 ukazatelů na char. Nultej prvek je ukazatel na první znak v str 'A' (pole bez závorek je ukazatel na první prvek). První ukazuje na první znak 'E' stringu kterej se uloží do .data readonly
    strcat( *s + 2, "1234" );       // *s přitupuje v nultýmu ukazateli. Spojení "CD" a "1234" protože (*s + 2) ukazuje na 'C' "AB" se jakoby ignoruje "1234" se prostě přidá za "CD". V str je nyní {'A', 'B', 'C', 'D', '1', '2', '3', '4, \0, ...bordel}
    return (*s)[3];                 // *s je str a 4. znak v str je 'D'
}

// Jakou hodnotu vrátí funkce f3()?
int f3(void) {
    static char str[10] = "ABCD";   // Statické pole 10 znaků. Víckrát se funkce nevolá takže je mi jedno že to je static
    char *s[10] = { str, "EFGH" };  // To stejný jako vejš 
    strcpy((*s) + 2, "1234");       // Od znaku 'C' se nakopíruje "1234". Závorka která je vcelku zbytečná * má větší prioritu než sčítání. V str je nyní {'A', 'B', '1', '2', '3', '4, \0, ...bordel}
    return ( (*s)++ )[5];           // Nejprve dereference s a mam str což je vlastně ukazatel na 'A'. Přičtu 1 ale vrátim furt ukazatel na 'A' protože postfix ++. Přitu 5 a provedu dereferenci (tak funguje [5]) takže dostanu '4'
}

// Jakou hodnotu vrátí funkce f4(3)?
char f4(int x) {
    static char *s = "ABCDEFGH";           // Ukazatel na string v .data readonly. Že je statický je mi zase jedno
    const char (*p)[3] = (void *)(s + x);  // s mě ukazuje na 'A' posunu se o 3 a mam ukazatel na 'D'. Přetypuju ho na void pointer a ten uložím jako ukazatele na tříprvkové pole konstatních charů. Což se dá to je prostě přetypování ukazatele
    return * (const char *)(p + 1);        // Jelikož je p ukazatel na tří prvkové pole tak se skáče po třech znacích při přitení 1 (po kolika se skáče určuje právě typ ukazatele). Nyní ukazuju na 'G'. Je nutný přetypování na ukazatel na char jinak by mi jedna derefernce vrátila jenom pole a byla by potřeba ještě jedna dereference (Ukazatel na pole je jakoby ukazatel na ukazatel). Dereference a mam 'G'
    //return **(p + 1);                      // Funguje stejně
}

// Jakou hodnotu vrátí funkce f5(4)?
static int f5(int i) {
    static char pole[] = "ABCDEF";   // Pole charů že je statický je mi jedno protože se funcke nevolá vícekrát. Pole je velký 7 znaků (\0 se počítá taky)
    char *p1 = pole + sizeof(pole);  // Ukazatel p1 mi bude ukazovat za poslední znak v poli (\0) kde je nějakej bordel. Aneb posunu se o 7 od prvního znaku
    char **p2 = &p1;                 // Ukazatel p2 mi ukazuje na ukazatel p1 a už sme všichni v prdeli že
    (*p2) -= i;                      // Dereference p2 takže pracuju s p1 vrátim se o 4 znaky zpátky takže na 'D'
    return **p2;                     // Dvojitá dereference je znak 'D'
}

// Jakou hodnotu vrátí funkce f8()?
int f6(void) {
    char p[10][10] = { "ABC", "DEF", };  // Pole polí charů. Pohoda
    return * p[1];                       // Přistoupim k druhýmu prvku což je ukazatel na 'D'. Dereferencuju a mam znak 'D'
}

// Jakou hodnotu vrátí funkce f6()?
char f7(void) {
    char *s[] = { "1234", "5678", "ABCD", };  // Pole ukazatelů na chary. Stringy jsou v .data readonly 
    return s[2]++ , * ( ++ s[2] );            // Čárka zřetězí příkazy takže se provede nejdřív ten před a pak po čárce. Nejprve se třetí ukazatel zvětší o 1 a nyní již ukazuje na 'B'. Pak se znovu zvětší o 1 a zvětšená hodnota se i vrátí protože prefix ++. Dereference což je znak 'C'. (return vrátí hodnotu toho co je nejvíc napravo odělený čárkou)
}

// Jakou hodnotu vrátí funkce f7()?
char f8(void) {
    const char *s[] = { "012", "345", "678", };  // Pole ukazatelů na konstantní chary. Stringy jsou v .data readonly
    return * ++ (*s);                            // Nejprve se provede dereference z pole a získám nultej prvek a mam ukazatel na '0'. Přičtu jedna a ukazatel mi už ukazuje na '1' prefix ++ takže se mi zvětšený ukazatel i vrátí. Další dereference a dostanu znak '1'
}

// Jakou hodnotu vrátí funkce f9()?
char f9(void) {
    const char *s[] = { "0123", "4567", "89AB", };  // Pole ukazatelů na chary. Stringy jsou v .data readonly
    return s[2]++ , * ( * (s+2) + 1 );              // Stejná siuace s čárkou. Nejprve se posune ukazatel posledního stringu na '9'. Dereference má přednost před sčítátím. *(s+2) je jako s[2] v posledním stringu se posunu o další jeden znak a znova dereference což mi dá 'A'
}

// Jakou hodnotu vrátí funkce f10()?
char f10(void) {
    const char *s[] = { "0123", "4567", "89xy", };  // Pole ukazatelů na chary. Stringy jsou v .data readonly
    return * ++ (s[2]);                             // Nejprve přistoupm k poslednímu ukazateli pak se k němu přičte 1 a přičtený se i vrátí k dereferenci a vrátí '9'
}

// Jakou hodnotu vrátí funkce f()?
char f11(void) {
    const char *s[7] = { "0123456", "ABCDEF", "6543210", };  // Pole ukazatelů na chary. Stringy jsou v .data readonly
    return * (s[1]++ + 2);                                 // [1]++ má přednost před sčítáním. Přistoupim k druhým ukazateli na string a přičtu k němu 1 ale vrátí se původní hodnota (postfix ++). Nyní přičtu 2 takže se posunu na 'C'. Nyní mam ukazatel na 'C'. Dereference a mam 'C'
}

// Co vrátí funkce main1?
static int g1(int i) {
    static int s1 = 10;  // Inicializace se provede jenom jednou pak je s1 jakoby globální
    int a = s1 + 3;      // Do a se uloží aktuální s1 + 3
    s1 -= i;             // Od s1 se odečte i a bacha fakt je s1 globální teď už. Po skončení funkce v s1 zůstane hodnota
    return a;
}
int main1(void) {
    g1(1);               // Po provedení funkce je v s1 9 a funkce vrátí 13
    return g1(2);        // Po provedení funkce je v s1 7 a funkce vrátí 12
}

// Co vrátí funkce main1?
static int g2(int i) {
    static int s2 = 4;  // Inicializace se provede jenom jednou pak je s2 zase jakoby globální
    int a = s2 + 3;     // Do a se uloží aktuální s2 + 3
    s2 -= i;            // Stejný jako g1
    return a;
}
int main2(void) {
    g2(2);              // Po provedení funkce je v s2 2 a funkce vrátí 7
    return g2(1);       // Po provedení funkce je v s2 1 a funkce vrátí 5
}

//                                                                            //
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////// SHORT SHITS /////////////////////////////////
//                                                                            //

// 1) Napište:
// a) Deklaraci funkce AllocMatrix_double3x3 bez parametrů s návratovým 
//    typem "ukazatel na první řádek dvojrozměrného pole čísel" (rozměry a 
//    typ čísel viz jméno funkce).
double (*AllocMatrix_double3x3())[3];  // bez typedef
//typedef double (*mat_ret1)[3];       // s typedef
//mat_ret1 AllocMatrix_double3x3();

// b) Definici výše uvedené funkce takto: funkce dynamicky alokuje a 
//    NULUJE dvojrozměrné pole čísel o zadaném rozměru a vrací ukazatel na 
//    toto pole (POZOR NA TYP - viz výše), nebo NULL pokud alokace selže.
double (*AllocMatrix_double3x3())[3] {  // mat_ret1 AllocMatrix_double3x3() {
    double (*ptr)[3];                   // mat_ret1 ptr = NULL;
    ptr = calloc(3*3, sizeof(double));
    return ptr;
}

// c) Příklad volání této funkce: výsledek uložte do vámi správně definované 
//    proměnné a poslední prvek nastavte na 1.
void shrshi1() {                    // Pomocná funkce abych to nemusel psát do mainu
    double (*mat)[3];               // mat_ret1 mat;
    mat = AllocMatrix_double3x3();
    if(mat != NULL) {
        mat[2][2] = 1;
    }

    // Toto je už mimo zadání, jenom pro ukázku že to lítá
    if(mat != NULL) {
        for(int y = 0; y < 3; y++) {
            for(int x = 0; x < 3; x++) {
                printf("%.1f ", mat[x][y]);
            }
            printf("\n");
        }
        free(mat);
    }
}

// 2) Napište:
// a) Deklaraci funkce AllocIntMatrix100x100 bez parametrů vracející ukazatel
//    na dvojrozměrné pole čísel (rozměry a typ čísel viz jméno funkce).
int (*AllocIntMatrix100x100())[100][100];  // bez typedef
//typedef int (*mat_ret2)[100][100];       // s typedef
//mat_ret2 AllocIntMatrix100x100();

// b) Definujte tuto funkci: funkce dynamicky alokuje a nuluje dvojrozměrné 
//    pole čísel o zadaném rozměru a vrací ukazatel na toto pole
//    (pozor na typ), nebo NULL pokud alokace selže.
int (*AllocIntMatrix100x100())[100][100] {  // mat_ret2 AllocIntMatrix100x100() {
    int (*ptr)[100][100];                   // mat_ret2 ptr = NULL;
    ptr = calloc(100*100, sizeof(int));
    return ptr;
}

// c) Napište příklad volání této funkce, výsledek uložte do vámi správně
//    definované proměnné.
void shrshi2() {                    // Pomocná funkce abych to nemusel psát do mainu
    int (*mat)[100][100];           // mat_ret2 mat;
    mat = AllocIntMatrix100x100();

    // Toto je už mimo zadání 
    if(mat != NULL) {
        free(mat);
    }
}

// 3) 
// a) Definujte inline funkci AllocMAT1(size_t N), která dynamicky alokuje
//    dvojrozměrné pole (matici) čísel int o rozměru N*N a toto pole
//    inicializuje jako jednotkovou matici (1 na diagonále). Funkce vrací 
//    ukazatel na celé pole, nebo NULL pokud alokace selže.
extern void *AllocMAT1(size_t N);                 // Externí definice pro případ že se nepodaří inlinování aby se měla funkce kam dát
inline void *AllocMAT1(size_t N) {                // N je parametr takže nemůžu vrace konkrétní ukazatel třeba na pole [5][5]. Funkce musí bejt univerzální. 'void *' je na to ideálka protože si ho musim přetypovat abych pak moh pracovat dál když si zavolám někde tu funkci
    int (*ptr)[N][N] = calloc(N*N, sizeof(int));  // Uvnitř můžu mít konktrétní ukazatel a taky ho potřebuju abych mohl inicializovat tu jednotkovou matici

    if(ptr != NULL) {
        for(size_t i = 0; i < N; i++) {
            (*ptr)[i][i] = 1;                     // Nejdřív se dereferencuje ten ukazatel abych se dostal k poli
        }
    }

    return (void *)ptr;                           // Nakonec ho vrátim jako 'void *'. Ten kdo tu funkci volal ví jak snim pracovat a na co ho přetypovat protože funkci zadal daný N
}

// b) Napište příklad volání funkce a otestujte hodnotu prvku [0][0].
void shrshi3() {                      // Pomocná funkce abych to nemusel psát do mainu
    size_t N = 5;

    int (*mat)[N][N] = AllocMAT1(N);  // Tady vim kolik je N takže vim na co si 'void *' přetypovat
    if(mat != NULL) {
        if((*mat)[0][0] == 1) {
            printf("AllocMAT1 ok\n");
        } else {
            printf("AllocMAT1 err\n");
        }
    }

    // Toto je zase mimo zadání jenom hezky na otestování
    if(mat != NULL) {
        for(size_t y = 0 ; y < N; y++) {
            for(size_t x = 0 ; x < N; x++) {
                printf("%d ", (*mat)[x][y]);
            }
            printf("\n");
        }
        free(mat);
    }
}

// 4) Napište deklaraci funkce F s paramatrem P typu dvojrozměrné pole znaků
//    typu char, vracející ukazatel na pole čísel short.
short (*F(char P[][5]))[5];  // Velikost 5 je prostě nějaká vymyšlená ale musí tama bejt. jenom [] by se nezkompilovalo. Krom prvních [] u parametru funkce ty můžou bejt prázdný jako jediný

// 5) Napište deklaraci funkce typu void s parametrem typu pole ukazatelů na int.
void fce1(int *p[]);

// 6) Napište deklaraci funkce bez parametrů vracející pole ukazatelů na char.
char **fce2(void);  // Nemůžu napsat 'char *fce2(void)[5];' protože pole nemůže být navratový typ. Takže se tam musí loupnout asi takhle "ukazatel na první prvek" protože to funguje stejně jako pole. Nevidim jinou klounou cestu ako to urobiť

// 7) 
// a) Definujte 2 struktury S1 a S2:
//      S1 obsahuje položku typu long a ukazatel ukS2 na S2,
//      S2 obsahuje položku typu char a ukazatel ukS1 na S1.
struct S2;            // Nejdřív si musim deklarovat že vůbec něco jako S2 exituje abych v S1 na to moh ukazovat. Můžu ale bez obsahu je to jenom deklarace definice je potom
struct S1 {
    long x;
    struct S2 *ukS2;
};
struct S2 {
    char x;
    struct S1 *ukS1;
};

// b) Definujte 2 globální proměnné: a typu struktura S1, b typu strutkura S2
//    a _inicializujte_ je tak, aby na sebe navzájem ukazovaly
//    (přes položky ukS1, ukS2).
extern struct S2 b;          // Řeknu kompilátoru že někde bude struct b abych
struct S1 a = {.ukS2 = &b};  // tady moh použít její adresu až jí kompilátor najde
struct S2 b = {.ukS1 = &a};  // zde

//                                                                            //
////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////// MAKRA ////////////////////////////////////
//                                                                            //

// 1) Definujte makro ASSIGN_BITFIELD(x, pos, n, val), které v L-hodnotě x
//    libovolného celočíselného typu nastaví zadaných n bitů od bitové pozice
//    pos na hodnotu val (Pozor: val obsahuje n-bitovou hodnotu). ZKONTROLUJTE
//    správnost hodnot všech parametrů pomocí assert. Pozice číslujte od 0 
//    (od LSB). Musíte použít CHAR_BIT. POZOR: Nesmíte změnit hodnoty pos, n,
//    val a nesmíte použít cyklus.
//    Příklad: (int32_t): pos=12, n=12, val=0xF0 0xabXXXcde -> 0xab0F0cde
//    Napište příklad správneho použítí makra.
//



#define ASSIGN_BITFIELD(x, pos, n, val) \
        assert(pos >= 0 && n > 0 && pos < sizeof(x) * CHAR_BIT, n < sizeof(x) * CHAR_BIT);\
        x = (~((~((unsigned long long)(~0) << n)) << pos)) & x | ((unsigned long long)(~0) & val) << pos

#define ASSIGN_BITFIELD(x, pos, n, val) \
    assert(pos >= 0 && n > 0); \
    assert(pos < (sizeof(unsigned long long) * CHAR_BIT) && n < (sizeof(unsigned long long) * CHAR_BIT)); \
    x = (~(~((unsigned long long)(~0) << n) << pos) & x)  |  ((~((unsigned long long)(~0) << n) & val) << pos)
    //  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //     původní x které jsou kolem měnenějch bitů                             měněné bity                  
    // --------------------------------------------------------------------------------------------------------
    // Např. x=0010 1001, pos=2, n=4, val=0101 1101          Zanedbám to že long tam narve hodně nul doleva a jedem hezky postupně zevnitř
    // ~0                                   -> 1111 1111     ~0                                   -> 1111 1111
    // ~0 << n                              -> 1111 0000     ~0 << n                              -> 1111 0000
    // ~(~0 << n)                           -> 0000 1111     ~(~0 << n)                           -> 0000 1111
    // ~(~0 << n) << pos                    -> 0011 1100     ~(~0 << n) & val                     -> 0000 1101
    // ~(~(~0 << n) << pos)                 -> 1100 0011     (~(~0 << n) & val) << pos            -> 0011 0100
    // ~(~(~0 << n) << pos) & x             -> 0000 0001
    //
    //                        (~(~(~0 << n) << pos) & x)  |  ((val & ~(~0 << n)) << pos)          -> 0011 0101

    // Bacha na to že posun nad záporným číslem je andefájnd bihejvr takže se to musí pro jistotku lámat na ten 'unsigned long long' aby to sežralo všechno. Defaultně je 0 totiž int

void mac1() {
    int32_t bitA = 0xbadffcde;
    int64_t bitB = 0x0feeffffefffffff;

    printf("%08x -> ", bitA);
    ASSIGN_BITFIELD(bitA, 8, 12, 0xba);
    printf("%08x\n", bitA);

    printf("%016lx -> ", bitB);
    ASSIGN_BITFIELD(bitB, 32, 16, 0xcdbab);
    printf("%016lx\n", bitB);
}

// 2) Definujte makro ROT_BITS_LEFT(x, n), které v L-hodnotě x typu int 
//    rotuje bity o n pozic doleva (ty které "vypadnou" se vrací na druhé 
//    straně). Před provedením operace zajistěte, aby hodnota n nepřesáhla
//    počet bitů v x. Můžete předpokládat že CHAR_BIT = 8. POZOR: Nesmíte
//    změnit hodnotu n a nesmíte pužít cyklus.
//    Napište příklad správného použití makra.
//



#define ROT_BITS_LEFT(x. n)\
    assert (n > 0 && n < sizeof(x) * 8);\
    x = ((unsigned long long)x << n) | (unsigned long long)x) >> (sizeof(x) * 8 - n)

#define ROT_BITS_LEFT(x, n) \
    assert(n >= 0); \
    assert(n < sizeof(x) * 8); \
    x = ((unsigned)x << n)  |  ((unsigned)x >> ((sizeof(x) * 8) - n))
    //  ~~~~~~~~~~~~~~~~~~     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //    posunutý bity                   přetečený bity
    // ---------------------------------------------------------------
    // Např. x=1100 1010, n=2  Kdyby se pracovalo s bytem normálně to bude int, byte je jenom jako ukázka)
    // x << n -> 0010 1000     sizeof(x) * 8             ->         8
    //                         (sizeof(x) * 8) - n       ->         6
    //                         x >> (sizeof(x) * 8) - n  -> 0000 0011
    //
    //            (x << n)  |  (x >> (sizeof(x)*8) - n)  -> 0010 1011

    // Zase bacha že jakýkoliv posuny nad číselem se znamínkem se nedělajó. Stačí přetypovat na unsigend (unsigned = unsigned int) a je to cajk, hope so

// Na ukázku i posun doprava aby se neřeklo. Posuny jsou jenom obráceně
#define ROT_BITS_RIGHT(x, n) \
    assert(n >= 0); \
    assert(n < sizeof(x) * 8); \
    x = ((unsigned)x >> n)  |  ((unsigned)x << ((sizeof(x) * 8) - n))


void mac2() {
    int bitA = 0xee02c0ff;
    int bitB = 0xcefacefa;

    printf("%08x -> ", bitA);
    ROT_BITS_LEFT(bitA, 16);
    printf("%08x\n", bitA);

    printf("%08x -> ", bitB);
    ROT_BITS_RIGHT(bitB, 8);
    printf("%08x\n", bitB);
}

// 3) Definujte makro DELETE_N_BITS(x, pos, n), které v L-hodnotě x typu 
//    signed int "zruší" n bitů od libvolné bitové pozice pos. Do horních 
//    bitů x se šíří znaménkový bit. Pozice číslujte od nuly (od LSB).
//    Například (32 bit): pos=8, n=12  0xabcNNNde -> 0xFFFabcde
//    Zkotrolujte správnost hodnot parametrů pos, n pomocí assert. POZOR: 
//    Nesmíte změnit hodnoty pos, n a nesmíte použít cyklus.
//    Musíte použít CHAR_BIT.
//

// 11xx x111

#define DELETE_N_BITS(x, pos, n)\
    assert(pos >= 0 && n > 0);\
    assert (pos + n < sizeof(int) *8);\
    if((unsigned) x >> sizeof(int) * 8 - 1)\
        x = (~((unsigned)(~0) << pos) & x | (~((unsigned)(~0) << pos + n)) & x | ((unsigned)(~0) << pos + n);\
    else\
        x =



#define DELETE_N_BITS(x, pos, n) \
    assert(pos >= 0 && n > 0); \
    assert(pos + n < sizeof(x) * CHAR_BIT); \
    if((x & ((unsigned)1 << ((sizeof(x) * CHAR_BIT) - 1))) != 0) { /*Tady se jenom vymaskuje znaménkovej bit (ten nejvíc nalevo) a podle toho se určuje zda tam přidat jedničky nebo ne*/ \
        x = (~((unsigned)(~0) << pos) & x)  |  ((((unsigned)(~0) << (pos + n)) & x) >> n)  |  ((unsigned)(~0) << ((sizeof(x) * CHAR_BIT) - n)); \
    } else { \
        x = (~((unsigned)(~0) << pos) & x)  |  ((((unsigned)(~0) << (pos + n)) & x) >> n); \
    }
    //  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //     bity napravo co se nezmění                          posunuté bity                                  případné jedničky
    // ----------------------------------------------------------------------------------------------------------------------------------------
    // Např. x=0110 1010, pos=2, n=4
    // ~0                     -> 1111 1111     ~0                            -> 1111 1111     ~0                                  -> 1111 1111
    // ~0 << pos              -> 1111 1100     ~0 << (pos + n)               -> 1100 0000     sizeof(x) * CHAR_BIT                ->         8
    // ~(~0 << pos)           -> 0000 0011     (~0 << (pos + n)) & x         -> 0100 0000     (sizeof(x) * CHAR_BIT) - n          ->         6
    // ~(~0 << pos) & x       -> 0000 0010     ((~0 << (pos + n)) & x) >> n  -> 0000 0100     ~0 << ((sizeof(x) * CHAR_BIT) - n)  -> 1100 0000
    //
    //                  (~(~0 << pos) & x)  |  ((~0 << (pos + n)) & x) >> n  -> 0000 0110 {|  (~0 << ((sizeof(x) * CHAR_BIT) - n))}           Když je horní bit 1

    // Stejný zase se zápornejma číslama musim to dát na unsigned

void mac3() {
    int bitA = 0xcac123a0;
    int bitB = 0x7da12dff;
    int bitC = 0xabcfffde;

    printf("%08x -> ", bitA);
    DELETE_N_BITS(bitA, 8, 12);
    printf("%08x\n", bitA);

    printf("%08x -> ", bitB);
    DELETE_N_BITS(bitB, 12, 8);
    printf("%08x\n", bitB);

    printf("%08x -> ", bitC);
    DELETE_N_BITS(bitC, 8, 8);
    printf("%08x\n", bitC);
}

// 4) Definujte makro NBIT_INSERT(x, Pos, n, y), které v L-hodnotě x 
//    libovolného celočíselného typu posune bity na pozicích vyšších než Pos
//    tak, aby vzniklo místo pro n nejméně významných bitů z y, které budou 
//    vloženy na pozici Pos. Pozice bitů číslujte od LSB.
//    Příklad: x=0x12345678, Pos=4, n=12, y=0xCDEF -> 0x4567DEF8
//    Zkontrolujte správnost hodnot paramaterů Pos, n pomocí assert.
//    POZOR: NEsmíte použít cyklus ani změnit hodnoty Pos, n a y.
//    Napište _příklad_ správného použití makra.
//

//   xX
// 1011 0101
// 1111 0000

#define NBIT_INSERT(x, Pos, n, y)\
    assert(Pos >= 0 && n > 0 && Pos < sizeof(x) * CHAR_BiT && n < sizeof(x) * CHAR_BIT);\
    x = (~((unsigned long long)(~0) << Pos)) & x) | (((unsigned long long)(~0) << Pos) & x)<< n) | ((~(unsigned long long)(~0) << n) & y) << Pos

#define NBIT_INSERT(x, Pos, n, y) \
    assert(Pos >= 0 && n > 0); \
    assert(Pos < sizeof(x) * CHAR_BIT && n < sizeof(x) * CHAR_BIT); \
    x = (~((unsigned long long)(~0) << Pos) & x)  |  ((~((unsigned long long)(~0) << n) & y) << Pos)  |  ((((unsigned long long)(~0) << Pos) & x) << n)
    //  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //          bity napravo co se nemění                              vkládané bity                          bity co se posunou aby se uvolnilo místo
    // -------------------------------------------------------------------------------------------------------------------------------------------------
    // Např. x=1001 1010, Pos=2, n=3, y=0000 0101 
    // ~0                           -> 1111 1111     ~0                                 -> 1111 1111     ~0                                -> 1111 1111
    // ~0 << Pos                    -> 1111 1100     ~0 << n                            -> 1111 1000     ~0 << Pos                         -> 1111 1100
    // ~(~0 << Pos)                 -> 0000 0011     ~(~0 << n)                         -> 0000 0111     (~0 << Pos) & x                   -> 1001 1000
    // ~(~0 << Pos) & x             -> 0000 0010     ~(~0 << n) & y                     -> 0000 0101     ((~0 << Pos) & x) << n            -> 1100 0000
    //                                                   (~(~0 << n) & y) << Pos            -> 0001 0100
    //
    //                       (~(~0 << Pos) & x )  |            ((~(~0 << n) & y) << Pos)              |  (((~0 << Pos) & x) << n)          -> 1101 0110
void mac4() {
    int32_t bitA = 0xacdcacee;
    int64_t bitB = 0xfffffffff123abcd;

    printf("%08x -> ", bitA);
    NBIT_INSERT(bitA, 12, 8, 0xfe);
    printf("%08x\n", bitA);

    printf("%016lx -> ", bitB);
    NBIT_INSERT(bitB, 16, 24, 0x456789);
    printf("%016lx\n", bitB);
}

//                                                                            //
////////////////////////////////////////////////////////////////////////////////

////////////////////////// FUCKIN LONG MTHRFCKR SHITS //////////////////////////
//                                                                            //

// 1) Napište funkci
//
//       bool ulong2str(unsigned long x, int r, char *s, int n)
//
//    která převede číslo x typu unsigned long na řetězec s. Základ použité 
//    číselné soustavy je r. Použijte assert na kontrolu rozsahu základu 
//    (od 2 do 36). Výstup může obsahovat znaky z množiny [0-9A-Z]. 
//    Předpokládáme, že pole s má velikost n znaků. Pokud délka výsledku
//    přesáhne maximum, vrací funkce hodnotu false a obsah pole má  
//    nedefinovanou hodnotu. Jinak funkce vrací true a správnou hodnotu v 
//    řetězci s. Pozor na x==0.
//
//    Nepoužívejte žádné standartní funkce kromě assert (jinak 0b).
//
//    Napište PŘÍKLAD volání této funkce s vhodně zvolenými argumenty (včetne
//    jejich deklarací/definic)
//

char int_to_char(int n )
{
        if(n >= 0 && n < 10)
            return '0' + n;
        else
            return 'A' + (n - 10);
}

bool ulong2str(unsigned long x, int r, char *s, int n)
{
        if( s == NULL || n < 0)
            return false;
        assert(r >=2 && r <= 36);

        char temp[n];
        if(x == 0)
            return '0';
        int counter = 0;
        int mod = 0;
        while(x > 0 && counter < n)
        {
            mod = x % r;
            x = x / r;
            temp[counter] = n_to_char(int n);
            ++counter;
            temp[counter] = '\0';
        }
        if(x != 0)
            return false;
        for(int i = 0; i < counter; ++i)
        {
            s[i] = temp[counter - i];
        }
        s[counter] = '\0';
        return true;

}


char char_from_number(int i) {
    if(i < 10) {
        return '0' + i;
    } else {
        return 'A' + (i - 10);
    }
}
bool ulong2str(unsigned long x, int r, char *s, int n) {
    assert(r >= 2 && r <= 36);
    if(s == NULL || n < 2) {
        return false;
    }

    char temp[n];      // Dočasné pole pro uložení znaků které jsou ale pozpátku 
    int ch_count = 0;  // Počet znaků bez \0
    temp[0] = '\0';    // \0 musí bejt nakoci výslednýho pole -> na začátku toho dočasnýho

    // Pro případ x==0
    if(x == 0) {
        temp[1] = '0';
        ch_count = 1;
    } else {
        // Postupný dělení a ukládání si znaků
        for(ch_count = 0; (ch_count < (n - 1)) && (x != 0); ch_count++) {
            temp[1 + ch_count] = char_from_number(x % r); // Převody mezi soustavama to snad každej ví jak lítá
            x = x / r;
        }
        // Pokud jsem nedodělil do nuly nevešel jsem se
        if(x != 0) {
            return false;
        }
    }    

    // Reverznutí pole
    for(int i = 0; i < ch_count +
    1; i++) {
        s[i] = temp[ch_count - i];
    }
    return true;
}
void mthrfckr1() {
    char buffer[100];
    if(ulong2str(255, 16, buffer, 100)) {
        printf("%s\n", buffer);
    } else {
        printf("ovf\n");
    }
    if(ulong2str(5, 2, buffer, 100)) {
        printf("%s\n", buffer);
    } else {
        printf("ovf\n");
    }
    if(ulong2str(255, 2, buffer, 100)) {
        printf("%s\n", buffer);
    } else {
        printf("ovf\n");
    }
    if(ulong2str(255, 2, buffer, 5)) {
        printf("%s\n", buffer);
    } else {
        printf("ovf\n");
    }
}

// 2) Napište program SORTCHECK, který čte ze zadaného souboru (první
//    argument programu) slova a kontroluje zda vyhovují vzestupnému 
//    uspořádání (každé následující slovo je větší nebo rovno předchozímu).
//    Není-li soubor zadán, čte stdin. Program vrací exit kód nula, pokud
//    uspořádání vyhovuje (nebo je prázdný soubor), jinak vrací 1.
//
//    Pro čtení slova ze souboru musíte napsat funkci 
//      
//       int ReadWord(char *s, unsigned m, FILE *f)
//
//    která přeskočí odělovače a načte slovo ze souboru f do řetězce s, kam
//    uloží maximálně m bajtů. Pokud je slovo delší, hlásí chybu na stderr a 
//    _ukončí_ program. Nesmíte použít fscanf(). Funkce vrací délku slova
//    nebo EOF, když narazí na konec souboru.
//
//   Pro porovnání obsahu řetězců použijte standartní funkci
//       int strcmp(const char *s1, const char *s2);
//

int ReadWord(char *s, unsigned m, FILE *F)
{
        if(s == NULL || f == NULL )
            return -42;
        char c = fgetc(f);
        while(c != EOF && isspace(c))
            c = fgetc(f);
        int counter = 0;
        while(c != EOF && !isspace(c))
        {
            ++counter;
            if(counter >= m )
            {
                fprintf(stderr, "error\n");
                exit(1);
            }
            s[counter - 1] = c;
            s[counter] = '\0';
            c = fgec(f);
        }
        if(c == EOF)
            return EOF;
        return counter;

}

int main(int argc, char *argv[])
{
        FILE *file = stdin;
        if(argc >= 2)
        {
            file = fopen(argv[1], "r");
            if (file == NULL)
                return 1;
        }
        int ret_val = 0;
        char str1[128];
        char str2[128];
        ret_val = ReadWord(str2, 128, file);
        while(ret_val != EOF && ret_val >= 0)
        {
            strcpy(str1, str2);
            ret_val = ReadWord(str2, 128, file);
            if(strcmp(str1, str2) > 0)
                return 1;

        }
}


#define WORD_LENGTH 128
int ReadWord(char *s, unsigned m, FILE *f) {
    if(s == NULL || f == NULL) {
        return 0;
    }

    unsigned word_length = 0;
    int loaded_char;

    // Přeskočení bílých znaků
    while(isspace(loaded_char = fgetc(f)) && loaded_char != EOF);
    if(loaded_char == EOF) {
        return EOF;
    }

    // Načtení znaků
    do {
        if(loaded_char == EOF) {
            s[word_length] = '\0';
            return EOF;
        }
        if(word_length >= m - 1) {
            fprintf(stderr, "Přetečení bufferu\n");
            exit(1);
        }

        s[word_length] = loaded_char;
        word_length++;
    } while(!isspace(loaded_char = fgetc(f)));

    s[word_length] = '\0';
    return word_length;
}
int mthrfckr2(int argc, char *argv[]) {  // Tohle je jakoby main
    FILE *file = stdin;
    if(argc >= 2) {
        file = fopen(argv[1], "r");
    }
    if(file == NULL) {
        return 1;
    }

    char buffer_old[WORD_LENGTH];
    char buffer_new[WORD_LENGTH];
    int read_return;
    if(ReadWord(buffer_old, WORD_LENGTH, file) == EOF) {
        if(argc >= 2) {
            fclose(file);
        }
        return 0;
    }
    do {
        read_return = ReadWord(buffer_new, WORD_LENGTH, file);
        if(strcmp(buffer_new, buffer_old) < 0) {
            if(argc >= 2) {
                fclose(file);
            }
            return 1;
        }
        strcpy(buffer_old, buffer_new);
    } while(read_return != EOF);

    if(argc >= 2) {
        fclose(file);
    }
    return 0;
}

// 3) Napište funkci
//       
//       int SearchReplace(char *Str, int Max, const char *s1, const char *s2);
//    
//    která v řetězci Str zamění všechny výskyty podřetězce s1 za obsah s2.
//    Funkce vrací počet úspěšných záměn. Když s2 obsahuje s1 funkce končí.
//    Předpokládáme, že Str může obsahovat Max bajtů a pokud by měl výsledek 
//    překročit tuto mez, funkce další záměny neprovádí a vrátí záporné číslo
//    udávající počet provedených záměn.
//    (Například: Str="STRING", Max=9, s1="ST", s1="", výsledek=1, Str="RING")
//
//    Musíte napsat a použít pomocnou funkci
//       const char *StrStr(const char *Str, const char *s1);
//    který vrátí pozici výskytu podřetězce s1 ve Str nebo NULL v případě
//    neúspěchu.
//
//    Obě funkce musí zvládnout i prázdné řetězce
//
//    POZOR: Nesmíte použít žádné standardní funkce kromě strlen() ani žádná
//    pomocná pole (jinak 0b).
//
//    Nakonec napište PŘÍKLAD volání SearchReplace() s vhodně zvolenými
//    argumenty (včetně jejich deklarací/definic).
//


const char *StrStr(const char *Str, const char *s1)
{
        if(s1 == NULL || Str == NULL)
            return NULL;
        if(strlen(s1) == 0 || strlen(Str) == 0)
            return NULL;

        for(int i = 0; i < strlen(Str); ++i)
        {
            if(Str[i] == s1[0])
            {
                int counter = 0;
                while(Str[i + counter] = s1[counter])
                {
                    ++counter
                }
                if(counter == strlen(s1))
                    return &(Str[i]);
                else
                    return NULL;
            }
        }
        return NULL;
}

int SearchReplace(char *Str, int Max, const char *s1, const char *s2)
{
        if(Str == NULL || s1 == NULL || s2 == NULL)
            return 0;

        if(StrStr(s2, s1) != NULL)
            return 0;

        if(strlen(Str) == 0 && strlen(s1) == 0)
        {
            if(strlen(s2) >= Max)
                return 0;
            for(int i = 0; i <= strlen(s2))
            {
                Str[i] = s2[i];
            }
            return strlen(s2);
        }
        int counter = 0;
        char *ptr = (char*)StrStr(Str, s1);
        while(ptr != NULL)
        {
            ++counter;
            int diff = strlen(s1) - strlen(s2);
            if(diff > 0)
            {
                for(int i = 0; i < Max - 1; ++i)
                {
                    ptr[i] = ptr[i + diff];
                    if(ptr[i] == '\0')
                        break;
                }
            }
            else if(diff < 0)
            {
                diff = -diff;
                if( diff + strlen(Str) >= Max)
                for (int i = Max - 1; i >= 0; --i)
                {
                    if(&(ptr[i + diff]) == ptr)
                        break;
                    ptr[i] = ptr[i + diff];
                }
            }
            for(int i = 0; i <= strlen(s2); ++i)
            {
                ptr[i] = s2[i];
            }
        }
        return counter;
}



const char *StrStr(const char *Str, const char *s1) {
    if(Str == NULL || s1 == NULL) {
        return NULL;
    }
    if(strlen(Str) == 0 || strlen(s1) == 0) {
        return NULL;
    }

    char first_char = s1[0];
    const char *return_char = NULL; // Ukazatel na konstatní char ne konstatní ukazatel na char
    bool match = true;

    for(size_t s = 0; s < strlen(Str); s++) {
        if(Str[s] == first_char) {
            return_char = &(Str[s]);
            match = true;
            for(size_t i = 0; i < strlen(s1); i++) {
                if(s + i < strlen(Str)) {
                    if(Str[s + i] != s1[i]) {
                        match = false;
                        break;
                    }
                } else {
                    match = false;
                    break;
                }
            }
            if(match) {
                return return_char;
            }
        }
    }

    return NULL;
}
int SearchReplace(char *Str, int Max, const char *s1, const char *s2) {
    if(Str == NULL || s1 == NULL || s2 == NULL) {
        return 0;
    }
    if(StrStr(s2, s1) != NULL) {
        return 0;
    }
    if(strlen(s1) == 0 && strlen(Str) == 0) {
        if(strlen(s2) < (unsigned)Max) {
            for(size_t i = 0; i < strlen(s2); i++) {
                Str[i] = s2[i];
            }
            Str[strlen(s2)] = '\0';
            return 1;
        } else {
            return 0;
        }
    }

    char *replace = NULL;
    int replace_count = 0;
    int shift = strlen(s2) - strlen(s1);
    while((replace = (char *)StrStr(Str, s1)) != NULL) {
        if(shift > 0) {  // Posun doprava
            if(strlen(Str) + shift >= (unsigned)Max) {
                return -replace_count;
            }

            for(int i = Max - 1; i >= 0; i--) {
                if(&(Str[i - shift]) == replace) {
                    break;
                }
                Str[i] = Str[i - shift];
            }
        }
        if(shift < 0) {  // Posun doleva
            for(int i = 0; i < Max - 1; i++) {
                replace[i] = replace[i - shift];
                if(replace[i - shift] == '\0') {
                    break;
                }
            }
        }

        // Nakopírování novýho znaku
        for(size_t i = 0; i < strlen(s2); i++) {
            replace[i] = s2[i];
        }
        replace_count++;
    }

    return replace_count;
}
void mthrfckr3() {
    char buffer[10] = "STRING";
    printf("%s -> ", buffer);
    SearchReplace(buffer, 10, "ST", "");
    printf("%s\n", buffer);

    printf("%s -> ", buffer);
    SearchReplace(buffer, 10, "RI", "STRO");
    printf("%s\n", buffer);

    printf("%s -> ", buffer);
    SearchReplace(buffer, 10, "G", "HOP");
    printf("%s\n", buffer);

    printf("%s -> ", buffer);
    SearchReplace(buffer, 10, "HOP", "K");
    printf("%s\n", buffer);
}

// 4) Napište program
//       WORDS Délka [soubor]
//    který z textového souboru zadaného jako druhý argument proramu (není-li
//    zadán použije stdin) čte slova funkcí ReadWord() a na stdout tiskne jen 
//    slova s délkou Délka +-1 znak (například při zadání délky 10 tiskne 
//    slova o délce 9, 10, 11). Délka je zadaná jako první argument programu.
//    Na konverzi použijte
//       int atoi(const char *nptr);
//    Každé slovo program tiskne na zvláštní řádek, před něj navíc vytiskne
//    jeho délku.
//
//    Pro čtení slova ze souboru napiště funkci
//       int ReadWord(FILE *f, char *str, unsigned n);
//    která přeskočí oddělovače (použijte !isalnum()) a čte jedno slovo ze
//    ze souboru f do řetězce str, kam uloží maximálně n bajtů (n si zvolte,
//    delší slova zkraťte a zbytek slova přeskočte). Nesmíte použít fscanf.
//    Funkce vrací SKUTEČNOU délku slova před zkrácením nebo EOF, když narazí
//    na konec souboru
//
#define WORD_LENGTH 128
int ReadWord2(FILE *f, char *str, unsigned n) {
    unsigned word_length = 0;
    int loaded_char;

    // Přeskočení bílých znaků
    while(!isalnum(loaded_char = fgetc(f)) && loaded_char != EOF);
    if(loaded_char == EOF) {
        return EOF;
    }

    // Načtení znaků
    do {
        if(loaded_char == EOF) {
            if(word_length < n) {
                str[word_length] = '\0';
            } else {
                str[n - 1] = '\0';
            }
            return EOF;
        }
        if(word_length < n - 1) {
            str[word_length] = loaded_char;
        }
        word_length++;
    } while(isalnum(loaded_char = fgetc(f)));

    if(word_length < n) {
        str[word_length] = '\0';
    } else {
        str[n - 1] = '\0';
    }
    return word_length;
}
int mthrfckr4(int argc, char *argv[]) {  // Tohle je jakoby main
    FILE *file = stdin;
    int length = 0;
    int loaded_length = 0;

    if(argc < 2) {
        fprintf(stderr, "Neplatný počet argumentů\n");
        return 1;
    }
    length = atoi(argv[1]);
    if(argc >= 3) {
        file = fopen(argv[2], "r");
        if(file == NULL) {
            fprintf(stderr, "Nepodařilo se otevřít soubor\n");
            return 1;
        }
    }

    char buffer[WORD_LENGTH];
    do {
        loaded_length = ReadWord2(file, buffer, WORD_LENGTH);
        if(loaded_length >= length - 1 && loaded_length <= length + 1) {
            printf("%d %s\n", loaded_length, buffer);
        }
    } while(loaded_length != EOF);

    if(argc >= 3) {
        fclose(file);
    }

    return 0;
}

// 5) Napište funkci
//
//       bool Edit(char *Str, int Max, unsigned Pos, unsigned N, const char *Ins)
//    
//   která v řetězci Str zamění N znaků od pozice Pos za obsah řetězce Ins.
//   Funkce vrací true, pokud dojde k úspěšnému zapsání všech znaků řetězce
//   Ins. Předpokládáme, že Str může obsahovat maximálně Max bajtů a pokud by
//   výsledek překročil tuto mez, funkce vrátí false a _nezmění_ Str.
//   (Například: Str="PUK", Max=9, Pos=1, Ins="íse", N=1, výsledek="PíseK", true)
//   Funkce _musí_ zvládnout všechny možné situace, tj. i prázdné řetězce a N==0.
//
//   POZOR: Nesmíte použít žádné standartní funcke kromě strlen() ani žádná
//          pomocná pole (jinak 0b).
//
//   Napište PŘÍKLAD volání této funkce a vhodně zvolenými argumenty (včetně
//   jejich deklarací/definic)
//
bool Edit(char *Str, int Max, unsigned Pos, unsigned N, const char *Ins) {
    if(Str == NULL || Ins == NULL) {
        return false;
    }

    int shift = strlen(Ins) - N;
    if(strlen(Str) + shift >= (unsigned)Max) {
        return false;
    }

    if(shift > 0) {  // Posun doprava
        for(unsigned i = Max - 1; i >= Pos + shift; i--) {
            Str[i] = Str[i - shift];
        }
    }
    if(shift < 0) {  // Posun doleva
        for(unsigned i = Pos; i < (unsigned)Max + shift; i++) {
            Str[i] = Str[i - shift];
        }
    }
    for(size_t i = 0; i < strlen(Ins); i++) {
        Str[Pos + i] = Ins[i];
    }

    return true;
}
void mthrfckr5() {
    char buffer[10] = "PUK";
    printf("%s -> ", buffer);
    Edit(buffer, 10, 1, 1, "ise");
    printf("%s\n", buffer);

    printf("%s -> ", buffer);
    Edit(buffer, 10, 1, 3, "U");
    printf("%s\n", buffer);

    printf("%s -> ", buffer);
    Edit(buffer, 10, 3, 0, "ER");
    printf("%s\n", buffer);

    printf("%s -> ", buffer);
    Edit(buffer, 10, 2, 0, "N");
    printf("%s\n", buffer);
}

// 6) Napište program 
//       SwapColCSV číslo_sloupce1 číslo_sloupce2 [CVSsoubor]
//    který z CSV souboru zadaného jako třetí argument programu (není-li zadán
//    použije stdin) čte CSV-položky a na stdout tiskne obsah CSV souboru s 
//    navzájem zaměněnými (swap) sloupci zadanými jako první dva argumenty
//    programu (číslo_sloupce1 a číslo sloupce2). Položky na řádku i řádky
//    číslujeme od 1. Můžete omezit maximální počet položek na jednom řádku 
//    na 1024. Na stderr program nakonec vytiskne celkový počet zpracovaných
//    řádků.
//
//    Pro čtení jedné položky z CSV souboru musíte napsat funkci 
//  
//       int ReadCSVItem(FILE *f, char Delimiter, char *Str, unsigned m)
// 
//    která načte další položku ze souboru f do řetězce Str, kam uloží
//    maximálně m bajtů (vhodně zvolte). Pokud je položka delší, přečte jí 
//    celou, ale uloží jen prvních m-1 znaků. Musíte číst pomocí fgetc(f).
//    Znak Delimiter je zadaný oddělovač položek CSV souboru.
//    Funkce vrací jednu z následujících hodnot:
//     - (vámi správně definovanou) konstanu EOL pro poslední položku řádku
//     - standardní konstatnu EOF když je konec souboru
//     - jinak vrací 0
//
//    Poznámka: CSV (Coma Separated Value) = na řádku jsou položky-řetězce
//    oddělené speciálním oddělovacím znakem (použijte středník), pro naše
//    účely předpokládáme, že nikdy neoobsahují tento oddělovač. 
//    Příklad vstupníjho řádku: položka1;položka2; ... ;položka100
//
#define WORD_LENGTH 128
#define LINE_MAX 1024
int ReadCSVItem(FILE *f, char Delimiter, char *Str, unsigned m) {
    if(f == NULL || Str == NULL) {
        return 0;
    }
    int loaded_char;
    unsigned word_length = 0;

    // Načtení znaků
    while((loaded_char = fgetc(f)) != Delimiter) {
        if(loaded_char == EOF) {
            if(word_length < m) {
                Str[word_length] = '\0';
            } else {
                Str[m - 1] = '\0';
            }
            return EOF;
        }
        if(loaded_char == '\n') {
            if(word_length < m) {
                Str[word_length] = '\0';
            } else {
                Str[m - 1] = '\0';
            }
            return -2;
        }
        if(word_length < m - 1) {
            Str[word_length] = loaded_char;
        }
        word_length++;
    }

    if(word_length < m) {
        Str[word_length] = '\0';
    } else {
        Str[m - 1] = '\0';
    }
    return 0;
}
int mthrfckr6(int argc, char *argv[]) {
    FILE *f = stdin;    
    int a_column = 0;
    int b_column = 0;    
    char *buffers[LINE_MAX + 1];
    int read_return;
    int word_index = 0;
    int lines_count = 0;

    if(argc < 3) {
        fprintf(stderr, "Neplatný počet argumentů.\n");
        return 1;
    }
    a_column = atoi(argv[1]);
    b_column = atoi(argv[2]);
    if(argc >= 4) {
        f = fopen(argv[3], "r");
        if(f == NULL) {
            fprintf(stderr, "Nepodařilo se otevřít soubor\n");
            return 1;
        }
    }
    if(a_column < 1 || a_column > LINE_MAX) {
        fprintf(stderr, "Číslo pvního sloupce je mimo meze\n");
        return 1;
    }
    if(b_column < 1 || b_column > LINE_MAX) {
        fprintf(stderr, "Číslo druhého sloupce je mimo meze\n");
        return 1;
    }
    a_column--;
    b_column--;

    for(int i = 0; i <= LINE_MAX; i++) {
        buffers[i] = malloc(WORD_LENGTH);
        if(buffers[i] == NULL) {
            for(int r = i; i >= 0; i--) {
                free(buffers[r]);
            }
            fprintf(stderr, "Nepodařilo se alokovat místo v paměti\n");
            return 1;
        }
    }
    
    do {
        read_return = ReadCSVItem(f, ';', buffers[LINE_MAX], WORD_LENGTH);

        if(word_index != a_column && word_index != b_column) {
            strcpy(buffers[word_index], buffers[LINE_MAX]);
        } else if(word_index == a_column) {
            strcpy(buffers[b_column], buffers[LINE_MAX]);
        } else if(word_index == b_column) {
            strcpy(buffers[a_column], buffers[LINE_MAX]);
        }

        word_index++;
        if(read_return == -2 || read_return == EOF) {
            for(int i = 0; i < word_index; i++) {
                printf("%s ", buffers[i]);
            }
            printf("\n");
            word_index = 0;
            lines_count++;
        }        
    } while(read_return != EOF);
    fprintf(stderr, "%d\n", lines_count);

    for(int i = 0; i <= LINE_MAX; i++) {
        free(buffers[i]);
    }
    if(argc >= 4) {
        fclose(f);
    }
    return 0;
}

// 7) Napište funkci
//
//       int ReplaceSP(char *Str, int Max, const char *s2);
//
//    která v řetězci Str zamění _poslední_ sekvenci mezer (délky 1..x) za 
//    obsah řetězce s2 (může být i prázdný). Funkce vrací délku sekvence
//    mezer, pokud dojde k úspěšné záměně, jinak vrací délku nulu. Str může
//    obsahovat maximálně Max bajtů a pokud by výsledek překročil tuto mez, 
//    funkce vrátí nulu a _nezmění_ Str.
//    Příklad: Str="text  text", Max=99, s2="XXX", výsledek="textXXXtext", 2
//
//    Musíte napsat a použít pomocnou funkci 
//       const char *SearchSP(const char *Str, int *ptr);
//    která vrátí pozici _poslední_ sekvence mezer ve Str nebo NULL v 
//    případě neúspěchu. Funkce přes ukazatel ptr vrátí také délku 
//    nalezené sekvence (jen když ptr!=NULL).
//
//    Obě funkce musí zvládnout i prázdné řetězce.
//    POZOR: Nesmíte použít žádné standardní funkce krom strlen() ani žádná
//           pomocná pole (jinak 0b).
//
//    Napište příkald volání ReplaceSP() s vhodně zvolenými argumenty
//    (včetně jejich deklarací/definicí)
//

const char *SearchSP(const char *Str, int *ptr)
{
        if(Str == NULL)
            return NULL;
        if(strlen(Str) == 0)
            return NULL;
        int index = strlen(Str) - 1;
        int len = 0;
        bool space = false;
        while(index >= 0 && Str[index] != ' ')
            --index;
        while(index >= 0 && Str[index] == ' ')
        {
            space = true;
            ++len;
            --index;
        }
        if(!space)
            return NULL;
        return &(Str[index + 1]);
}


const char *SearchSP(const char *Str, int *ptr) {
    if(Str == NULL) {
        return NULL;
    }
    if(strlen(Str) == 0) {
        return NULL;
    }
    
    const char *return_char = NULL; // Ukazatel na konstatní char ne konstatní ukazatel na char
    int space_length = 0;
    bool refresh = true;

    for(size_t i = 0; i < strlen(Str); i++) {
        if(Str[i] == ' ') {
            if(refresh) {
                return_char = &(Str[i]);
                space_length = 0;
                refresh = false;
            }
            space_length++;
        } else {
            refresh = true;
        }
    }

    if(ptr != NULL) {
        *ptr = space_length;
    }

    return return_char;
}
int ReplaceSP(char *Str, int Max, const char *s2) {
    if(Str == NULL || s2 == NULL) {
        return 0;
    }

    int space_length;
    char *replace = (char *)SearchSP(Str, &space_length);
    if(replace == NULL) {
        return 0;
    }
    int shift = strlen(s2) - space_length;
    

    if(shift > 0) {  // Posun doprava
        if(strlen(Str) + shift >= (unsigned)Max) {
            return 0;
        }

        for(int i = Max - 1; i >= 0; i--) {
            if(&(Str[i - shift]) == replace) {
                break;
            }
            Str[i] = Str[i - shift];
        }
    }
    if(shift < 0) {  // Posun doleva
        for(int i = 0; i < Max - 1; i++) {
            replace[i] = replace[i - shift];
            if(replace[i - shift] == '\0') {
                break;
            }
        }
    }
    for(size_t i = 0; i < strlen(s2); i++) {
        replace[i] = s2[i];
    }

    return space_length;
}
void mthrfckr7() {
    char buffer[40] = "text text      text  text";
    printf("%s -> ", buffer);
    ReplaceSP(buffer, 40, "XXX");
    printf("%s\n", buffer);

    printf("%s -> ", buffer);
    ReplaceSP(buffer, 40, "A");
    printf("%s\n", buffer);

    printf("%s -> ", buffer);
    ReplaceSP(buffer, 40, "PUSSY");
    printf("%s\n", buffer);
}

// 8) Napište program CONVERT, který čte ze zadaného souboru (první
//    argument programu, není-li zadán, čte stdin) znaky a opisuje je na
//    stdout tak, že všechny sekvence velkých písmen A-Z (isupper) v textu
//    nahradí za jejich reverzi (znaky pozpátku, napište si funkci strrev).
//
//    Pro kopii ne A-Z znaků napište funci
//
//       int CopyNonUPPER(FILE *in, FILE *out);
//
//    která kopíruje až po první znak A-Z, který nezpracuje - použijte 
//    ungetc(c, in). Pokud narazí na konec souboru, vrací EOF, jinak 0.
//
//    Pro čtení sekvence A-Z ze souboru musíte napsat funkci
//
//       int ReadUPPER(char *s, unsigned m, FILE *f);
//
//    která přečte znaky A-Z ze souboru f do _řetězce_ s, kam uloží maximálně
//    m bajtů. Pokud je sekvence delší, hlásí chybu na stderr a _ukončí_ 
//    program. Nesmíte použít fscanf(). Funkce vrací délku přečtené sekvence 
//    A-Z (1..m-1).
//
#define WORD_LENGTH 128
void strrev(char *str) {
    if(str == NULL) {
        return;
    }

    char temp[strlen(str) + 1];
    strcpy(temp, str);
    for(int i = strlen(str) - 1; i >= 0; i--) {
        str[i] = temp[strlen(str) - 1 - i];
    }
}
int CopyNonUPPER(FILE *in, FILE *out) {
    if(in == NULL || out == NULL) {
        return 0;
    }

    int loaded_char;
    while((loaded_char = fgetc(in)) != EOF) {
        if(!isupper(loaded_char)) {
            fputc(loaded_char, out);
        } else {
            ungetc(loaded_char, in);
            return 0;
        }
    }

    return EOF;
}
int ReadUPPER(char *s, unsigned m, FILE *f) {
    if(s == NULL || f == NULL) {
        return 0;
    }

    unsigned seq_length = 0;
    int loaded_char;

    while(isupper(loaded_char = fgetc(f))) {
        if(loaded_char == EOF) {
            s[seq_length] = '\0';
            return EOF;
        }
        if(seq_length >= m - 1) {
            fprintf(stderr, "Přetečení bufferu");
            exit(1);
        }
        s[seq_length] = loaded_char;
        seq_length++;
    }
    ungetc(loaded_char, f);
    s[seq_length] = '\0';

    return seq_length;
}
int mthrfckr8(int argc, char *argv[]) {
    FILE *f = stdin;
    char buffer[WORD_LENGTH];
    int read_return;

    if(argc >= 2) {
        f = fopen(argv[1], "r");
        if(f == NULL) {
            fprintf(stderr, "Nepodařilo se otevřít soubor\n");
            return 1;
        }
    }

    while(CopyNonUPPER(f, stdout) != EOF) {
        read_return = ReadUPPER(buffer, WORD_LENGTH, f);
        strrev(buffer);
        printf("%s", buffer);
        if(read_return == EOF) {
            break;
        }
    }

    return 0;
}

// 9) Napište funkci
//       
//       int WordReplace(char *Str, int Max, const char *s2);
//
//    která v řetězci Str zamění _první_ slovo (sekvenci znaků isalpha) za
//    obsah řetězce s2 (může být i prázdný). Funkce vrací délku slova pokud 
//    dojde k úspěšné záměně, jinak vrací nulu. Str může obsahovat maximálně 
//    Max bajtů a pokud by výsledek překročil tuto mez, funkce vrátí nulu a 
//    _nezmění_ Str.
//    (Příklad: Str:"_abc_def_", Max=99, s2="XX", výsledek="_X_def_", 3)
//   
//    Musíte napsat a použít pomocnou funkci
//       const char *WordSearch(const char *Str, int *ptr);
//    která vrátí pozici _první_ sekvence isalpha znaků ve Str nebo NULL v
//    případě neúspěchu. Funkce přes ukazatel ptr vrátí také délku nalezené
//    sekvence (jen když ptr!=NULL).
//
//    Obě funkce _musí_ zvládnout i prázdné řetězce.
//    POZOR: Nesmíte použít žádné standartní funkce kromě strlen(), isalpha()
//           ani žádná pomocná pole (jinak 0b).
//
//    Napište příklad volání WordReplac() s vhodně zvolenými argumenty
//    (včetně jejich) deklarací/definic).
//
const char *WordSearch(const char *Str, int *ptr) {
    if(Str == NULL) {
        return NULL;
    }
    size_t start = 0;
    int length = 0;

    while(start < strlen(Str)) {
        if(isalpha(Str[start])) {
            break;
        }
        start++;
    }
    for(size_t i = start; i < strlen(Str); i++) {        
        if(!isalpha(Str[i])) {
            if(ptr != NULL) {
                *ptr = length;                
            }
            return &(Str[start]);
        }        
        length++;
        if(i == (strlen(Str) - 1)) {
            if(ptr != NULL) {
                *ptr = length;
            }
            return &(Str[start]);
        }
    }
    return NULL;
}
int WordReplace(char *Str, int Max, const char *s2) {
    if(Str == NULL || s2 == NULL) {
        return 0;
    }

    int word_length = 0;    
    char *replace = (char *)WordSearch(Str, &word_length);    
    if(replace == NULL) {
        return 0;
    }
    int shift = strlen(s2) - word_length;

    if(shift > 0) {  // Posun doprava
        if(strlen(Str) + shift >= (unsigned)Max) {
            return 0;
        }

        for(int i = Max - 1; i >= 0; i--) {
            if(&(Str[i - shift]) == replace) {
                break;
            }
            Str[i] = Str[i - shift];
        }
    }
    if(shift < 0) {  // Posun doleva
        for(int i = 0; i < Max - 1; i++) {
            replace[i] = replace[i - shift];         
            if(replace[i - shift] == '\0') {
                break;
            }
        }
    }

    for(size_t i = 0; i < strlen(s2); i++) {
        replace[i] = s2[i];
    }

    return word_length;
}
void mthrfckr9() {
    char buffer[40] = "_abc_def_";
    printf("%s -> ", buffer);
    WordReplace(buffer, 40, "XX");
    printf("%s\n", buffer);

    printf("%s -> ", buffer);
    WordReplace(buffer, 40, "A");
    printf("%s\n", buffer);

    printf("%s -> ", buffer);
    WordReplace(buffer, 40, "TITS");
    printf("%s\n", buffer);
}

//10) Napiště program REVERSE_WORDS který čte ze zadaného souboru (první
//    argument programu) slova a tiskne je obráceně ("abc"->"cba") do souboru
//    stejného jména s přidanou připonou ".out". Na obrácení slova máte k 
//    dispozici funkci strrev(char *str); Není-li soubor zadán, čte ze stdin
//    a zapisuje na stdout. Slovo je souvislá posloupost písmen --- použijte
//    isalpha(). Pro čtení slova ze souboru napište funkci:
//
//       int read_word(FILE *f, char *Str, size_t m);
//
//    která přeskočí oddělovače a čte slovo ze souboru f do řetězce Str, kam
//    uloží maximálně m znaků. Pokud je slovo delší hlásí chybu na stderr a 
//    ukončí program. Nesmíte použít fscanf(). Funkce vrací délku nebo EOF,
//    když narazí na konec souboru.
//
#define WORD_LENGTH 128
int read_word(FILE *f, char *Str, size_t m) {
    if(f == NULL || Str == NULL) {
        return 0;
    }

    unsigned word_length = 0;
    int loaded_char;

    // Přeskočení bílých znaků
    while(!isalpha(loaded_char = fgetc(f)) && loaded_char != EOF);

    // Načtení znaků
    do {
        if(loaded_char == EOF) {
            Str[word_length] = '\0';
            return EOF;
        }
        if(word_length >= m - 1) {
            fprintf(stderr, "Přetečení bufferu\n");
            exit(1);
        }

        Str[word_length] = loaded_char;
        word_length++;
    } while(isalpha(loaded_char = fgetc(f)));

    Str[word_length] = '\0';
    return word_length;
}
int mthrfckr10(int argc, char *argv[]) {
    FILE *in = stdin;
    FILE *out = stdout;
    char buffer[WORD_LENGTH];
    int read_return;

    if(argc >= 2) {
        in = fopen(argv[1], "r");
        if(in == NULL) {
            fprintf(stderr, "Nepodařilo se otevřít soubor\n");
            return 1;
        }

        char name[strlen(argv[1]) + 5];
        strcpy(name, argv[1]);
        strcat(name, ".out");
        out = fopen(name, "w");
        if(out == NULL) {
            fclose(in);
            fprintf(stderr, "Nepodařilo se otevřít soubor\n");
            return 1;
        }
    }
    do {
        read_return = read_word(in, buffer, WORD_LENGTH);
        strrev(buffer);
        fprintf(out, "%s ", buffer);
    } while(read_return != EOF);

    return 0;
}

//                                                                            //
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////// MAIN ////////////////////////////////////
//                                                                            //

int main() {
    float temp[9][10];

    printf("++ Expr1: %c\n", expr1());
    printf("++ Expr2: nope\n");
    printf("++ Expr3: %d\n", expr3());
    printf("++ Expr4: %d\n", expr4());
    printf("++ Expr5: nope\n");
    printf("++ Swit1: %d\n", swit1());
    printf("++ Swit2: %d\n", swit2());
    printf("++ Swit3: %d\n", swit3());
    printf("++ f1: %ld\n", f1(temp));
    printf("++ f2: %c\n", f2());
    printf("++ f3: %c\n", f3());
    printf("++ f4: %c\n", f4(3));
    printf("++ f5: %c\n", f5(4));
    printf("++ f6: %c\n", f6());
    printf("++ f7: %c\n", f7());
    printf("++ f8: %c\n", f8());
    printf("++ f9: %c\n", f9());
    printf("++ f10: %c\n", f10());
    printf("++ f11: %c\n", f11());
    printf("++ main1: %d\n", main1());
    printf("++ main2: %d\n", main2());
    printf("\n");

    printf("++ shrshi1:\n");
    shrshi1();
    printf("++ shrshi2:\n");
    shrshi2();
    printf("++ shrshi3:\n");
    shrshi3();
    printf("\n");

    printf("++ mac1:\n");
    mac1();
    printf("++ mac2:\n");
    mac2();
    printf("++ mac3:\n");
    mac3();
    printf("++ mac4:\n");
    mac4();

    printf("++ mthrfckr1:\n");
    mthrfckr1();
    printf("++ mthrfckr2:\n");
    char *args1[] = { "mthrfckr2", "file1" };
    printf("returns: %d\n", mthrfckr2(2, args1));
    printf("++ mthrfckr3:\n");
    mthrfckr3();
    printf("++ mthrfckr4:\n");
    char *args2[] = { "mthrfckr4", "4", "file2" };
    mthrfckr4(3, args2);
    printf("++ mthrfckr5:\n");
    mthrfckr5();
    printf("++ mthrfckr6:\n");
    char *args3[] = { "mthrfckr6", "2", "4", "file3" };
    mthrfckr6(4, args3);
    printf("++ mthrfckr7:\n");
    mthrfckr7();
    printf("++ mthrfckr8:\n");
    char *args4[] = { "mthrfckr8", "file4" };
    mthrfckr8(2, args4);
    printf("++ mthrfckr9:\n");
    mthrfckr9();
    printf("++ mthrfckr10:\n");
    char *args5[] = { "mthrfckr10", "file5" };
    mthrfckr10(2, args5);

    return 0;
}

//                                                                            //
////////////////////////////////////////////////////////////////////////////////
// This is the end, hold your breath and count to 90 minutes, uuuu you need to 
// act a fool arrr, cause hit or miss, guess pepe never miss, leg huh, 
// everything is too late, everything is too late, everything is too late and
// everything is too late, im your light, Tokyo by night, i wonder if you know,
// how they live in FIT, if you seen it, then you mean it, then you know you have 
// to go, mother looking at me, tell me what do you see, YES Ive lost my mind,
// hmmm where is my mind, where is my mind, where is my mind, maybe its in the 
// gutter, where i left my lover, what an expensive fate, well here we are
// dont turn away now.
//
// Optimální rozdělení času:
// Baity:               5  minut
// Deklarace, definice: 10 minut
// Makro:               15 minut
// 1. dlouhej příklad:  30 minut
// 2. dlouhej příklad:  30 minut
