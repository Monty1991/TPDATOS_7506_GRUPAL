/* 
 * File:   ArchivoFactory.h
 * Author: Monty
 *
 * Created on 16 de marzo de 2016, 12:30
 */

#ifndef ARCHIVOFACTORY_H
#define	ARCHIVOFACTORY_H

#include "Headers/iArchivo.h"

typedef enum eTipoArchivo
{
	eTipoArchivo_Binario,
	eTipoArchivo_Texto,
	eTipoArchivo_Log
} eTipoArchivo, *eTipoArchivoPtr;

iArchivoPtr ArchivoFactory_Nuevo(const char *nombre, eTipoArchivo tipoArchivo);

#endif	/* ARCHIVOFACTORY_H */
