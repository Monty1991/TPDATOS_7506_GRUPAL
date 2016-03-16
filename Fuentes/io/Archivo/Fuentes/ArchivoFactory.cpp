#include "../ArchivoFactory.h"
#include "../Headers/Archivo.h"

iArchivoPtr ArchivoFactory_Nuevo(const char *nombre)
{
	return new Archivo(nombre);
}
