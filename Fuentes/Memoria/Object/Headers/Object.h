/* 
 * File:   Object.h
 * Author: Monty
 *
 * Created on 19 de marzo de 2016, 17:36
 */

#ifndef OBJECT_H
#define	OBJECT_H

#include "iObject.h"

typedef class Object: public iObject
{
	private:
		int refCount;

	public:
		Object();

		virtual iObject *Clone() = 0;
		virtual void Dispose();

	protected:
		virtual ~Object();
		virtual void IncrementarContador();

} *ObjectPtr;

#endif	/* OBJECT_H */
