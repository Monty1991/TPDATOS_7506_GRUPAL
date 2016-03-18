#include "../Sistema.h"
#include "../../io/Bitacora/BitacoraFactory.h"
#include <stddef.h>

#include "../TraceEntry/TraceEntryFactory.h"
#include "../StackTrace/StackTraceFactory.h"

iBitacoraPtr gBitacora = NULL;
iStackTracePtr gStackTrace = NULL;

void Sistema_Inicializar()
{
	if (gBitacora)
		return;

	gBitacora = BitacoraFactory_Nuevo("Log.txt");
	gStackTrace = StackTraceFactory_Nuevo();
}

const iBitacoraPtr Sistema_ObtenerBitacora()
{
	return gBitacora;
}

void Sistema_Finalizar()
{
	if (gBitacora)
	{
		gBitacora->Close();
		gBitacora = NULL;
	}
	
	if (gStackTrace)
	{
		gStackTrace->Dispose();
		gStackTrace = NULL;		
	}
}

iStackTrace *Sistema_GetStackTraceCopy()
{
	return gStackTrace->Clone();
}

void Sistema_PushEntry(const char *file, int line, const char *functionName)
{
	gStackTrace->Push(TraceEntryFactory_Nuevo(file, line, functionName));
}

void Sistema_PopEntry()
{
	iTraceEntryPtr entry = gStackTrace->Pop();
	if (entry)
		entry->Dispose();
}
