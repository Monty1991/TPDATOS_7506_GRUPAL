#include "../Headers/Sistema.h"
#include <stddef.h>

#include "../../Entorno/EntornoFactory.h"

iEntornoPtr gEntorno = NULL;

void Sistema_Inicializar()
{
	if (gEntorno)
		return;

	gEntorno = EntornoFactory_Nuevo();
}

void Sistema_Finalizar()
{
	if (gEntorno)
	{
		gEntorno->Dispose();
		gEntorno = NULL;
	}
}

const iEntornoPtr Sistema_ObtenerEntorno()
{
	return gEntorno;
}

void Sistema_ExecuteSecure(ClosedProcedure closedProcedure, const char *fileName, size_t line, const char *functionName)
{
	gEntorno->Execute(closedProcedure, fileName, line, functionName);
}
