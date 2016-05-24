/* 
 * File:   NodoArbolPuntoOptimoFactory.h
 * Author: Monty
 *
 * Created on 24 de mayo de 2016, 00:07
 */

#ifndef NODOARBOLPUNTOOPTIMOFACTORY_H
#define NODOARBOLPUNTOOPTIMOFACTORY_H

#include "Headers/iNodoArbolPuntoOptimo.h"

//	Devuelve un nodo vacio
iNodoArbolPuntoOptimoNodoHojaPtr NodoArbolPuntoOptimoFactory_Nuevo(eNodoArbolPuntoOptimo tipoNodo);

iNodoArbolPuntoOptimoNodoHojaPtr NodoArbolPuntoOptimoFactory_Nuevo(eNodoArbolPuntoOptimo tipoNodo, iRegistroPtr *listaRegistros, size_t cantidadRegistros);

#endif /* NODOARBOLPUNTOOPTIMOFACTORY_H */
