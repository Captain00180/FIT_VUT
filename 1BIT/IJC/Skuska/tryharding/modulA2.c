// modul2.c
static int x;     // Proměnná x neviditelná pro ostatní moduly. Je globální takže je nulovaná
//extern int x;   // Takhle by se použila ta z druhého modulu
int main(void) {
    return x;     // Použije tato statická promměná 
}
