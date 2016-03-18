/* 
 * File:   Exception.h
 * Author: Monty
 *
 * Created on 17 de marzo de 2016, 13:06
 */

#ifndef EXCEPTION_H
#define	EXCEPTION_H

#include "iException.h"
#include "../Sistema/Sistema.h"

typedef class Exception: public iException
{
	private:
		char *msg;
		iStackTracePtr stackTrace;

	public:
		Exception(const char *msg, const char *file, int lineNumber, const char *function);
		~Exception();

		virtual const char *Header();
		const char *Msg();

		iStackTracePtr ObtenerStackTrace();

		void Dispose();

	private:

} *ExceptionPtr;

#define Throw(exception, msg) throw new exception(msg, Sistema_DebugInfo(-1));

#endif	/* EXCEPTION_H */
