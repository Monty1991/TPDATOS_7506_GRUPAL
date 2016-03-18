/* 
 * File:   TraceEntry.h
 * Author: Monty
 *
 * Created on 17 de marzo de 2016, 13:49
 */

#ifndef TRACEENTRY_H
#define	TRACEENTRY_H

#include "iTraceEntry.h"

class TraceEntry: public iTraceEntry
{
	private:
		char *filename;
		int numeroLinea;
		char *functionName;

	public:
		TraceEntry(const char *filename, int numeroLinea, const char *nombreMetodo);
		~TraceEntry();

		const char *ObtenerNombreArchivo();
		int ObtenerNumeroLinea();
		const char *ObtenerNombreMetodo();

		char *ObtenerAsString();

		TraceEntry *Clone();
		void Dispose();
		
	private:

};

#endif	/* TRACEENTRY_H */
