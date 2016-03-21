/* 
 * File:   Pointer.cpp
 * Author: Monty
 * 
 * Created on 20 de marzo de 2016, 17:41
 */

#include "../Headers/Pointer.h"

Pointer::Pointer(Object *obj): obj(obj)
{
	this->prev = this->next = this;
}

Pointer::Pointer(const Pointer &ptr)
{
	this->Attach(ptr);
}

Pointer::~Pointer()
{
	this->Release();
}

Object &Pointer::operator*()
{
	return *(this->obj);
}

Object *Pointer::operator->()
{
	return this->obj;
}

Pointer &Pointer::operator=(const Pointer &ptr)
{
	if (this != &ptr)
	{
		this->Release();
		this->Attach(ptr);
	}

	return *this;
}

void Pointer::Attach(const Pointer &ptr)
{
	this->obj = ptr.obj;
	this->prev = &ptr;
	this->next = ptr.next;
	this->next->prev = this;
	ptr.next = this;
}

void Pointer::Release()
{
	if (this->prev == this)
		delete this->obj;
	else
	{
		this->prev->next = this->next;
		this->next->prev = this->prev;
		this->next = this->prev = NULL;
	}
	
	this->obj = NULL;
}
