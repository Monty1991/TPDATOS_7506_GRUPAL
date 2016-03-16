/* 
 * File:   ArchivoFactory.h
 * Author: Monty
 *
 * Created on 16 de marzo de 2016, 12:30
 */

#ifndef ARCHIVOFACTORY_H
#define	ARCHIVOFACTORY_H

#include "Headers/iArchivo.h"

iArchivoPtr ArchivoFactory_Nuevo(const char *nombre);

#endif	/* ARCHIVOFACTORY_H */

