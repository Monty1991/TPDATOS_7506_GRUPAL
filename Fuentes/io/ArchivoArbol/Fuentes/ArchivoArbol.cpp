#include "../Headers/ArchivoArbol.h"
#include "../../ArchivoBloque/ArchivoBloqueFactory.h"
#include "../../../Utils/MapaDeBits/MapaDeBitsFactory.h"
#include "../../../Serializadores/SerializadorNodo/SerializadorNodoFactory.h"
#include "../../../Hidratadores/HidratadorNodo/HidratadorNodoFactory.h"
#include "../../../Utils/Bloque/BloqueFactory.h"
#include "../../../Exceptions/ExceptionFactory.h"
#include "../../../Utils/Nodo/NodoFactory.h"

ArchivoArbol::ArchivoArbol(const char *_nombreArchivo, size_t _tamanioNodo,
		size_t _cargaMinima, size_t _tolerancia, eTipoArbol tipoArbol) :
		tamanioNodo(_tamanioNodo), cargaMinima(_cargaMinima), tolerancia(
				_tolerancia) {

	archivoBloque = ArchivoBloqueFactory_Nuevo(_nombreArchivo, tamanioNodo);
	serializadorNodo = SerializadorNodoFactory_Nuevo(tipoArbol);
	hidratadorNodo = HidratadorNodoFactory_Nuevo(tipoArbol);

	iBloquePtr pBloque = archivoBloque->LeerBloque(0);
	mapaDeBits = MapaDeBitsFactory_Nuevo(pBloque);

	pBloque->Dispose();
}

ArchivoArbol::~ArchivoArbol() {

	// El mapa de bits se actualiza en disco siempre que se modifica
	// Por eso es seguro liberarlo en memoria
	if (mapaDeBits) {

		mapaDeBits->Dispose();
		mapaDeBits = NULL;
	}

	if (archivoBloque) {

		archivoBloque->Close();
		archivoBloque = NULL;
	}

	if (hidratadorNodo) {

		hidratadorNodo->Dispose();
		hidratadorNodo = NULL;
	}

	if (serializadorNodo) {

		serializadorNodo->Dispose();
		serializadorNodo = NULL;
	}

}

void ArchivoArbol::Close() {

	delete this;
}

size_t ArchivoArbol::GetNodoLibre() {

	for (size_t i = 0; i < mapaDeBits->ObtenerTamanio(); i++)
		if (!mapaDeBits->ObtenerBit(i))
			return i;

	Throw(" ", "No hay nodos libres");
}

eEstadoCargaNodo ArchivoArbol::DeterminarEstadoNodo(
		size_t _tamanioSerializacion) {

	if (_tamanioSerializacion > tamanioNodo)
		return eEstadoCargaNodo_Overflow;
	else if (_tamanioSerializacion > cargaMinima)
		return eEstadoCargaNodo_NoCargaMinima;
	else if (_tamanioSerializacion > (cargaMinima - tolerancia))
		return eEstadoCargaNodo_CargaMinima;
	else
		return eEstadoCargaNodo_Underflow;
}

iBloquePtr ArchivoArbol::SerializarNodo(iNodoPtr _pNodo) {

	char * buffer = new char[tamanioNodo];

	serializadorNodo->Serializar(buffer, _pNodo);
	iBloquePtr pBloque = BloqueFactory_Nuevo(buffer, tamanioNodo);

	delete[] buffer;
	return pBloque;
}

iNodoPtr ArchivoArbol::HidratarNodo(iBloquePtr _pBloque) {

	iNodoPtr pNodo = NULL;
	iNodoPtr * ppNodo = &pNodo;

	hidratadorNodo->Hidratar((char*) _pBloque->ObtenerContenido(), ppNodo);

	return pNodo;
}

iNodoPtr ArchivoArbol::LeerNodo(size_t _nroNodo) {

	if (_nroNodo < mapaDeBits->ObtenerTamanio())
		if (mapaDeBits->ObtenerBit(_nroNodo)) {

			iBloquePtr pBloque = archivoBloque->LeerBloque(++_nroNodo);
			iNodoPtr pNodo = HidratarNodo(pBloque);

			pBloque->Dispose();
			return pNodo;
		}

	Throw(" ", "Número de nodo inválido");
}

void ArchivoArbol::EscribirNodo(size_t _nroNodo, iNodoPtr _pNodo) {

	iBloquePtr pBloque = NULL;
	eEstadoCargaNodo carga;

	if (_nroNodo >= mapaDeBits->ObtenerTamanio())
		Throw(" ", "Número de nodo inválido");

	carga = DeterminarEstadoNodo(_pNodo);

	if (carga == eEstadoCargaNodo_Underflow)
		Throw(" ", "Nodo en underflow");

	if (carga == eEstadoCargaNodo_Overflow)
		Throw(" ", "Nodo en overflow");

	pBloque = SerializarNodo(_pNodo);
	archivoBloque->EscribirBloque(_nroNodo + 1, pBloque);

	pBloque->Dispose();
	pBloque = NULL;

	if (!mapaDeBits->ObtenerBit(_nroNodo)) {

		mapaDeBits->SetearBit(_nroNodo, true);

		pBloque = mapaDeBits->Leer();
		archivoBloque->EscribirBloque(0, pBloque);

		pBloque->Dispose();
	}
}

size_t ArchivoArbol::NuevoNodo(iNodoPtr *_ppNodo) {

	*_ppNodo = NodoFactory_Nuevo();
	return GetNodoLibre();
}

eEstadoCargaNodo ArchivoArbol::DeterminarEstadoNodo(iNodoPtr _pNodo) {

	return DeterminarEstadoNodo(
			serializadorNodo->CalcularEspacioSerializacion(_pNodo));
}

void ArchivoArbol::LiberarNodo(size_t _nroNodo) {

	if (_nroNodo < mapaDeBits->ObtenerTamanio()) {

		mapaDeBits->SetearBit(_nroNodo, false);

		iBloquePtr pBloque = mapaDeBits->Leer();
		archivoBloque->EscribirBloque(0, pBloque);

		pBloque->Dispose();
		return;
	}

	Throw(" ", "Número de nodo inválido");
}

