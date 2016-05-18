/* 
 * File:   ArchivoArbolFactory.h
 * Author: Monty
 *
 * Created on 26 de abril de 2016, 00:22
 */

#ifndef ARCHIVOARBOLFACTORY_H
#define	ARCHIVOARBOLFACTORY_H

#include "Headers/iArchivoArbol.h"

iArchivoArbolPtr ArchivoArbolFactory_Nuevo(const char *_nombreArchivo,
		size_t _tamanioNodo, size_t _cargaMinima, size_t _tolerancia,
		eSerializadorNodo _typeSerializer, eHidratadorNodo _typeHydrator);

#endif	/* ARCHIVOARBOLFACTORY_H */

