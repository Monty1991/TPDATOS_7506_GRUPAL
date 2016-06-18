#include "../Headers/ArchivoArbol.h"
#include "../../ArchivoBloque/ArchivoBloqueFactory.h"
#include "../../../Utils/MapaDeBits/MapaDeBitsFactory.h"
#include "../../../Serializadores/SerializadorNodo/SerializadorNodoFactory.h"
#include "../../../Hidratadores/HidratadorNodo/HidratadorNodoFactory.h"
#include "../../../Utils/Bloque/BloqueFactory.h"
#include "../../../Exceptions/ExceptionFactory.h"
#include "../../../Utils/Nodo/NodoFactory.h"

ArchivoArbol::ArchivoArbol(const char *nombreArchivo, size_t tamanioNodo, size_t cargaMinima, size_t tolerancia, eTipoArbol tipoArbol): tamanioNodo(tamanioNodo), cargaMinima(cargaMinima), tolerancia(tolerancia), tipoArbol(tipoArbol)
{
	this->archivoBloque = ArchivoBloqueFactory_Nuevo(nombreArchivo, this->tamanioNodo);
	this->serializadorNodo = SerializadorNodoFactory_Nuevo(this->tipoArbol);
	this->hidratadorNodo = HidratadorNodoFactory_Nuevo(this->tipoArbol);

	this->mapaDeBits = MapaDeBitsFactory_Nuevo(this->archivoBloque->LeerBloque(0));
}

ArchivoArbol::~ArchivoArbol()
{
	// El mapa de bits se actualiza en disco siempre que se modifica
	// Por eso es seguro liberarlo en memoria
	if (this->mapaDeBits)
		this->mapaDeBits->Dispose();

	if (this->archivoBloque)
		this->archivoBloque->Close();

	if (this->hidratadorNodo)
		this->hidratadorNodo->Dispose();

	if (this->serializadorNodo)
		this->serializadorNodo->Dispose();
}


iNodoPtr ArchivoArbol::LeerNodo(size_t nroNodo)
{
	if (nroNodo < this->mapaDeBits->ObtenerTamanio())
		if (this->mapaDeBits->ObtenerBit(nroNodo))
		{
			iBloquePtr bloque = this->archivoBloque->LeerBloque(nroNodo + 1);
			iNodoPtr nodo = this->HidratarNodo(bloque);

			bloque->Dispose();
			return nodo;
		}

	return NULL;
}

void ArchivoArbol::EscribirNodo(size_t nroNodo, iNodoPtr nodo)
{
	if (nroNodo >= this->mapaDeBits->ObtenerTamanio())
		Throw(ExceptionType_ArrayIndexOutOfBounds, "Numero de nodo invalido");

	iBloquePtr bloque = this->SerializarNodo(nodo);
	this->archivoBloque->EscribirBloque(nroNodo + 1, bloque);

	bloque->Dispose();

	if (!this->mapaDeBits->ObtenerBit(nroNodo))
	{
		this->mapaDeBits->SetearBit(nroNodo, true);
		this->archivoBloque->EscribirBloque(0, this->mapaDeBits->Leer());
	}
}

size_t ArchivoArbol::NuevoNodo(size_t origen, iNodoPtr *nodo, size_t tipoNodo)
{
	*nodo = NodoFactory_Nuevo(this->tipoArbol, tipoNodo);
	return this->GetNodoLibre(origen);
}

eEstadoCargaNodo ArchivoArbol::DeterminarEstadoNodo(iNodoPtr nodo)
{
	return this->DeterminarEstadoNodo(this->serializadorNodo->CalcularEspacioSerializacion(nodo));
}

float ArchivoArbol::DeterminarPorcentajeCarga(iNodoPtr nodo)
{
    return (this->serializadorNodo->CalcularEspacioSerializacion(nodo) * 100.0) / this->tamanioNodo;
}

void ArchivoArbol::LiberarNodo(size_t nroNodo)
{
	if (nroNodo >= this->mapaDeBits->ObtenerTamanio())
		Throw(ExceptionType_ArrayIndexOutOfBounds, "Numero de nodo invalido");

	if (this->mapaDeBits->ObtenerBit(nroNodo))
	{
		this->mapaDeBits->SetearBit(nroNodo, false);
		this->archivoBloque->EscribirBloque(0, this->mapaDeBits->Leer());
	}
}

void ArchivoArbol::Close()
{
	delete this;
}

size_t ArchivoArbol::GetNodoLibre(size_t origen)
{
	for (size_t i = origen; i < this->mapaDeBits->ObtenerTamanio(); i++)
		if (!this->mapaDeBits->ObtenerBit(i))
			return i;

	Throw("Out of storage", "No hay nodos libres");
}

eEstadoCargaNodo ArchivoArbol::DeterminarEstadoNodo(size_t tamanioSerializacion)
{
	if (tamanioSerializacion > this->tamanioNodo)
		return eEstadoCargaNodo::eEstadoCargaNodo_Overflow;

	if (tamanioSerializacion > this->cargaMinima)
		return eEstadoCargaNodo::eEstadoCargaNodo_NoCargaMinima;

	if (tamanioSerializacion > (this->cargaMinima - this->tolerancia))
		return eEstadoCargaNodo::eEstadoCargaNodo_CargaMinima;

	return eEstadoCargaNodo::eEstadoCargaNodo_Underflow;
}

iBloquePtr ArchivoArbol::SerializarNodo(iNodoPtr nodo)
{
	char buffer[this->tamanioNodo];
	for (size_t i = 0; i < this->tamanioNodo; i++)
		buffer[i] = 0;

	this->serializadorNodo->Serializar(buffer, nodo);
	return BloqueFactory_Nuevo(buffer, this->tamanioNodo);
}

iNodoPtr ArchivoArbol::HidratarNodo(iBloquePtr bloque)
{
	iNodoPtr nodo = NULL;

	this->hidratadorNodo->Hidratar(bloque->ObtenerContenido(), &nodo);

	return nodo;
}
