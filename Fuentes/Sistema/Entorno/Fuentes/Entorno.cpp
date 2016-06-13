#include "../Headers/Entorno.h"
#include "../../../io/Bitacora/BitacoraFactory.h"
#include "../../StackTrace/StackTraceFactory.h"
#include "../../TraceEntry/TraceEntryFactory.h"

Entorno::Entorno()
{
	this->bitacora = BitacoraFactory_Nuevo("Log.txt");
	this->stackTrace = StackTraceFactory_Nuevo();
}

Entorno::~Entorno()
{
	this->bitacora->Close();
	this->stackTrace->Dispose();
}

const iBitacoraPtr Entorno::ObtenerBitacora()
{
	return this->bitacora;
}

iStackTracePtr Entorno::ObtenerStackTrace()
{
	return this->stackTrace->Clone();
}

void Entorno::PushEntry(const char *fileName, int line, const char *functionName)
{
	this->stackTrace->Push(TraceEntryFactory_Nuevo(fileName, line, functionName));
}

void Entorno::PopEntry()
{
	iTraceEntryPtr entry = this->stackTrace->Pop();

	if (entry)
		entry->Dispose();
}

const void Entorno::Execute(ClosedProcedure closedProcedure, const char *fileName, int line, const char *functionName)
{
	this->PushEntry(fileName, line, functionName);
	try
	{
		closedProcedure();
		this->PopEntry();
	}
	catch(iExceptionPtr e)
	{
		this->PopEntry();
		throw e;
	}
}

void Entorno::Dispose()
{
	delete this;
}
