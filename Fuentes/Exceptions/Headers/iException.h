/* 
 * File:   iException.h
 * Author: Monty
 *
 * Created on 18 de marzo de 2016, 15:52
 */

#ifndef IEXCEPTION_H
#define	IEXCEPTION_H

#include <exception>
using namespace std;

#include "../../Sistema/StackTrace/Headers/iStackTrace.h"

typedef class iException: private exception
{
	public:
		virtual const char *Header() = 0;
		virtual const char *Msg() = 0;

		virtual iStackTracePtr ObtenerStackTrace() = 0;

		virtual void Dispose() = 0;
} *iExceptionPtr;

#endif	/* IEXCEPTION_H */

