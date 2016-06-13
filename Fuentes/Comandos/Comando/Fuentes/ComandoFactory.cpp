#include "../ComandoFactory.h"
#include "../../ComandoAlta/ComandoAltaFactory.h"
#include "../../ComandoBaja/ComandoBajaFactory.h"
#include "../../ComandoBuscar/ComandoBuscarFactory.h"
#include "../../ComandoModificacion/ComandoModificacionFactory.h"

#include <string.h>
#include <ctype.h>

iComandoPtr ComandoFactory_Nuevo(const char *nombreComando)
{
	size_t largo = strlen(nombreComando);
	char nombreABuscar[largo + 1];

	for (size_t i = 0; i < largo; i++)
		nombreABuscar[i] = toupper(nombreComando[i]);

	nombreABuscar[largo] = '\0';

	if (!strcmp("ALTA", nombreABuscar))
		return ComandoAltaFactory_Nuevo();

	if (!strcmp("BAJA", nombreABuscar))
		return ComandoBajaFactory_Nuevo();

	if (!strcmp("BUSCAR", nombreABuscar))
		return ComandoBuscarFactory_Nuevo();

	if (!strcmp("MODIFICACION", nombreABuscar))
		return ComandoModificacionFactory_Nuevo();

	return NULL;
}
