/**/
/*
 *  P�edm�t: Algoritmy (IAL) - FIT VUT v Brn�
 *  Pokro�il� testy pro p��klad c201.c (Jednosm�rn� v�zan� line�rn� seznam)
 *  Vytvo�il: Martin Tu�ek, z��� 2005
 *  �prava: Bohuslav K�ena, ��jen 2006
 */

#include "c201.h"
                                                         /* pracovn� prom�nn� */
tList TEMPLIST;
int obsah;
int MaxListLength = 100;                     /* Handles wrongly linked lists. */

/*******************************************************************************
 * Pomocn� funkce usnad�uj�c� testov�n� vlastn� implementace.
 ******************************************************************************/

void print_elements_of_list(tList SEZNAM)	{
/* Vytiskne seznam. */
	tList temp_S=SEZNAM;
	int CurrListLength = 0;
	printf("-----------------");
	while ((temp_S.First!=NULL) && (CurrListLength<MaxListLength))	{
		printf("\n\t %d",temp_S.First->data);
		if ((temp_S.First==SEZNAM.Act) && (SEZNAM.Act!=NULL))
			printf("\t <= toto je aktivn� prvek ");
		temp_S.First=temp_S.First->ptr;
		CurrListLength++;
	}
    if (CurrListLength>=MaxListLength)
        printf("\nList exceeded maximum length!");
	printf("\n-----------------\n");
}

int use_copy(tList *TL, int *obsah)	{
/* O�et�uje pou�it� operace Copy. */
	int tmp;
	Copy(TL,&tmp);
	if (!solved) {
		printf("Operace Copy nebyla implementov�na!\n");
		return(FALSE);
	}
	else {
		if (errflg)	{
			printf("Operace Copy volala funkci Error.\n");
			errflg=FALSE;
			return(FALSE);
		}
		else	{
			*obsah=tmp;
			printf("Operace Copy vrac� obsah %d.\n",tmp);
			return(TRUE);
		}
	}
}

int use_copy_first(tList *TL, int *obsah)	{
/* O�et�uje pou�it� operace CopyFirst. */
	int tmp;
	CopyFirst(TL,&tmp);

	if (!solved)	{
		printf("Operace CopyFirst nebyla implementov�na!\n");
		return(FALSE);
	}
	else {
		if (errflg)	{
			printf("Operace CopyFirst volala funkci Error.\n");
			errflg=FALSE;
			return(FALSE);
		}
		else	{
			*obsah=tmp;
			printf("Operace CopyFirst vrac� obsah %d.\n",tmp);
			return(TRUE);
		}
	}
}

int use_active(tList TL)	{
/* O�et�uje pou�it� operace Active. */
	int IsActive = Active(&TL);
	if (!solved)	{
		printf("Operace Active nebyla implementov�na!\n");
		return(FALSE);
	}
	else	{
		printf("Operace Active vrac� %d.\n",IsActive);
		return(TRUE);
	}
}

/*
 * N�sleduj�c� funkce volan� z vlastn�ch test� uveden�ch ve funkci main
 * kontroluj�, zda byly jednotliv� funkce implementov�ny,
 * p��padn� vypisuj� aktu�ln� stav pracovn�ho seznamu TEMPLIST.
 */

int test_InitList()	{

	solved=TRUE;
	InitList(&TEMPLIST);
	if (!solved)	{
		printf("Operace InitList nebyla implementovana \n");
		return(FALSE);
	}
	else	{
		print_elements_of_list(TEMPLIST);
		return(TRUE);
	}

}

int test_Copy()	{

	solved=TRUE;
	return(use_copy(&TEMPLIST,&obsah));

}

int test_CopyFirst()	{

	solved=TRUE;
	return(use_copy_first(&TEMPLIST,&obsah));

}

int test_InsertFirst()	{

	solved=TRUE;
	InsertFirst(&TEMPLIST,obsah);
	if (!solved)	{
		printf("Operace InsertFirst nebyla implementov�na!\n");
		return(FALSE);
	}
	else	{
		print_elements_of_list(TEMPLIST);
		return(TRUE);
	}

}

int test_First()	{

	solved=TRUE;
	First(&TEMPLIST);
	if (!solved)	{
		printf("Operace First nebyla implementov�na!\n");
		return(FALSE);
	}
	print_elements_of_list(TEMPLIST);
	return(TRUE);

}

