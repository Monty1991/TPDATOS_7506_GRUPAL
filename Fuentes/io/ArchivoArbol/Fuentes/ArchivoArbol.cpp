#include "../Headers/ArchivoArbol.h"
#include "../../ArchivoBloque/ArchivoBloqueFactory.h"
#include "../../../Utils/MapaDeBits/MapaDeBitsFactory.h"

ArchivoArbol::ArchivoArbol(const char *nombreArchivo, size_t tamanioBloque, void *esquemaRegistroDato, void *esquemaRegistroInterno)
{
	this->archivoBloque = ArchivoBloqueFactory_Nuevo(nombreArchivo, tamanioBloque);

	iBloquePtr bloque = this->archivoBloque->LeerBloque(0);

	this->mapaDeBits = MapaDeBitsFactory_Nuevo(bloque);

	bloque->Dispose();
}

ArchivoArbol::~ArchivoArbol()
{
	// El mapa de bits se actualiza en disco siempre que se modifica
	// Por eso es seguro liberarlo en memoria
	if (this->mapaDeBits)
	{
		this->mapaDeBits->Dispose();
		this->mapaDeBits = NULL;
	}

	if (this->archivoBloque)
	{
		this->archivoBloque->Close();
		this->archivoBloque = NULL;
	}
}

void ArchivoArbol::Close()
{
	delete this;
}
