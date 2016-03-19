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

	public:
		Entorno();
		~Entorno();
		
		const iBitacoraPtr ObtenerBitacora();

		iStackTracePtr ObtenerStackTrace();

		void PushEntry(const char *fileName, int line, const char *functionName);
		void PopEntry();

		const void Execute();
		
		void Dispose();
};

#endif	/* ENTORNO_H */

