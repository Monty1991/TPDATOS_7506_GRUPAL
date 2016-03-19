/* 
 * File:   Exception.cpp
 * Author: Monty
 * 
 * Created on 17 de marzo de 2016, 13:06
 */

#include "Exception.h"
#include "../Utils/StringUtils/Headers/StringUtils.h"
#include "../Sistema/Sistema.h"
#include "../Sistema/TraceEntry/TraceEntryFactory.h"

Exception::Exception(const char *msg, const char *file, int lineNumber, const char *function)
{
	this->msg = StringUtils_Clonar(msg);
	
	this->stackTrace = Sistema_ObtenerEntorno()->ObtenerStackTrace();
	this->stackTrace->Push(TraceEntryFactory_Nuevo(file, lineNumber, function));
}

Exception::~Exception()
{
	if (this->msg)
	{
		delete this->msg;
		this->stackTrace = NULL;
	}
	
	if (this->stackTrace)
	{
		this->stackTrace->Dispose();
		this->stackTrace = NULL;
	}
}

const char *Exception::Header()
{
	return "Exception";
}

const char *Exception::Msg()
{
	return this->msg;
}

iStackTracePtr Exception::ObtenerStackTrace()
{
	return this->stackTrace->Clone();
}

void Exception::Dispose()
{
	delete this;
}
