// modul2.c
extern int x;     // Kompilátor ví že někde bude int x buď tady nebo někde jinde
int main(void) {
    return x;     // Pracovat s x lze protože někde bude (díky extern se ví že někde jinde). Po slinkování linker najde x v modulu 1 a x teda je 55
}
