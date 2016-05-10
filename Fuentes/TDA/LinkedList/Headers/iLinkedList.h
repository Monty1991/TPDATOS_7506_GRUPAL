/* 
 * File:   iLinkedList.h
 * Author: Monty
 *
 * Created on 20 de marzo de 2016, 21:39
 */

#ifndef ILINKEDLIST_H
#define	ILINKEDLIST_H

#include "../../../Memoria/Object/Headers/iObject.h"

typedef class iLinkedList: public iObject
{
	public:
		virtual iLinkedList *Copiar() = 0;
		virtual iLinkedList *Clone() = 0;

		virtual iLinkedList *Next() = 0;
		virtual iObjectPtr Value() = 0;
		virtual void Dispose() = 0;

	private:

} *iLinkedListPtr;

#endif	/* ILINKEDLIST_H */
