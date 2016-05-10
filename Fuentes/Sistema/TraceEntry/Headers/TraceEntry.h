/* 
 * File:   TraceEntry.h
 * Author: Monty
 *
 * Created on 17 de marzo de 2016, 13:49
 */

#ifndef TRACEENTRY_H
#define	TRACEENTRY_H

#include "iTraceEntry.h"
#include "../../../Memoria/Object/Headers/Object.h"

class TraceEntry: public iTraceEntry, public Object
{
	private:
		char *filename;
		size_t numeroLinea;
		char *functionName;

		virtual ~TraceEntry();
	public:
		TraceEntry(const char *filename, size_t numeroLinea, const char *nombreMetodo);

		virtual iTraceEntryPtr Copiar();
		virtual iTraceEntryPtr Clone();

		const char *ObtenerNombreArchivo();
		size_t ObtenerNumeroLinea();
		const char *ObtenerNombreMetodo();

		char *ObtenerAsString();

		virtual void Dispose();
		
	private:

};

#endif	/* TRACEENTRY_H */
