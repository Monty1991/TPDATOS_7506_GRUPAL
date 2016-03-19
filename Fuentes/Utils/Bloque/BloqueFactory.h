/* 
 * File:   BloqueFactory.h
 * Author: Monty
 *
 * Created on 19 de marzo de 2016, 00:24
 */

#ifndef BLOQUEFACTORY_H
#define	BLOQUEFACTORY_H

#include "Headers/iBloque.h"
#include <stddef.h>

iBloquePtr BloqueFactory_Nuevo(const char *buffer, size_t tamanioBloque);

#endif	/* BLOQUEFACTORY_H */
