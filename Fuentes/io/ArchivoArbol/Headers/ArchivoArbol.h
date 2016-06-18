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

class ArchivoArbol: public iArchivoArbol
{
	private:
		size_t tolerancia;			// Tolerancia a la carga mínima en bytes
		size_t tamanioNodo;			// Define el tamanio del bloque en bytes
		size_t cargaMinima;			// Carga mínima por nodo        en bytes
		iMapaDeBitsPtr mapaDeBits;
		iArchivoBloquePtr archivoBloque;
		iHidratadorNodoPtr hidratadorNodo;
		iSerializadorNodoPtr serializadorNodo;

		// Necesario para fabricar nodos nuevos
		eTipoArbol tipoArbol;

		virtual ~ArchivoArbol();
	public:
		ArchivoArbol(const char *nombreArchivo, size_t tamanioNodo, size_t cargaMinima, size_t tolerancia, eTipoArbol tipoArbol);

		iNodoPtr LeerNodo(size_t nroNodo);

		void EscribirNodo(size_t nroNodo, iNodoPtr pNodo);

		size_t NuevoNodo(size_t origen, iNodoPtr *nodo, size_t tipoNodo);

		eEstadoCargaNodo DeterminarEstadoNodo(iNodoPtr nodo);

		float DeterminarPorcentajeCarga(iNodoPtr nodo);

		void LiberarNodo(size_t nroNodo);

		void Close();

	private:
		virtual size_t GetNodoLibre(size_t origen);

		virtual eEstadoCargaNodo DeterminarEstadoNodo(size_t tamanioSerializacion);

		virtual iBloquePtr SerializarNodo(iNodoPtr nodo);

		virtual iNodoPtr HidratarNodo(iBloquePtr bloque);
};

#endif	/* ARCHIVOARBOL_H */

