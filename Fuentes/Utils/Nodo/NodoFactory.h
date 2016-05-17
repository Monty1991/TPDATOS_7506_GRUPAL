/* 
 * File:   NodoFactory.h
 * Author: Monty
 *
 * Created on 25 de abril de 2016, 22:47
 */

#ifndef NODOFACTORY_H
#define	NODOFACTORY_H

#include "Headers/iNodo.h"

// devuelve un nodo vacio, de tipo hoja, por defecto.
iNodoPtr NodoFactory_Nuevo();

iNodoPtr NodoFactory_Nuevo(eTipoNodo tipo, iRegistroPtr *listaRegistros, size_t cantidadRegistros);

#endif	/* NODOFACTORY_H */
