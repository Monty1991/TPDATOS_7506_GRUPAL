/* 
 * File:   Entorno.h
 * Author: Monty
 *
 * Created on 18 de marzo de 2016, 20:05
 */

#ifndef ENTORNO_H
#define	ENTORNO_H

#include "iEntorno.h"

class Entorno: public iEntorno
{
	private:
		iBitacoraPtr bitacora;
		iStackTracePtr stackTrace;

		virtual ~Entorno();
	public:
		Entorno();
		
		virtual const iBitacoraPtr ObtenerBitacora();

		virtual iStackTracePtr ObtenerStackTrace();

		virtual void PushEntry(const char *fileName, int line, const char *functionName);
		virtual void PopEntry();

		virtual const void Execute(ClosedProcedure closedProcedure, const char *fileName, int line, const char *functionName);
		
		virtual void Dispose();
};

#endif	/* ENTORNO_H */
