/* 
 * File:   iArchivoArbol.h
 * Author: Monty
 *
 * Created on 26 de abril de 2016, 00:14
 */

#ifndef IARCHIVOARBOL_H
#define	IARCHIVOARBOL_H

#include "../../../Utils/Nodo/Headers/iNodo.h"

typedef class iArchivoArbol
{
	public:
		virtual void Close() = 0;

		// Si el nro de nodo hace referencia a un nodo libre, devuelve NULL
		virtual iNodoPtr LeerNodo(size_t nroNodo) = 0;

		// Escribe un nodo en la posicion de nodo indicada
		virtual void EscribirNodo(size_t nroNodo, iNodoPtr nodo) = 0;

		// Devuelve el nro de nodo mas pequenio que referencia a un nodo libre
		// Y crea un nodo vacio y lo asigna al puntero referenciado.
		virtual size_t NuevoNodo(iNodoPtr *nodo) = 0;

		// Devuelve uno de los valores, dependiendo del estado del nodo
		virtual eEstadoCargaNodo DeterminarEstadoNodo(iNodoPtr nodo) = 0;

} *iArchivoArbolPtr;

#endif	/* IARCHIVOARBOL_H */
