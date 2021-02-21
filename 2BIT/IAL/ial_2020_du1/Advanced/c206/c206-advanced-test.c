/**/
/*
 *  P�edm�t: Algoritmy (IAL) - FIT VUT v Brn�
 *  Pokro�il� testy pro p��klad c206.c (Dvousm�rn� v�zan� line�rn� seznam)
 *  Vytvo�il: Martin Tu�ek, z��� 2005
 *  �prava: Bohuslav K�ena, ��jen 2006
 */

int showFirstLast=0;	//Pri zmene na 1 ukazuje prvni a posledni prvek pole 



#include "c206.h"
                                                         /* pracovn� prom�nn� */
tDLList TEMPLIST;
int obsah=1;
int MaxListLength = 100;                     /* Handles wrongly linked lists. */

/*******************************************************************************
 * Pomocn� funkce usnad�uj�c� testov�n� vlastn� implementace.
 ******************************************************************************/

void print_elements_of_list(tDLList SEZNAM)	{

	tDLList temp_S=SEZNAM;
	int CurrListLength = 0;
	printf("-----------------");
	while ((temp_S.First!=NULL)&&(CurrListLength<MaxListLength))	{
		printf("\n \t%d",temp_S.First->data);
		if ((temp_S.First==SEZNAM.Act) && (SEZNAM.Act!=NULL))
			printf("\t <= toto je aktivn� prvek ");
		temp_S.First=temp_S.First->rptr;
		CurrListLength++;
	}
    if (CurrListLength>=MaxListLength)
        printf("\nList exceeded maximum length!");
	printf("\n-----------------\n");
}

int test_DLInitList()	{
	solved=TRUE;
	DLInitList(&TEMPLIST);
	if (!solved)	{
		printf("Operace InitList nebyla implementov�na!\n");
		return(FALSE);
	}
	else	{
		print_elements_of_list(TEMPLIST);
		return(TRUE);
	}
}

int test_DLDisposeList()	{
	solved=TRUE;
	DLDisposeList(&TEMPLIST);
	if (!solved)	{
		printf("Operace DLDisposeList nebyla implementov�na!\n");
		return(FALSE);
	}
	else	{
		print_elements_of_list(TEMPLIST);
		return(TRUE);
	}
}

int test_DLInsertFirst()	{
	solved=TRUE;
	DLInsertFirst(&TEMPLIST,obsah);
	if (!solved)	{
		printf("Operace DLInsertFirst nebyla implementov�na!\n");
		return(FALSE);
	}
	else	{
		print_elements_of_list(TEMPLIST);
		return(TRUE);
	}
}

int test_DLInsertLast()	{
	solved=TRUE;
	DLInsertLast(&TEMPLIST,obsah);
	if (!solved)	{
		printf("Operace DLInsertLast nebyla implementov�na!\n");
		return(FALSE);
	}
	else	{
		print_elements_of_list(TEMPLIST);
		return(TRUE);
	}
}

int test_DLFirst()	{
	solved=TRUE;
	DLFirst(&TEMPLIST);
	if (!solved)	{
		printf("Operace DLFirst nebyla implementov�na!\n");
		return(FALSE);
	}
	else	{
		print_elements_of_list(TEMPLIST);
		return(TRUE);
	}
}

int test_DLLast()	{
	solved=TRUE;
	DLLast(&TEMPLIST);
	if (!solved)	{
		printf("Operace DLLast nebyla implementov�na!\n");
		return(FALSE);
	}
	else	{
		print_elements_of_list(TEMPLIST);
		return(TRUE);
	}
}

int test_DLCopyFirst()	{
	solved=TRUE;
    int temp;
    DLCopyFirst(&TEMPLIST,&temp);
	if (!solved)	{
		printf("Operace DLCopyFirst nebyla implementov�na!\n");
		return(FALSE);
	}
	else {
		if (errflg)	{
			printf("Operace DLCopyFirst volala funkci DLError.\n");
			errflg=FALSE;
			return(FALSE);
		}
		else	{
			printf("Operace DLCopyFirst vrac� obsah %d.\n",temp);
			return(TRUE);
		}
	}
}

