/* 
 * File:   LinkedList.h
 * Author: Monty
 *
 * Created on 20 de marzo de 2016, 21:23
 */

#ifndef LINKEDLIST_H
#define	LINKEDLIST_H

#include "iLinkedList.h"

typedef class LinkedList: public iLinkedList
{
	private:
		iObjectPtr obj;
		iLinkedList *next;
	
	public:
		LinkedList(iObjectPtr obj, iLinkedList *next);
		virtual ~LinkedList();

		iLinkedList *Next();
		iObjectPtr Value();

		iLinkedList *Clone();

		void Dispose();

	private:

} *LinkedListPtr;

#endif	/* LINKEDLIST_H */
