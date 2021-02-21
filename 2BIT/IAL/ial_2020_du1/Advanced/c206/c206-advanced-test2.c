/* Soubor:   c206-bigtest.c
 * Datum:    16.10.2009
 * Autor:    Petr Novohradsk�, xnovoh01
 *           xnovoh01@stud.fit.vutbr.cz
 *           Fakulta informa�n�ch technologi�
 *           Vysok� u�en� technick� v Brn�
 * Projekt:  Roz���en� testov�n� �kolu do p�edm�tu IAL, zima 2009
 * Pozn�mky: Encoding ISO-8859-2
 *           Testuje implementaci line�rn�ho dvousm�rn� v�zan�ho seznamu
 *           Nehl�d� p��znak solved -> p�edpokl�d� �e u� jsou hotov� v�echny funkce
 */

// pr�ce se vstupem/v�stupem
#include <stdio.h>

// obecn� funkce jazyka C
#include <stdlib.h>

// typ bool, konstanty true, false
#include <stdbool.h>

//implementovan� seznam
#include "c206.h"

/* Vyp��e seznam prvk� a ov��� v�echny ukazatele
 * Nevyu��v� ji� implementovan� funkce
 */
void VypisPrvku(tDLList Seznam)
{
  if(errflg)//kontrola chyb knihovny
  {
    printf("Posledn� operace hl�s� chybu.\n");
    errflg = false;
  }
  printf("-------------------\n");//Za��tek v�pisu
  if(Seznam.First == NULL)//Seznam je pr�zdn�
  {
    printf("Seznam je pr�zdn�, ukazatele jsou ");
    if((Seznam.Last == NULL)&&(Seznam.Act == NULL))
      printf("spr�vn�.\n");
    else
    {
      printf("�patn�.\n");
      printf("V�echny ukazatele ve struktu�e tDLList mus� b�t NULL.\n");
    }
  }
  else//V seznamu n�co je
  {
    bool AktivniNalezen = false;
    printf("Hodnota Ov��en� Aktivita\n");//Hlavi�ka v�pisu
    tDLElemPtr Prvek, Predchozi;
    Predchozi = NULL;
    Prvek = Seznam.First;
    while(Prvek != NULL)//Projde cel� seznam
    {
      printf("%-8d", Prvek->data);//Tisk hodnoty prvku
      if(Prvek->lptr == Predchozi)//ov��� platnost ukazatele na p�edchoz� prvek
        printf("OK      ");
      else
        printf("ERR lptr");
      if(Prvek == Seznam.Act)//Ov��� aktivitu
      {
        AktivniNalezen = true;
        printf("Aktivn� prvek");
      }
      printf("\n");
      Predchozi = Prvek;
      Prvek = Prvek->rptr;
    }
    if(Seznam.Last != Predchozi)
      printf("Ukazatel na posledn� prvek je �patn�!\n");
    printf("Ukazatel na aktivn� prvek ");
    if((AktivniNalezen)||(Seznam.Act == NULL))
      printf("OK\n");
    else
      printf("ukazuje mimo seznam!\n");
  }
  printf("-------------------\n");//Konec v�pisu
}

