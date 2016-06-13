/* 
 * File:   LinkedList.cpp
 * Author: Monty
 * 
 * Created on 20 de marzo de 2016, 21:23
 */

#include "../Headers/LinkedList.h"

#include <stddef.h>

LinkedList::LinkedList(iObjectPtr obj, iLinkedListPtr next): Object(), obj(NULL), next(NULL)
{
	if (obj)
		this->obj = obj->Copiar();

	if (next)
		this->next = next->Copiar();
}

LinkedList::~LinkedList()
{
	if (this->obj)
		this->obj->Dispose();

	if (this->next)
		this->next->Dispose();
}

iLinkedListPtr LinkedList::Copiar()
{
	Object::IncrementarContador();
	return this;
}

iLinkedListPtr LinkedList::Clone()
{
	iObjectPtr objClone = (this->obj? this->obj->Clone(): NULL);
	iLinkedListPtr nextClone = (this->next? this->next->Clone(): NULL);

	return new LinkedList(objClone, nextClone);
}

iLinkedListPtr LinkedList::Next()
{
	return this->next;
}

iObjectPtr LinkedList::Value()
{
	return this->obj;
}

void LinkedList::Dispose()
{
	Object::Dispose();
}
