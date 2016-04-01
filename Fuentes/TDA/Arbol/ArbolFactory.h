/* 
 * File:   ArbolFactory.h
 * Author: Monty
 *
 * Created on 1 de abril de 2016, 00:46
 */

#ifndef ARBOLFACTORY_H
#define	ARBOLFACTORY_H

#include "Headers/iArbol.h"

iArbolPtr ArbolFactory_Nuevo(int key, iObjectPtr valor);

#endif	/* ARBOLFACTORY_H */