int main(void)
{
  int pocitadlo = 1;//po��tadlo, plnit se bude v�dy jinou hodnotou
  int vysledek;//Prom�nn� na v�sledek operace
  tDLList Seznam;
  Seznam.Act = (tDLElemPtr)1;//inicializace struktury na jin� ne� standard. hodnoty
  Seznam.First = (tDLElemPtr)1;
  Seznam.Last = (tDLElemPtr)1;
  
  printf("\n*******************\n[TEST 1]\n");
  printf("DLInitList\n");
  DLInitList(&Seznam);
  VypisPrvku(Seznam);
  
  printf("\n*******************\n[TEST 2]\n");
  printf("DLDisposeList - pro pr�zdn� seznam\n");
  DLDisposeList(&Seznam);
  VypisPrvku(Seznam);
  
  printf("\n*******************\n[TEST 3]\n");
  printf("DLFirst - pro pr�zdn� seznam\n");
  DLFirst(&Seznam);
  VypisPrvku(Seznam);
  
  printf("\n*******************\n[TEST 4]\n");
  printf("DLLast - pro pr�zdn� seznam\n");
  DLLast(&Seznam);
  VypisPrvku(Seznam);
  
  printf("\n*******************\n[TEST 5]\n");
  printf("DLCopyFirst - pro pr�zdn� seznam\n");
  vysledek = -1;
  DLCopyFirst(&Seznam, &vysledek);
  printf("V�sledek: %d\n", vysledek);
  VypisPrvku(Seznam);
  
  printf("\n*******************\n[TEST 6]\n");
  printf("DLCopyLast - pro pr�zdn� seznam\n");
  vysledek = -1;
  DLCopyLast(&Seznam, &vysledek);
  printf("V�sledek: %d\n", vysledek);
  VypisPrvku(Seznam);
  
  printf("\n*******************\n[TEST 7]\n");
  printf("DLDeleteFirst - pro pr�zdn� seznam\n");
  DLDeleteFirst(&Seznam);
  VypisPrvku(Seznam);
  
  printf("\n*******************\n[TEST 8]\n");
  printf("DLDeleteLast - pro pr�zdn� seznam\n");
  DLDeleteLast(&Seznam);
  VypisPrvku(Seznam);
  
  printf("\n*******************\n[TEST 9]\n");
  printf("DLInsertFirst - pro pr�zdn� seznam\n");
  DLInsertFirst(&Seznam, pocitadlo++);
  VypisPrvku(Seznam);
  
  printf("\n*******************\n[TEST 10]\n");
  printf("DLInsertFirst - pro nepr�zdn� seznam\n");
  DLInsertFirst(&Seznam, pocitadlo++);
  VypisPrvku(Seznam);
  
  printf("\n*******************\n[TEST 11]\n");
  printf("DLInsertLast - pro nepr�zdn� seznam\n");
  DLInsertLast(&Seznam, pocitadlo++);
  VypisPrvku(Seznam);
  
  printf("\n*******************\n[TEST 12]\n");
  printf("DLCopyFirst - pro nepr�zdn� seznam\n");
  vysledek = -1;
  DLCopyFirst(&Seznam, &vysledek);
  printf("V�sledek: %d\n", vysledek);
  VypisPrvku(Seznam);
  
  printf("\n*******************\n[TEST 13]\n");
  printf("DLCopyLast - pro nepr�zdn� seznam\n");
  vysledek = -1;
  DLCopyLast(&Seznam, &vysledek);
  printf("V�sledek: %d\n", vysledek);
  VypisPrvku(Seznam);
  
  printf("\n*******************\n[TEST 14]\n");
  printf("DLCopy - pro neaktivn� seznam\n");
  vysledek = -1;
  DLCopy(&Seznam, &vysledek);
  printf("V�sledek: %d\n", vysledek);
  VypisPrvku(Seznam);
  
  printf("\n*******************\n[TEST 15]\n");
  printf("DLActualize - pro neaktivn� seznam\n");
  DLActualize(&Seznam, pocitadlo++);
  VypisPrvku(Seznam);
  
  printf("\n*******************\n[TEST 16]\n");
  printf("DLSucc - pro neaktivn� seznam\n");
  DLSucc(&Seznam);
  VypisPrvku(Seznam);
  
  printf("\n*******************\n[TEST 17]\n");
  printf("DLPred - pro neaktivn� seznam\n");
  DLPred(&Seznam);
  VypisPrvku(Seznam);
  
  printf("\n*******************\n[TEST 18]\n");
  printf("DLPostDelete - pro neaktivn� seznam\n");
  DLPostDelete(&Seznam);
  VypisPrvku(Seznam);
  
  printf("\n*******************\n[TEST 19]\n");
  printf("DLPreDelete - pro neaktivn� seznam\n");
  DLPreDelete(&Seznam);
  VypisPrvku(Seznam);
  
  printf("\n*******************\n[TEST 20]\n");
  printf("DLPostInsert - pro neaktivn� seznam\n");
  DLPostInsert(&Seznam, pocitadlo++);
  VypisPrvku(Seznam);
  
  printf("\n*******************\n[TEST 21]\n");
  printf("DLPreInsert - pro neaktivn� seznam\n");
  DLPreInsert(&Seznam, pocitadlo++);
  VypisPrvku(Seznam);
  
  printf("\n*******************\n[TEST 22]\n");
  printf("DLFirst - pro nepr�zdn� seznam\n");
  DLFirst(&Seznam);
  VypisPrvku(Seznam);
  
  printf("\n*******************\n[TEST 23]\n");
  printf("DLCopy - pro aktivn� seznam\n");
  vysledek = -1;
  DLCopy(&Seznam, &vysledek);
  printf("V�sledek: %d\n", vysledek);
  VypisPrvku(Seznam);
  
  printf("\n*******************\n[TEST 24]\n");
  printf("DLActualize - pro aktivn� seznam\n");
  DLActualize(&Seznam, pocitadlo++);
  VypisPrvku(Seznam);
  
  printf("\n*******************\n[TEST 25]\n");
  printf("DLSucc - pro aktivn� seznam\n");
  DLSucc(&Seznam);
  VypisPrvku(Seznam);
  
  printf("\n*******************\n[TEST 26]\n");
  printf("DLPred - pro aktivn� seznam\n");
  DLPred(&Seznam);
  VypisPrvku(Seznam);
  
  printf("\n*******************\n[TEST 27]\n");
  printf("DLPred - pro aktivn� prvn� prvek seznamu\n");
  DLPred(&Seznam);
  VypisPrvku(Seznam);
  
  printf("\n*******************\n[TEST 28]\n");
  printf("DLLast - pro nepr�zdn� seznam\n");
  DLLast(&Seznam);
  VypisPrvku(Seznam);
  
  printf("\n*******************\n[TEST 29]\n");
  printf("DLSucc - pro aktivn� posledn� prvek seznamu\n");
  DLSucc(&Seznam);
  VypisPrvku(Seznam);
  
  printf("\nP�esouv�m aktivitu seznamu na posledn� prvek...\n");
  DLLast(&Seznam);
  
  printf("\n*******************\n[TEST 30]\n");
  printf("DLPostInsert - pro aktivn� posledn� prvek seznamu\n");
  DLPostInsert(&Seznam, pocitadlo++);
  VypisPrvku(Seznam);

  printf("\n*******************\n[TEST 31]\n");
  printf("DLPostInsert - uprost�ed seznamu\n");
  DLPostInsert(&Seznam, pocitadlo++);
  VypisPrvku(Seznam);
  
  printf("\nP�esouv�m aktivitu seznamu na prvn� prvek...\n");
  DLFirst(&Seznam);

  printf("\n*******************\n[TEST 32]\n");
  printf("DLPreInsert - pro aktivn� prvn� prvek seznamu\n");
  DLPreInsert(&Seznam, pocitadlo++);
  VypisPrvku(Seznam);

  printf("\n*******************\n[TEST 33]\n");
  printf("DLPreInsert - uprost�ed seznamu\n");
  DLPreInsert(&Seznam, pocitadlo++);
  VypisPrvku(Seznam);

  printf("\nP�esouv�m aktivitu seznamu na prvn� prvek...\n");
  DLFirst(&Seznam);
  
  printf("\n*******************\n[TEST 34]\n");
  printf("DLDeleteFirst - pro nepr�zdn� seznam, ma�e se aktivn� prvek\n");
  DLDeleteFirst(&Seznam);
  VypisPrvku(Seznam);
  
  printf("\nP�esouv�m aktivitu seznamu na posledn� prvek...\n");
  DLLast(&Seznam);
  
  printf("\n*******************\n[TEST 35]\n");
  printf("DLDeleteLast - pro nepr�zdn� seznam, ma�e se aktivn� prvek\n");
  DLDeleteLast(&Seznam);
  VypisPrvku(Seznam);
  
  printf("\nP�esouv�m aktivitu seznamu na druh� prvek...\n");
  DLFirst(&Seznam);
  DLSucc(&Seznam);
  
  printf("\n*******************\n[TEST 36]\n");
  printf("DLPreDelete - ma�e se prvn� prvek seznamu\n");
  DLPreDelete(&Seznam);
  VypisPrvku(Seznam);
  
  printf("\n*******************\n[TEST 37]\n");
  printf("DLPreDelete - aktivn� prvn� prvek seznamu\n");
  DLPreDelete(&Seznam);
  VypisPrvku(Seznam);
  
  printf("\nP�esouv�m aktivitu seznamu na druh� prvek od konce...\n");
  DLLast(&Seznam);
  DLPred(&Seznam);
  
  printf("\n*******************\n[TEST 38]\n");
  printf("DLPostDelete - ma�e se posledn� prvek seznamu\n");
  DLPostDelete(&Seznam);
  VypisPrvku(Seznam);
  
  printf("\n*******************\n[TEST 39]\n");
  printf("DLPostDelete - aktivn� posledn� prvek seznamu\n");
  DLPostDelete(&Seznam);
  VypisPrvku(Seznam);
  
  printf("\n*******************\n[TEST 40]\n");
  printf("DLPreDelete - uprost�ed seznamu\n");
  DLPreDelete(&Seznam);
  VypisPrvku(Seznam);
  
  printf("\nP�id�v�m prvek na konec seznamu...\n");
  DLInsertLast(&Seznam, pocitadlo++);
  printf("P�esouv�m aktivitu seznamu na prvn� prvek...\n");
  DLFirst(&Seznam);

  printf("\n*******************\n[TEST 41]\n");
  printf("DLPostDelete - uprost�ed seznamu\n");
  DLPostDelete(&Seznam);
  VypisPrvku(Seznam);
  
  printf("\n*******************\n[TEST 42]\n");
  printf("DLDisposeList - pro nepr�zdn� seznam\n");
  DLDisposeList(&Seznam);
  VypisPrvku(Seznam);

  printf("\n*******************\n[TEST 43]\n");
  printf("DLInsertLast - pro pr�zdn� seznam\n");
  DLInsertLast(&Seznam, pocitadlo++);
  VypisPrvku(Seznam);

  printf("\nP�esouv�m aktivitu seznamu na prvn� prvek...\n");
  DLFirst(&Seznam);

  printf("\n*******************\n[TEST 44]\n");
  printf("DLDeleteFirst - maz�n� posledn�ho prvku, prvek je aktivn�\n");
  DLDeleteFirst(&Seznam);
  VypisPrvku(Seznam);

  printf("\nVkl�d�m do seznamu prvek a nastavuji mu aktivitu...\n");
  DLInsertFirst(&Seznam, pocitadlo++);
  DLFirst(&Seznam);
  
  printf("\n*******************\n[TEST 45]\n");
  printf("DLDeleteLast - maz�n� posledn�ho prvku\n");
  DLDeleteLast(&Seznam);
  VypisPrvku(Seznam);
}

