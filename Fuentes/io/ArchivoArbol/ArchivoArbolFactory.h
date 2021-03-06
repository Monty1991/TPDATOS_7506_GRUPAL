/* 
 * File:   ArchivoArbolFactory.h
 * Author: Monty
 *
 * Created on 26 de abril de 2016, 00:22
 */

#ifndef ARCHIVOARBOLFACTORY_H
#define	ARCHIVOARBOLFACTORY_H

#include "Headers/iArchivoArbol.h"

iArchivoArbolPtr ArchivoArbolFactory_Nuevo(const char *nombreArchivo, size_t tamanioNodo, size_t cargaMinima, size_t tolerancia, eTipoArbol tipoArbol);

#endif	/* ARCHIVOARBOLFACTORY_H */