int test_DLCopyLast()	{
	solved=TRUE;
    int temp;
    DLCopyLast(&TEMPLIST,&temp);
	if (!solved)	{
		printf("Operace DLCopyLast nebyla implementov�na!\n");
		return(FALSE);
	}
	else {
		if (errflg)	{
			printf("Operace DLCopyLast volala funkci DLError.\n");
			errflg=FALSE;
			return(FALSE);
		}
		else	{
			printf("Operace DLCopyLast vrac� obsah %d.\n",temp);
			return(TRUE);
		}
	}
}

int test_DLDeleteFirst ()	{
	solved=TRUE;
	DLDeleteFirst(&TEMPLIST);
	if (!solved)	{
		printf("Operace DLDeleteFirst nebyla implementov�na!\n");
		return(FALSE);
	}
	else	{
		print_elements_of_list(TEMPLIST);
		return(TRUE);
	}
}

int test_DLDeleteLast ()	{
	solved=TRUE;
	DLDeleteLast(&TEMPLIST);
	if (!solved)	{
		printf("Operace DLDeleteLast nebyla implementov�na!\n");
		return(FALSE);
	}
	else	{
		print_elements_of_list(TEMPLIST);
		return(TRUE);
	}
}

int test_DLPostDelete()	{
	solved=TRUE;
	DLPostDelete(&TEMPLIST);
	if (!solved)	{
		printf("Operace DLPostDelete nebyla implementov�na!\n");
		return(FALSE);
	}
	else	{
		print_elements_of_list(TEMPLIST);
		return(TRUE);
	}
}

int test_DLPreDelete()	{
	solved=TRUE;
	DLPreDelete(&TEMPLIST);
	if (!solved)	{
		printf("Operace DLPreDelete nebyla implementov�na!\n");
		return(FALSE);
	}
	else	{
		print_elements_of_list(TEMPLIST);
		return(TRUE);
	}
}

int test_DLPostInsert()	{
	solved=TRUE;
	DLPostInsert(&TEMPLIST,obsah);
	if (!solved)	{
		printf("Operace DLPostInsert nebyla implementov�na!\n");
		return(FALSE);
	}
	else	{
		print_elements_of_list(TEMPLIST);
		return(TRUE);
	}
}

int test_DLPreInsert()	{
	solved=TRUE;
	DLPreInsert(&TEMPLIST,obsah);
	if (!solved)	{
		printf("Operace DLPreInsert nebyla implementov�na!\n");
		return(FALSE);
	}
	else	{
		print_elements_of_list(TEMPLIST);
		return(TRUE);
	}
}

int test_DLCopy()	{
	solved=TRUE;
	int temp;
	DLCopy(&TEMPLIST,&temp);

	if (!solved)	{
		printf("Operace DLCopy nebyla implementov�na!\n");
		return(FALSE);
	}
	else {
		if (errflg)	{
			printf("Operace DLCopy volala funkci DLError.\n");
			errflg=FALSE;
			return(FALSE);
		}
		else	{
			printf("Operace DLCopy vrac� obsah %d.\n",temp);
			return(TRUE);
		}
	}
}

int test_DLActualize()	{
	solved=TRUE;
	DLActualize(&TEMPLIST,obsah);
	if (!solved)	{
		printf("Operace DLActualize nebyla implementov�na!\n");
		return(FALSE);
	}
	else	{
		print_elements_of_list(TEMPLIST);
		return(TRUE);
	}
}

int test_DLSucc()	{
	solved=TRUE;
	DLSucc(&TEMPLIST);
	if (!solved)	{
		printf("Operace DLSucc nebyla implementov�na!\n");
		return(FALSE);
	}
	else	{
		print_elements_of_list(TEMPLIST);
		return(TRUE);
	}
}

