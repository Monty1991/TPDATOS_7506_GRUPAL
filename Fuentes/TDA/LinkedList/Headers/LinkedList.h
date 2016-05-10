/* 
 * File:   LinkedList.h
 * Author: Monty
 *
 * Created on 20 de marzo de 2016, 21:23
 */

#ifndef LINKEDLIST_H
#define	LINKEDLIST_H

#include "iLinkedList.h"
#include "../../../Memoria/Object/Headers/Object.h"

typedef class LinkedList: public iLinkedList, public Object
{
	private:
		iObjectPtr obj;
		iLinkedList *next;
	
		virtual ~LinkedList();
	public:
		LinkedList(iObjectPtr obj, iLinkedListPtr next);

		virtual iLinkedListPtr Copiar();
		virtual iLinkedListPtr Clone();

		virtual iLinkedListPtr Next();
		virtual iObjectPtr Value();

		virtual void Dispose();
		
	private:

} *LinkedListPtr;

#endif	/* LINKEDLIST_H */
