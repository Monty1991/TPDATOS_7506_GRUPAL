/* 
 * File:   NodoFactory.h
 * Author: Monty
 *
 * Created on 25 de abril de 2016, 22:47
 */

#ifndef NODOFACTORY_H
#define	NODOFACTORY_H

#include "Headers/iNodo.h"

iNodoPtr NodoFactory_Nuevo(size_t altura, iRegistroPtr *listaRegistros, size_t cantidadRegistros);

#endif	/* NODOFACTORY_H */
