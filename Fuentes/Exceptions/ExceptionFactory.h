/* 
 * File:   ExceptionFactory.h
 * Author: Monty
 *
 * Created on 18 de marzo de 2016, 22:00
 */

#ifndef EXCEPTIONFACTORY_H
#define	EXCEPTIONFACTORY_H

#include "Headers/iException.h"
#include "../Sistema/Sistema/Headers/Sistema.h"

#define ExceptionType_InvalidArg "Invalid arg"
#define ExceptionType_ArrayIndexOutOfBounds "ArrayIndexOutOfBoundsException"

iExceptionPtr ExceptionFactory_Nuevo(const char *exceptionType, const char *msg, const char *fileName, int line, const char *functionName);

#define Throw(exception, msg) throw ExceptionFactory_Nuevo(exception, msg, Sistema_DebugInfo(-1));

#endif	/* EXCEPTIONFACTORY_H */
