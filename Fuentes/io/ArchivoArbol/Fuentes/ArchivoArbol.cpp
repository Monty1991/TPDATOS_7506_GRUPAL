#include "../Headers/ArchivoArbol.h"
#include "../../ArchivoBloque/ArchivoBloqueFactory.h"
#include "../../../Utils/MapaDeBits/MapaDeBitsFactory.h"
#include "../../../Serializadores/SerializadorNodo/SerializadorNodoFactory.h"
#include "../../../Hidratadores/HidratadorNodo/HidratadorNodoFactory.h"
#include "../../../Utils/Bloque/BloqueFactory.h"
#include "../../../Exceptions/ExceptionFactory.h"
#include "../../../Utils/Nodo/NodoFactory.h"

ArchivoArbol::ArchivoArbol(const char *_nombreArchivo, size_t _tamanioNodo, size_t _cargaMinima, size_t _tolerancia, eTipoArbol tipoArbol) : tamanioNodo(_tamanioNodo), cargaMinima(_cargaMinima), tolerancia(_tolerancia), tipoArbol(tipoArbol)
{
	this->archivoBloque = ArchivoBloqueFactory_Nuevo(_nombreArchivo, tamanioNodo);
	this->serializadorNodo = SerializadorNodoFactory_Nuevo(tipoArbol);
	this->hidratadorNodo = HidratadorNodoFactory_Nuevo(tipoArbol);

	this->mapaDeBits = MapaDeBitsFactory_Nuevo(archivoBloque->LeerBloque(0));
}

ArchivoArbol::~ArchivoArbol()
{
	// El mapa de bits se actualiza en disco siempre que se modifica
	// Por eso es seguro liberarlo en memoria
	if (mapaDeBits)
	{
		mapaDeBits->Dispose();
		mapaDeBits = NULL;
	}

	if (archivoBloque)
	{
		archivoBloque->Close();
		archivoBloque = NULL;
	}

	if (hidratadorNodo)
	{
		hidratadorNodo->Dispose();
		hidratadorNodo = NULL;
	}

	if (serializadorNodo)
	{
		serializadorNodo->Dispose();
		serializadorNodo = NULL;
	}

}

void ArchivoArbol::Close()
{
	delete this;
}

float ArchivoArbol::DeterminarPorcentajeCarga(iNodoPtr _pNodo)
{
    return (serializadorNodo->CalcularEspacioSerializacion(_pNodo) * 100) / tamanioNodo;
}

size_t ArchivoArbol::GetNodoLibre(size_t origen)
{
	for (size_t i = origen; i < mapaDeBits->ObtenerTamanio(); i++)
		if (!mapaDeBits->ObtenerBit(i))
			return i;

	Throw(" ", "No hay nodos libres");
}

eEstadoCargaNodo ArchivoArbol::DeterminarEstadoNodo(size_t _tamanioSerializacion)
{
	if (_tamanioSerializacion > tamanioNodo)
		return eEstadoCargaNodo_Overflow;

	if (_tamanioSerializacion > cargaMinima)
		return eEstadoCargaNodo_NoCargaMinima;

	if (_tamanioSerializacion > (cargaMinima - tolerancia))
		return eEstadoCargaNodo_CargaMinima;

	return eEstadoCargaNodo_Underflow;
}

iBloquePtr ArchivoArbol::SerializarNodo(iNodoPtr _pNodo)
{
	char buffer[this->tamanioNodo];
	for (size_t i = 0; i < this->tamanioNodo; i++)
		buffer[i] = 0;

	this->serializadorNodo->Serializar(buffer, _pNodo);
	return BloqueFactory_Nuevo(buffer, this->tamanioNodo);
}

iNodoPtr ArchivoArbol::HidratarNodo(iBloquePtr _pBloque)
{
	iNodoPtr pNodo = NULL;

	this->hidratadorNodo->Hidratar((char*) _pBloque->ObtenerContenido(), &pNodo);

	return pNodo;
}

iNodoPtr ArchivoArbol::LeerNodo(size_t _nroNodo)
{
	if (_nroNodo < this->mapaDeBits->ObtenerTamanio())
		if (this->mapaDeBits->ObtenerBit(_nroNodo))
		{
			iBloquePtr pBloque = archivoBloque->LeerBloque(_nroNodo + 1);
			iNodoPtr pNodo = this->HidratarNodo(pBloque);

			pBloque->Dispose();
			return pNodo;
		}

	return NULL;
}

void ArchivoArbol::EscribirNodo(size_t _nroNodo, iNodoPtr _pNodo)
{
	if (_nroNodo >= mapaDeBits->ObtenerTamanio())
		Throw(ExceptionType_ArrayIndexOutOfBounds, "Número de nodo inválido");

	iBloquePtr pBloque = this->SerializarNodo(_pNodo);
	this->archivoBloque->EscribirBloque(_nroNodo + 1, pBloque);

	pBloque->Dispose();

	if (!this->mapaDeBits->ObtenerBit(_nroNodo))
	{
		this->mapaDeBits->SetearBit(_nroNodo, true);
		this->archivoBloque->EscribirBloque(0, mapaDeBits->Leer());
	}
}

size_t ArchivoArbol::NuevoNodo(size_t origen, iNodoPtr *_ppNodo, size_t tipoNodo)
{
	*_ppNodo = NodoFactory_Nuevo(this->tipoArbol, tipoNodo);
	return GetNodoLibre(origen);
}

eEstadoCargaNodo ArchivoArbol::DeterminarEstadoNodo(iNodoPtr _pNodo)
{
	return DeterminarEstadoNodo(this->serializadorNodo->CalcularEspacioSerializacion(_pNodo));
}

void ArchivoArbol::LiberarNodo(size_t _nroNodo)
{
	if (_nroNodo >= mapaDeBits->ObtenerTamanio())
		Throw(ExceptionType_ArrayIndexOutOfBounds, "Número de nodo inválido");

	if (this->mapaDeBits->ObtenerBit(_nroNodo))
	{
		mapaDeBits->SetearBit(_nroNodo, false);
		archivoBloque->EscribirBloque(0, mapaDeBits->Leer());
	}
}

