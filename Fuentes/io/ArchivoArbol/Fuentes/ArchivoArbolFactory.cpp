#include "../ArchivoArbolFactory.h"
#include "../Headers/ArchivoArbol.h"

iArchivoArbolPtr ArchivoArbolFactory_Nuevo(const char *nombreArchivo, size_t tamanioNodo, size_t cargaMinima, size_t tolerancia, eTipoArbol tipoArbol)
{
	return new ArchivoArbol(nombreArchivo, tamanioNodo, cargaMinima, tolerancia, tipoArbol);
}