int test_Active()	{

	solved=TRUE;
	return(use_active(TEMPLIST));

}

int test_Succ()	{

	solved=TRUE;
	Succ(&TEMPLIST);
	if (!solved)	{
		printf("Operace Succ nebyla implementov�na!\n");
		return(FALSE);
	}
	print_elements_of_list(TEMPLIST);
	return(TRUE);

}

int test_Actualize()	{

	solved=TRUE;
	Actualize(&TEMPLIST,obsah);
	if (!solved)	{
		printf("Operace Actualize nebyla implementov�na!\n");
		return(FALSE);
	}
	print_elements_of_list(TEMPLIST);
	return(TRUE);

}

int test_DeleteFirst()	{

	solved=TRUE;
	DeleteFirst(&TEMPLIST);
	if (!solved)	{
		printf("Operace DeleteFirst() nebyla implementov�na!\n");
		return(FALSE);
	}
	print_elements_of_list(TEMPLIST);
	return(TRUE);

}

int test_PostDelete()	{

	solved=TRUE;
	PostDelete(&TEMPLIST);
	if (!solved)	{
		printf("Operace PostDelete() nebyla implementov�na!\n");
		return(FALSE);
	}
	print_elements_of_list(TEMPLIST);
	return(TRUE);

}

int test_PostInsert()	{

	solved=TRUE;
	PostInsert(&TEMPLIST,obsah);
	if (!solved){
		printf("Operace PostInsert nebyla implementov�na!\n");
		return(FALSE);
	}
	print_elements_of_list(TEMPLIST);
	return(TRUE);

}

int test_DisposeList() {

    solved=TRUE;
    DisposeList(&TEMPLIST);
    if (!solved) {
        printf("Operace DisposeList() nebyla implementov�na!\n");
        return(FALSE);
    }
    print_elements_of_list(TEMPLIST);
    return(TRUE);
}

/*******************************************************************************
 * POKRO�IL� TESTY
 * ---------------
 * Nejsou dostupn� student�m p�i �e�en� dom�c�ch �loh.
 * Za jejich �sp�n� proj�t� z�sk� student druhou ��st bod� za p��klad.
 *
 ******************************************************************************/

