//======== Copyright (c) 2020, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - priority queue code
//
// $NoKeywords: $ivs_project_1 $tdd_code.cpp
// $Author:     FILIP JANUSKA <xjanus11@stud.fit.vutbr.cz>
// $Date:       $2020-22-02
//============================================================================//
/**
 * @file tdd_code.cpp
 * @author FILIP JANUSKA
 * 
 * @brief Implementace metod tridy prioritni fronty.
 */

#include <stdlib.h>
#include <stdio.h>

#include "tdd_code.h"

//============================================================================//
// ** ZDE DOPLNTE IMPLEMENTACI **
//
// Zde doplnte implementaci verejneho rozhrani prioritni fronty (Priority Queue)
// 1. Verejne rozhrani fronty specifikovane v: tdd_code.h (sekce "public:")
//    - Konstruktor (PriorityQueue()), Destruktor (~PriorityQueue())
//    - Metody Insert/Remove/Find a GetHead
//    - Pripadne vase metody definovane v tdd_code.h (sekce "protected:")
//
// Cilem je dosahnout plne funkcni implementace prioritni fronty implementovane
// pomoci tzv. "double-linked list", ktera bude splnovat dodane testy 
// (tdd_tests.cpp).
//============================================================================//

PriorityQueue::PriorityQueue()
{
	m_pHead = NULL;
}


PriorityQueue::~PriorityQueue()
{
	Element_t *node = GetHead();
	while(node != NULL)
	{
		Element_t *next = node->pNext;
		delete(node);
		node = next;
	}
	return;
}

void PriorityQueue::Insert(int value)
{
	
	//prazdna fronta
	if (GetHead() == NULL)
	{
		m_pHead = new Element_t;
		m_pHead->value = value;
		m_pHead->pNext = NULL;
		m_pHead->pPrev = NULL;
		return;
	}

	//novy nejmensi prvek
	if (GetHead()->value >= value)	
	
	{	
		Element_t *head = GetHead();
		Element_t *temp = new Element_t;
		temp->value = value;
		temp->pPrev = NULL;
		temp->pNext = head;
		head->pPrev = temp;
		m_pHead = temp;
		return;
	}

	//prvek se stejnou hodnotou jiz existuje (vlozit pred)
	Element_t *find = Find(value);
	if (find != NULL)
	{
		Element_t *temp = new Element_t;
		temp ->pPrev = find->pPrev;
		temp->pPrev->pNext = temp;
		temp->value = value;
		temp->pNext = find;
		find->pPrev = temp;
		return;
	}
	
	//prvek neexistuje
	
	find = GetHead();
	
	while(find != NULL)
	{
		if (find->value > value)
		{
			Element_t *temp = new Element_t;
			temp->value = value;
			temp->pPrev = find->pPrev;
			temp->pNext = find;
			temp->pPrev->pNext = temp;
			find->pPrev = temp;
			return;
		}
		if(find->pNext == NULL)
		{
			break;
		}
		find = find->pNext;
	}
			
	//vlozit na konec fronty
	if (find->pNext == NULL)
	{	
		Element_t *temp = new Element_t;
		temp->value = value;
		temp->pNext = NULL;
		temp->pPrev = find;
		find->pNext = temp;
		return;
	}	

}

bool PriorityQueue::Remove(int value)
{

	Element_t *node = Find(value);
	if (node == NULL)
	 {
		 return false;
	 }
	//Odstranit koren seznamu
	if(node == GetHead())
	{
		
		if (node->pNext != NULL)
		{
			m_pHead = node->pNext;
			m_pHead->pPrev = NULL;
		}
		//ak seznam obsahuje pouze tenhle koren
		else if(node->pNext == NULL)
		{
			m_pHead = NULL;
		}
		delete(node);
		return true;
	}
	//odstranit posledni prvek
	else if (node->pNext == NULL)
	{
		node->pPrev->pNext = NULL;
		delete(node);
		return true;
	}
	//odstranit prvek uvnitr seznamu
	else if (node->pNext != NULL && node->pPrev != NULL)
	{
		node->pPrev->pNext = node->pNext;
		node->pNext->pPrev = node->pPrev;
		delete(node);
		return true;
	}

}

PriorityQueue::Element_t *PriorityQueue::Find(int value)
{
   Element_t *node = GetHead();
   while(node != NULL)
   {
	   if (node->value == value)
	   {
		   return node;
	   }
	   node = node->pNext;
   }
   return NULL;
}

PriorityQueue::Element_t *PriorityQueue::GetHead()
{
	return m_pHead;
}

/*** Konec souboru tdd_code.cpp ***/
