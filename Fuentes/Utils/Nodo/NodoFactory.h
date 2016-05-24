/* 
 * File:   NodoFactory.h
 * Author: Monty
 *
 * Created on 25 de abril de 2016, 22:47
 */

#ifndef NODOFACTORY_H
#define	NODOFACTORY_H

#include "Headers/iNodo.h"

// Devuelve un nodo vacio
iNodoPtr NodoFactory_Nuevo(eTipoArbol tipoArbol, size_t tipoNodo);

iNodoPtr NodoFactory_Nuevo(eTipoArbol tipoArbol, size_t tipoNodo, iRegistroPtr *listaRegistros, size_t cantidadRegistros);

#endif	/* NODOFACTORY_H */
