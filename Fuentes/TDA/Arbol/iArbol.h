/* 
 * File:   iArbol.h
 * Author: Monty
 *
 * Created on 21 de marzo de 2016, 06:04
 */

#ifndef IARBOL_H
#define	IARBOL_H

#include "../../Memoria/Object/Headers/iObject.h"

typedef class iArbol
{
	public:
		virtual iArbol *Add(int key, iObjectPtr obj) = 0;
		virtual iObjectPtr GetValue(int key) = 0;
		virtual iArbol *Remove(int key) = 0;

		virtual void Dispose() = 0;

} *iArbolPtr;

#endif	/* IARBOL_H */
