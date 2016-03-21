/* 
 * File:   iTraceEntry.h
 * Author: Monty
 *
 * Created on 18 de marzo de 2016, 04:53
 */

#ifndef ITRACEENTRY_H
#define	ITRACEENTRY_H

#include "../../../Memoria/Object/Headers/iObject.h"

typedef class iTraceEntry: public iObject
{
	public:
		virtual const char *ObtenerNombreArchivo() = 0;
		virtual int ObtenerNumeroLinea() = 0;
		virtual const char *ObtenerNombreMetodo() = 0;
		
		virtual char *ObtenerAsString() = 0;
		
		virtual iTraceEntry *Clone() = 0;
		virtual void Dispose() = 0;

} *iTraceEntryPtr;

#endif	/* ITRACEENTRY_H */
