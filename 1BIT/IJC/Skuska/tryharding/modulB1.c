// modul1.c
int x;         // Proměnná x přístupná jiným modulů má hodnotu 0 protože je globání a nuluje se
extern int y;  // Kompilátor ví že někde v jiným modulu by měla bejt proměnná y
