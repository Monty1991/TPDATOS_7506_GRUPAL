/* 
 * File:   Exception.h
 * Author: Monty
 *
 * Created on 17 de marzo de 2016, 13:06
 */

#ifndef EXCEPTION_H
#define	EXCEPTION_H

#include "iException.h"

typedef class Exception: public iException
{
	private:
		char *header;
		char *msg;
		iStackTracePtr stackTrace;

	public:
		Exception(const char *exceptionType, const char *msg, const char *file, int lineNumber, const char *function);
		~Exception();

		const char *what();
		const char *Msg();

		iStackTracePtr ObtenerStackTrace();

		void Dispose();

	private:

} *ExceptionPtr;

#endif	/* EXCEPTION_H */
