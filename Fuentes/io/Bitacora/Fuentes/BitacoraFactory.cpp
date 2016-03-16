#include "../BitacoraFactory.h"
#include "../Headers/Bitacora.h"

iBitacoraPtr BitacoraFactory_Nuevo(const char *nombreArchivo)
{
	return new Bitacora(nombreArchivo);
}
