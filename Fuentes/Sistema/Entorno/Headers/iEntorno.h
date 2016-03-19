/* 
 * File:   iEntorno.h
 * Author: Monty
 *
 * Created on 18 de marzo de 2016, 20:40
 */

#ifndef IENTORNO_H
#define	IENTORNO_H

#include "../../../io/Bitacora/Headers/iBitacora.h"
#include "../../StackTrace/Headers/iStackTrace.h"

#include <functional>

typedef std::function<void(void)> ClosedProcedure;

typedef class iEntorno
{
	public:

		virtual const iBitacoraPtr ObtenerBitacora() = 0;

		virtual iStackTracePtr ObtenerStackTrace() = 0;

		virtual void PushEntry(const char *fileName, int line, const char *functionName) = 0;

		virtual void PopEntry() = 0;

		virtual const void Execute(ClosedProcedure closedProcedure, const char *fileName, int line, const char *functionName) = 0;
		
		virtual void Dispose() = 0;

} *iEntornoPtr;

#endif	/* IENTORNO_H */