int test_DLPred()	{
	solved=TRUE;
	DLPred(&TEMPLIST);
	if (!solved)	{
		printf("Operace DLPred nebyla implementov�na!\n");
		return(FALSE);
	}
	else	{
		print_elements_of_list(TEMPLIST);
		return(TRUE);
	}
}

int test_DLActive()	{
	solved=TRUE;
	int tmp=DLActive(&TEMPLIST);
	if (!solved)	{
		printf("Operace DLActive nebyla implementov�na!\n");
		return(FALSE);
	}
	else	{
		if (tmp)
			printf("Operace DLActive vrac� hodnotu true.\n");
		else
			printf("Operace DLActive vrac� hodnotu false.\n");
		return(TRUE);
	}
}

/*******************************************************************************
 * POKRO�IL� TESTY
 * ---------------
 * Nejsou dostupn� student�m p�i �e�en� dom�c�ch �loh.
 * Za jejich �sp�n� proj�t� z�sk� student druhou ��st bod� za p��klad.
 *
 ******************************************************************************/

int main(int argc, char *argv[])	{
    printf("Dvousm�rn� v�zan� line�rn� seznam\n");
    printf("=================================\n");

    printf("\n[TEST01]\n");
    printf("Inicializace seznamu\n");
    printf("~~~~~~~~~~~~~~~~~~~~\n");
    test_DLInitList();

    if(showFirstLast)
        printf("\nFirst: %d, Last: %d\n",TEMPLIST.First->data,TEMPLIST.Last->data);
                     /* Testy 02 a 03 jsou zde nav�c oproti z�kladn�m test�m. */
    printf("\n[TEST02]\n");
    printf("Pokus o vol�n� DLCopyFirst na pr�zdn� seznam => chyba\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLCopyFirst();

    if(showFirstLast)
        printf("\nFirst: %d, Last: %d\n",TEMPLIST.First->data,TEMPLIST.Last->data);

    printf("\n[TEST03]\n");
    printf("Pokus o vol�n� DLCopyLast na pr�zdn� seznam => chyba\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLCopyLast();

    if(showFirstLast)
        printf("\nFirst: %d, Last: %d\n",TEMPLIST.First->data,TEMPLIST.Last->data);

    printf("\n[TEST04]\n");
    printf("Zavol�me 2x operaci DLInsertFirst a 2x operaci DLInsertLast.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    obsah=1;
    test_DLInsertFirst();
    obsah=2;
    test_DLInsertFirst();
    obsah=3;
    test_DLInsertLast();
    obsah=4;
    test_DLInsertLast();

    if(showFirstLast)
        printf("\nFirst: %d, Last: %d\n",TEMPLIST.First->data,TEMPLIST.Last->data);
                             /* Test 05 je zde nav�c oproti z�kladn�m test�m. */
    printf("\n[TEST05]\n");
    printf("Seznam by m�l b�t neaktivn� -- ov���me si to vol�n�m DLActive.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLActive();

    if(showFirstLast)
        printf("\nFirst: %d, Last: %d\n",TEMPLIST.First->data,TEMPLIST.Last->data);
                      /* Testy 06 a� 10 odpov�daj� z�kladn�m test�m 03 a� 07. */
    printf("\n[TEST06]\n");
    printf("Otestujeme funkci DLFirst p�i neaktivn�m seznamu a funkci DLActive.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLFirst();
    test_DLActive();

    if(showFirstLast)
        printf("\nFirst: %d, Last: %d\n",TEMPLIST.First->data,TEMPLIST.Last->data);

    printf("\n[TEST07]\n");
    printf("Otestujeme funkci DLLast.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLLast();
    test_DLActive();

    if(showFirstLast)
        printf("\nFirst: %d, Last: %d\n",TEMPLIST.First->data,TEMPLIST.Last->data);

    printf("\n[TEST08]\n");
    printf("Test funkce DLCopy p�i aktivit� na posledn�m prvku\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLCopy();

    if(showFirstLast)
        printf("\nFirst: %d, Last: %d\n",TEMPLIST.First->data,TEMPLIST.Last->data);

    printf("\n[TEST09]\n");
    printf("Test funkce DLPred -- vol�me 3x, aktivita z�stane na prvn�m prvku.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLPred();
    test_DLPred();
    test_DLPred();
    test_DLActive();

    if(showFirstLast)
        printf("\nFirst: %d, Last: %d\n",TEMPLIST.First->data,TEMPLIST.Last->data);

    printf("\n[TEST10]\n");
    printf("Aktualizujeme obsah aktivn�ho prvku.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    obsah=5;
    test_DLActualize();
    test_DLActive();
    test_DLCopy();

    if(showFirstLast)
        printf("\nFirst: %d, Last: %d\n",TEMPLIST.First->data,TEMPLIST.Last->data);
                     /* Z�kladn� testy 08 a� 10 zde nahrad�me testem 11 a 12. */
    printf("\n[TEST11]\n");
    printf("Provedeme je�t� jednou DLPred -- aktivita se ztrat�.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLPred();
    test_DLActive();

    if(showFirstLast)
        printf("\nFirst: %d, Last: %d\n",TEMPLIST.First->data,TEMPLIST.Last->data);

    printf("\n[TEST12]\n");
    printf("Nastav�me aktivitu na konec a pak ji zru��me operac� DLSucc.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLLast();
    test_DLSucc();
    test_DLActive();

    if(showFirstLast)
        printf("\nFirst: %d, Last: %d\n",TEMPLIST.First->data,TEMPLIST.Last->data);
                                                     /* Test 13 je zde nav�c. */
    printf("\n[TEST13]\n");
    printf("Pokus�me se o aktualizaci p�i neaktivn�m seznamu => nic \n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    obsah=6;
    test_DLActualize();
    test_DLActive();

    if(showFirstLast)
        printf("\nFirst: %d, Last: %d\n",TEMPLIST.First->data,TEMPLIST.Last->data);
                                     /* Test 14 odpov�d� z�kladn�mu testu 11. */
    printf("\n[TEST14]\n");
    printf("Pokus o DLCopy p�i neaktivn�m seznamu => o�et�en� chyba.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLCopy();

    if(showFirstLast)
        printf("\nFirst: %d, Last: %d\n",TEMPLIST.First->data,TEMPLIST.Last->data);
                                             /* Testy 15 a 16 jsou zde nav�c. */
    printf("\n[TEST15]\n");
    printf("DLSucc p�i neaktivn�m seznamu nesm� zhavarovat.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLSucc();
    test_DLActive();

    if(showFirstLast)
        printf("\nFirst: %d, Last: %d\n",TEMPLIST.First->data,TEMPLIST.Last->data);

    printf("\n[TEST16]\n");
    printf("DLPred p�i neaktivn�m seznamu nesm� zhavarovat.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLPred();
    test_DLActive();

    if(showFirstLast)
        printf("\nFirst: %d, Last: %d\n",TEMPLIST.First->data,TEMPLIST.Last->data);
                      /* Testy 17 a� 20 odpov�daj� z�kladn�m test�m 12 a� 15. */
    printf("\n[TEST17]\n");
    printf("Pou�it� operace DLCopyFirst p�i neaktivn�m seznamu\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLCopyFirst();

    if(showFirstLast)
        printf("\nFirst: %d, Last: %d\n",TEMPLIST.First->data,TEMPLIST.Last->data);

    printf("\n[TEST18]\n");
    printf("Pou�it� operace DLCopyLast p�i neaktivn�m seznamu\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLCopyLast();

    if(showFirstLast)
        printf("\nFirst: %d, Last: %d\n",TEMPLIST.First->data,TEMPLIST.Last->data);

    printf("\n[TEST19]\n");
    printf("Pou�it� operace DLDeleteFirst p�i neaktivn�m seznamu\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLDeleteFirst();
    test_DLActive();

    if(showFirstLast)
        printf("\nFirst: %d, Last: %d\n",TEMPLIST.First->data,TEMPLIST.Last->data);

    printf("\n[TEST20]\n");
    printf("Pou�it� operace DLDeleteLast p�i neaktivn�m seznamu\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLDeleteLast();
    test_DLActive();

    if(showFirstLast)
        printf("\nFirst: %d, Last: %d\n",TEMPLIST.First->data,TEMPLIST.Last->data);
                        /* D�le se ji� od z�kladn�ch test� v�razn� odch�l�me. */
    printf("\n[TEST21]\n");
    printf("Operace DLFirst nastav� aktivitu na prvn� prvek.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLFirst();
    test_DLActive();

    if(showFirstLast)
        printf("\nFirst: %d, Last: %d\n",TEMPLIST.First->data,TEMPLIST.Last->data);

    printf("\n[TEST22]\n");
    printf("DLDeleteFirst aktivn�ho prvku povede ke ztr�t� aktivity.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLDeleteFirst();
    test_DLActive();

    if(showFirstLast)
        printf("\nFirst: %d, Last: %d\n",TEMPLIST.First->data,TEMPLIST.Last->data);

    printf("\n[TEST23]\n");
    printf("Operace DLLast nastav� aktivitu na posledn� prvek.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLLast();
    test_DLActive();

    if(showFirstLast)
        printf("\nFirst: %d, Last: %d\n",TEMPLIST.First->data,TEMPLIST.Last->data);

    printf("\n[TEST24]\n");
    printf("Operace DLFirst p�i jedin�m prvku => aktivita z�st�v�.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLFirst();
    test_DLActive();

    if(showFirstLast)
        printf("\nFirst: %d, Last: %d\n",TEMPLIST.First->data,TEMPLIST.Last->data);

    printf("\n[TEST25]\n");
    printf("DLDeleteLast aktivn�ho prvku povede ke ztr�t� aktivity.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLDeleteLast();
    test_DLActive();

    if(showFirstLast)
        printf("\nFirst: %d, Last: %d\n",TEMPLIST.First->data,TEMPLIST.Last->data);
           /* Te� m�me pr�zdn� seznam, tak si pro dal�� testy vytvo��me nov�. */
    printf("\n[TEST26]\n");
    printf("Vol�me 2x operaci DLInsertLast a 1x operaci DLInsertFirst.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    obsah = 7;
    test_DLInsertLast();
    obsah = 8;
    test_DLInsertLast();
    obsah = 9;
    test_DLInsertFirst();

    if(showFirstLast)
        printf("\nFirst: %d, Last: %d\n",TEMPLIST.First->data,TEMPLIST.Last->data);

    printf("\n[TEST27]\n");
    printf("Seznam je neaktivn� -- ov���me si to vol�n�m DLActive.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLActive();

    if(showFirstLast)
        printf("\nFirst: %d, Last: %d\n",TEMPLIST.First->data,TEMPLIST.Last->data);

    printf("\n[TEST28]\n");
    printf("U�it�m operace DLLast nastav�me aktivitu na konec seznamu.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLLast();
    test_DLActive();

    if(showFirstLast)
        printf("\nFirst: %d, Last: %d\n",TEMPLIST.First->data,TEMPLIST.Last->data);
                                     /* Test 29 odpov�d� z�kladn�mu testu 16. */
    printf("\n[TEST29]\n");
    printf("Operace DLPostDelete p�i aktivit� na posledn�m prvku ned�l� nic.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLPostDelete();
    test_DLActive();

    if(showFirstLast)
        printf("\nFirst: %d, Last: %d\n",TEMPLIST.First->data,TEMPLIST.Last->data);

    printf("\n[TEST30]\n");
    printf("Nastav�me aktivitu na p�edposledn� prvek operac� DLPred a op�t\n");
    printf("zavol�me DLPostDelete. Sma�eme t�m posledn� prvek v seznamu.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLPred();
    test_DLPostDelete();
    test_DLActive();

    if(showFirstLast)
        printf("\nFirst: %d, Last: %d\n",TEMPLIST.First->data,TEMPLIST.Last->data);

    printf("\n[TEST31]\n");
    printf("U�it�m operace DLFirst nastav�me aktivitu na za��tek seznamu.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLFirst();
    test_DLActive();

    if(showFirstLast)
        printf("\nFirst: %d, Last: %d\n",TEMPLIST.First->data,TEMPLIST.Last->data);

    printf("\n[TEST32]\n");
    printf("Operace DLPreDelete p�i aktivit� na prvn�m prvku ned�l� nic.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLPreDelete();
    test_DLActive();

    if(showFirstLast)
        printf("\nFirst: %d, Last: %d\n",TEMPLIST.First->data,TEMPLIST.Last->data);

    printf("\n[TEST33]\n");
    printf("Nastav�me aktivitu na druh� prvek operac� DLSucc a op�t\n");
    printf("zavol�me DLPreDelete. Sma�e prvn� prvek v seznamu.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLSucc();
    test_DLPreDelete();
    test_DLActive();

    if(showFirstLast)
        printf("\nFirst: %d, Last: %d\n",TEMPLIST.First->data,TEMPLIST.Last->data);

    printf("\n[TEST34]\n");
    printf("Otestujeme DLInsertFirst p�i seznamu s jedin�m prvkem, nastav�me\n");
    printf("aktivitu na nov� vlo�en� prvek a op�t posuneme aktivitu na konec \n");
    printf("seznamu.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    obsah=10;
    test_DLInsertFirst();
    test_DLFirst();
    test_DLSucc();
    test_DLActive();

    if(showFirstLast)
        printf("\nFirst: %d, Last: %d\n",TEMPLIST.First->data,TEMPLIST.Last->data);

    printf("\n[TEST35]\n");
    printf("Operac� DLPostInsert vlo��me nov� prvek za posledn� prvek seznamu.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    obsah=11;
    test_DLPostInsert();
    test_DLActive();

    if(showFirstLast)
        printf("\nFirst: %d, Last: %d\n",TEMPLIST.First->data,TEMPLIST.Last->data);

    printf("\n[TEST36]\n");
    printf("Nastav�me aktivitu na prvn� prvek seznamu a vyzkou��me DLPostInsert.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLFirst();
    obsah=12;
    test_DLPostInsert();
    test_DLActive();

    if(showFirstLast)
        printf("\nFirst: %d, Last: %d\n",TEMPLIST.First->data,TEMPLIST.Last->data);

    printf("\n[TEST37]\n");
    printf("Nastv�me aktivitu na druh� prvek a vol�me 2x DLPostDelete a 1x DLPreDelete.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLSucc();
    test_DLPostDelete();
    test_DLPostDelete();
    test_DLPreDelete();
    test_DLActive();

    if(showFirstLast)
        printf("\nFirst: %d, Last: %d\n",TEMPLIST.First->data,TEMPLIST.Last->data);

    printf("\n[TEST38]\n");
    printf("Otestujeme DLInsertLast p�i seznamu s jedin�m prvkem, nastav�me\n");
    printf("aktivitu na nov� vlo�en� prvek a posuneme aktivitu na za��tek.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    obsah=13;
    test_DLInsertLast();
    test_DLLast();
    test_DLPred();
    test_DLActive();

    if(showFirstLast)
        printf("\nFirst: %d, Last: %d\n",TEMPLIST.First->data,TEMPLIST.Last->data);

    printf("\n[TEST39]\n");
    printf("Operac� DLPreInsert vkl�d�me nov� prvek p�ed prvn� prvek seznamu.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    obsah=14;
    test_DLPreInsert();
    test_DLActive();

    if(showFirstLast)
        printf("\nFirst: %d, Last: %d\n",TEMPLIST.First->data,TEMPLIST.Last->data);

    printf("\n[TEST40]\n");
    printf("Nastav�me aktivitu na posledn� prvek seznamu a aplikujeme DLPreInsert.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLLast();
    obsah=15;
    test_DLPreInsert();
    test_DLActive();

    if(showFirstLast)
        printf("\nFirst: %d, Last: %d\n",TEMPLIST.First->data,TEMPLIST.Last->data);

    printf("\n[TEST41]\n");
    printf("Otestujeme funk�nost operace DLDisposeList.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLDisposeList();

    if(showFirstLast)
        printf("\nFirst: %d, Last: %d\n",TEMPLIST.First->data,TEMPLIST.Last->data);

                                   /* Testov�n� operac� p�i pr�zdn�m seznamu. */
    printf("\nN�sleduje testov�n� operac� p�i pr�zdn�m seznamu\n");
    printf("================================================\n");

    printf("\n[TEST42]\n");
    printf("DLFirst a DLLast p�i pr�zdn�m seznamu ned�laj� nic.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLFirst();
    test_DLLast();
    test_DLActive();

    if(showFirstLast)
        printf("\nFirst: %d, Last: %d\n",TEMPLIST.First->data,TEMPLIST.Last->data);

    printf("\n[TEST43]\n");
    printf("DLCopyFirst i DLCopyLast zp�sob� o�et�enou chybu.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLCopyFirst();
    test_DLCopyLast();

    if(showFirstLast)
        printf("\nFirst: %d, Last: %d\n",TEMPLIST.First->data,TEMPLIST.Last->data);

    printf("\n[TEST44]\n");
    printf("DLDeleteFirst a DLDeleteLast p�i pr�zdn�m seznamu ned�laj� nic.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLDeleteFirst();
    test_DLDeleteLast();

    if(showFirstLast)
        printf("\nFirst: %d, Last: %d\n",TEMPLIST.First->data,TEMPLIST.Last->data);

    printf("\n[TEST45]\n");
    printf("DLPostDelete a DLPreDelete p�i pr�zdn�m seznamu nic ned�laj�.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLPostDelete();
    test_DLPreDelete();

    if(showFirstLast)
        printf("\nFirst: %d, Last: %d\n",TEMPLIST.First->data,TEMPLIST.Last->data);

    printf("\n[TEST46]\n");
    printf("DLPostInsert i DLPreInsert p�i pr�zdn�m seznamu nic ned�laj�.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    obsah=16;
    test_DLPostInsert();
    obsah=17;
    test_DLPreInsert();

    if(showFirstLast)
        printf("\nFirst: %d, Last: %d\n",TEMPLIST.First->data,TEMPLIST.Last->data);

    printf("\n[TEST47]\n");
    printf("Pokus o DLCopy na pr�zdn� seznam => chyba\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLCopy();

    if(showFirstLast)
        printf("\nFirst: %d, Last: %d\n",TEMPLIST.First->data,TEMPLIST.Last->data);

    printf("\n[TEST48]\n");
    printf("DLActualize p�i pr�zdn�m seznamu nic neud�l�.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    obsah=18;
    test_DLActualize();

    if(showFirstLast)
        printf("\nFirst: %d, Last: %d\n",TEMPLIST.First->data,TEMPLIST.Last->data);

    printf("\n[TEST49]\n");
    printf("DLSucc a DLPred na pr�zdn� seznam nemaj� vliv.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    test_DLSucc();
    test_DLPred();
    test_DLActive();
    test_DLDisposeList();

    printf("\n----------------------- konec p��kladu c206----------------------\n");

	return(0);
}
/**/


