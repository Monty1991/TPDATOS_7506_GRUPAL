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
#include "../../../Serializadores/SerializadorNodo/Headers/iSerializadorNodo.h"
#include "../../../Hidratadores/HidratadorNodo/Headers/iHidratadorNodo.h"

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

	iBloquePtr SerializarNodo(iNodoPtr _pNodo);

	iNodoPtr HidratarNodo(iBloquePtr _pBloque);

public:

	ArchivoArbol(const char *_nombreArchivo, size_t _tamanioNodo,
			size_t _cargaMinima, size_t _tolerancia, eTipoArbol tipoArbol);

	iNodoPtr LeerNodo(size_t _nroNodo);

	void EscribirNodo(size_t _nroNodo, iNodoPtr _pNodo);

	size_t NuevoNodo(iNodoPtr *_ppNodo);

	eEstadoCargaNodo DeterminarEstadoNodo(iNodoPtr _pNodo);

	void LiberarNodo(size_t _nroNodo);

	void Close();

};

#endif	/* ARCHIVOARBOL_H */

