/* 
 * File:   ArchivoArbol.h
 * Author: Monty
 *
 * Created on 26 de abril de 2016, 00:24
 */

#ifndef ARCHIVOARBOL_H
#define	ARCHIVOARBOL_H

#include "iArchivoArbol.h"
#include "../../ArchivoBloque/Headers/iArchivoBloque.h"
#include "../../../Utils/MapaDeBits/Headers/iMapaDeBits.h"

class ArchivoArbol: public iArchivoArbol {

private:

	size_t tolerancia;  // Tolerancia a la carga mínima en bytes
	size_t tamanioNodo; // Define el tamanio del bloque en bytes
	size_t cargaMinima; // Carga mínima por nodo        en bytes
	iMapaDeBitsPtr mapaDeBits;
	iArchivoBloquePtr archivoBloque;
	iHidratadorNodoPtr hidratadorNodo;
	iSerializadorNodoPtr serializadorNodo;

	virtual ~ArchivoArbol();

	size_t GetNodoLibre();

	eEstadoCargaNodo DeterminarEstadoNodo(size_t _tamanioSerializacion);

	iBloquePtr SerializarNodo(iNodoPtr _nodo);

	iNodoPtr HidratarNodo(iBloquePtr _bloque);

public:

	ArchivoArbol(const char *_nombreArchivo, size_t _tamanioNodo,
			size_t _cargaMinima, size_t _tolerancia,
			eTipoArbol tipoArbol);

	iNodoPtr LeerNodo(size_t _nroNodo);

	void EscribirNodo(size_t _nroNodo, iNodoPtr _nodo);

	size_t NuevoNodo(iNodoPtr *_nodo);

	eEstadoCargaNodo DeterminarEstadoNodo(iNodoPtr _nodo);

	void LiberarNodo(size_t _nroNodo);

	void Close();

};

#endif	/* ARCHIVOARBOL_H */

