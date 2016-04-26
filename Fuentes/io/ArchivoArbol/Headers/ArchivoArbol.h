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

class ArchivoArbol
{
	private:
		iArchivoBloquePtr archivoBloque;
		iMapaDeBitsPtr mapaDeBits;

	public:
		ArchivoArbol(const char *nombreArchivo, size_t tamanioBloque, void *esquemaRegistroDato, void *esquemaRegistroInterno);
		virtual ~ArchivoArbol();
		
		virtual void Close();
};

#endif	/* ARCHIVOARBOL_H */

