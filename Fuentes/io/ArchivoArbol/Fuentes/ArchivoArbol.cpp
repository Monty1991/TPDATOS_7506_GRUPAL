#include "../Headers/ArchivoArbol.h"
#include "../../ArchivoBloque/ArchivoBloqueFactory.h"
#include "../../../Utils/MapaDeBits/MapaDeBitsFactory.h"
#include "../../../Serializadores/SerializadorNodo/SerializadorNodoFactory.h"
#include "../../../Hidratadores/HidratadorNodo/HidratadorNodoFactory.h"
#include "../../../Utils/Bloque/BloqueFactory.h"
#include "../../../Exceptions/ExceptionFactory.h"

ArchivoArbol::ArchivoArbol(const char *_nombreArchivo, size_t _tamanioNodo,
		size_t _cargaMinima, size_t _tolerancia,
		eSerializadorNodo _typeSerializer, eHidratadorNodo _typeHydrator) :
		tamanioNodo(_tamanioNodo), cargaMinima(_cargaMinima), tolerancia(
				_tolerancia) {

	this->archivoBloque = ArchivoBloqueFactory_Nuevo(_nombreArchivo,
			tamanioNodo);
	this->serializadorNodo = SerializadorNodoFactory_Nuevo(_typeSerializer);
	this->hidratadorNodo = HidratadorNodoFactory_Nuevo(_typeHydrator);

	iBloquePtr bloque = this->archivoBloque->LeerBloque(0);

	this->mapaDeBits = MapaDeBitsFactory_Nuevo(bloque);

	bloque->Dispose();
}

ArchivoArbol::~ArchivoArbol() {

	// El mapa de bits se actualiza en disco siempre que se modifica
	// Por eso es seguro liberarlo en memoria
	if (this->mapaDeBits) {

		this->mapaDeBits->Dispose();
		this->mapaDeBits = NULL;
	}

	if (this->archivoBloque) {

		this->archivoBloque->Close();
		this->archivoBloque = NULL;
	}

	if (this->hidratadorNodo) {

		this->hidratadorNodo->Dispose();
		this->hidratadorNodo = NULL;
	}

	if (this->serializadorNodo) {

		this->serializadorNodo->Dispose();
		this->serializadorNodo = NULL;
	}

}

void ArchivoArbol::Close() {

	delete this;
}

size_t ArchivoArbol::GetNodoLibre() {

	for (size_t i = 0; i < this->mapaDeBits->ObtenerTamanio(); i++)
		if (!this->mapaDeBits->ObtenerBit(i))
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

iBloquePtr ArchivoArbol::SerializarNodo(iNodoPtr _nodo) {

	char * buffer = new char[tamanioNodo];

	this->serializadorNodo->Serializar(buffer, _nodo);

	iBloquePtr bloque = BloqueFactory_Nuevo(buffer, tamanioNodo);

	delete[] buffer;
	return bloque;
}

iNodoPtr ArchivoArbol::HidratarNodo(iBloquePtr _bloque) {

	return NULL;
}

iNodoPtr ArchivoArbol::LeerNodo(size_t _nroNodo) {

	if (_nroNodo < this->mapaDeBits->ObtenerTamanio())
		if (this->mapaDeBits->ObtenerBit(_nroNodo)) {

			iBloquePtr bloque = this->archivoBloque->LeerBloque(++_nroNodo);

			iNodoPtr nodo = HidratarNodo(bloque);

			delete bloque;
			return nodo;
		}

	Throw(" ", "Número de nodo inválido");
}

void ArchivoArbol::EscribirNodo(size_t _nroNodo, iNodoPtr _nodo) {

}

size_t ArchivoArbol::NuevoNodo(iNodoPtr *_nodo) {

	return 0;
}

eEstadoCargaNodo ArchivoArbol::DeterminarEstadoNodo(iNodoPtr _nodo) {

	return DeterminarEstadoNodo(
			this->serializadorNodo->CalcularEspacioSerializacion(_nodo));
}

void ArchivoArbol::LiberarNodo(size_t _nroNodo) {

	if (_nroNodo < this->mapaDeBits->ObtenerTamanio()) {

		this->mapaDeBits->SetearBit(_nroNodo, false);

		iBloquePtr bloque = this->mapaDeBits->Leer();
		this->archivoBloque->EscribirBloque(0, bloque);

		delete bloque;
		return;
	}

	Throw(" ", "Número de nodo inválido");
}

