// modul2.c
extern int x;     // Proměnná x by měla bejt někde jinde ale nemusí protože se nepoužívá
int main(void) {
    return y;     // Tady se používá proměnná y o který se nic neví takže zase střelba no nohy nelze zkompilovat
}
