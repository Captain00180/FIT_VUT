// modul2.c
extern int x;     // Kompilátor ví že někde v jiným modulu je proměnná x
int main(void) {
    return y;     // Práce s proměnnou o který se vůbec nic neví. Není deklarovaná tady ani není jako extern že by se měla nacházet v jiným modulu. Nelze zkompilovat. Kulka v noze
}
