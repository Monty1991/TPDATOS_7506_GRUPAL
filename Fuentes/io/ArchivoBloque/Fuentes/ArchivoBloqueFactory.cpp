#include "../Headers/ArchivoBloque.h"

iArchivoBloquePtr ArchivoBloqueFactory_Nuevo(const char *nombre, size_t tamanioBloque)
{
	return new ArchivoBloque(nombre, tamanioBloque);
}