int main(int argc, char *argv[])	{

    printf("Jednosm�rn� v�zan� line�rn� seznam\n");
    printf("==================================\n");

                            /* Testy 01 a� 09 se shoduj� se z�kladn�mi testy. */

    printf("\n[TEST01]\n");
    printf("Inicializace seznamu\n");
    printf("~~~~~~~~~~~~~~~~~~~~\n");
    test_InitList();

    printf("\n[TEST02]\n");
    printf("Pokus o vol�n� CopyFirst nad pr�zdn�m seznamem => chyba\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_CopyFirst();

    printf("\n[TEST03]\n");
    printf("Zavol�me 4x operaci InsertFirst.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    obsah=1; test_InsertFirst();
    obsah=2; test_InsertFirst();
    obsah=3; test_InsertFirst();
    obsah=4; test_InsertFirst();

    printf("\n[TEST04]\n");
    printf("Seznam je neaktivn� -- ov���me si to vol�n�m funce Active.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_Active();

    printf("\n[TEST05]\n");
    printf("Otestujeme funkci First p�i neaktivn�m seznamu a funkci Active.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_First();
    test_Active();

    printf("\n[TEST06]\n");
    printf("Test funkce Copy p�i aktivit� na prvn�m prvku\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_Copy();

    printf("\n[TEST07]\n");
    printf("Test funkce Succ -- vol�me 3x, aktivita bude na posledn�m prvku.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_Succ();
    test_Succ();
    test_Succ();
    test_Active();

    printf("\n[TEST08]\n");
    printf("Aktualizujeme obsah aktivn�ho prvku.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    obsah=10;
    test_Actualize();
    test_Active();
    test_Copy();

    printf("\n[TEST09]\n");
    printf("Provedeme je�t� jednou Succ -- aktivita se ztrat�.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_Succ();
    test_Active();

           /* Testy 10 a� 14 testuj� chov�n� operac� nad neaktivn�m seznamem. */

    printf("\n[TEST10]\n");
    printf("Pokus�me se o aktualizaci p�i neaktivn�m seznamu => nic\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    obsah=100;
    test_Actualize();
    test_Active();

    printf("\n[TEST11]\n");
    printf("Pokus o Copy p�i neaktivn�m seznamu => o�et�en� chyba\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_Copy();

    printf("\n[TEST12]\n");
    printf("Operace Succ p�i neaktivn�m seznamu nesm� zhavarovat.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_Succ();
    test_Active();

    printf("\n[TEST13]\n");
    printf("Pou�it� operace CopyFirst p�i neaktivn�m seznamu\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_CopyFirst();

    printf("\n[TEST14]\n");
    printf("Vyzkou��me operaci DeleteFirst p�i neaktivn�m seznamu,\n");
    printf("p�i�em� smazan� prvek zase vr�t�me zp�tky do seznamu.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DeleteFirst();
    test_InsertFirst();
    test_Active();

                   /* Testy 15 a� 23 se shoduj� se z�kladn�mi testy 10 a� 18. */

    printf("\n[TEST10]\n");
    printf("Operace First nastav� aktivitu na prvn� prvek.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_First();
    test_Active();

    printf("\n[TEST11]\n");
    printf("DeleteFirst aktivn�ho prvku povede ke ztr�t� aktivity.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DeleteFirst();
    test_Active();

    printf("\n[TEST12]\n");
    printf("U�it�m operac� First a Succ nastav�me aktivitu na konec seznamu.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_First();
    test_Succ();
    test_Succ();
    test_Active();

    printf("\n[TEST13]\n");
    printf("Operace PostDelete p�i aktivit� na posledn�m prvku ned�l� nic.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_PostDelete();
    test_Active();

    printf("\n[TEST14]\n");
    printf("Nastav�me aktivitu na za��tek a dvakr�t zavol�me PostDelete.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_First();
    test_Active();
    test_PostDelete();
    test_PostDelete();
    test_Active();

    printf("\n[TEST15]\n");
    printf("Otestujeme InsertFirst p�i seznamu s jedin�m prvkem, nastav�me\n");
    printf("aktivitu na nov� vlo�en� prvek a op�t posuneme aktivitu na konec\n");
    printf("seznamu.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    obsah=101;
    test_InsertFirst();
    test_First();
    test_Succ();
    test_Active();

    printf("\n[TEST16]\n");
    printf("Operac� PostInsert vlo��me nov� prvek za posledn� prvek seznamu.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    obsah=102;
    test_PostInsert();
    test_Active();

    printf("\n[TEST17]\n");
    printf("Nastav�me aktivitu na prvn� prvek seznamu a vyzkou��me PostInsert.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_First();
    obsah=103;
    test_PostInsert();
    test_Active();

    printf("\n[TEST18]\n");
    printf("Otestujeme funk�nost operace DisposeList.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DisposeList();

             /* Testy 24 a� 30 testuj� chov�n� operac� nad pr�zdn�m seznamem. */

    printf("\n[TEST24]\n");
    printf("\n");
    printf("N�sleduje testov�n� operac� p�i pr�zdn�m seznamu\n");
    printf("================================================\n");
    test_Active();

    printf("\n[TEST25]\n");
    printf("DeleteFirst p�i pr�zdn�m seznamu => nic\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DeleteFirst();

    printf("\n[TEST26]\n");
    printf("Test PostDelete p�i pr�zdn�m seznamu => nic \n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n");
    test_PostDelete();

    printf("\n[TEST27]\n");
    printf("Je�t� jednou DisposeList => ��dn� zm�na\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DisposeList();

    printf("\n[TEST28]\n");
    printf("First ani PostInsert nad pr�zdn�m seznamem nic ned�l�.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_First();
    obsah=201;
    test_PostInsert();

    printf("\n[TEST29]\n");
    printf("Copy a CopyFirst nad pr�zdn�m seznamem => o�et�en� chyba\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_Copy();
    test_CopyFirst();

    printf("\n[TEST30]\n");
    printf("Actualize ani Succ by nem�ly m�t nad pr�zdn�m seznamem ��dny efekt.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    obsah=202;
    test_Actualize();
    test_Succ();
    test_Active();

    printf("\n----------------------- konec p��kladu c201 -------------------------\n");


	return(0);
}
/**/

