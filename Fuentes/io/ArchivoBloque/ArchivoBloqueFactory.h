/* 
 * File:   ArchivoBloqueFactory.h
 * Author: Monty
 *
 * Created on 17 de marzo de 2016, 03:33
 */

#ifndef ARCHIVOBLOQUEFACTORY_H
#define	ARCHIVOBLOQUEFACTORY_H

#include "Headers/iArchivoBloque.h"

iArchivoBloquePtr ArchivoBloqueFactory_Nuevo(const char *nombre, size_t tamanioBloque);

#endif	/* ARCHIVOBLOQUEFACTORY_H */
