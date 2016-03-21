/* 
 * File:   LinkedList.cpp
 * Author: Monty
 * 
 * Created on 20 de marzo de 2016, 21:23
 */

#include "../Headers/LinkedList.h"

#include <stddef.h>

LinkedList::LinkedList(iObjectPtr obj, iLinkedList *next): obj(obj), next(next)
{
}

LinkedList::~LinkedList()
{
}

iLinkedList *LinkedList::Next()
{
	return this->next;
}

iObjectPtr LinkedList::Value()
{
	return this->obj;
}

iLinkedList *LinkedList::Clone()
{
	return new LinkedList(this->obj->Clone(), this->next? this->next->Clone(): NULL);
}

void LinkedList::Dispose()
{
	delete this;
}
