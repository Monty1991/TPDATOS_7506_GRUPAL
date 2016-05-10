/* 
 * File:   iObject.h
 * Author: Monty
 *
 * Created on 20 de marzo de 2016, 21:33
 */

#ifndef IOBJECT_H
#define	IOBJECT_H

typedef class iObject
{
	public:
		virtual iObject *Copiar() = 0;
		virtual iObject *Clone() = 0;
		
		virtual void Dispose() = 0;

} *iObjectPtr;

#endif	/* IOBJECT_H */
