/* 
 * File:   Logger.h
 * Author: Monty
 *
 * Created on 15 de marzo de 2016, 22:16
 */

#ifndef LOGGER_H
#define	LOGGER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "Headers/iBitacora.h"

iBitacoraPtr BitacoraFactory_Nuevo(const char *nombreArchivo);

#ifdef	__cplusplus
}
#endif

#endif	/* LOGGER_H */
