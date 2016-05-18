/* 
 * File:   iArchivoArbol.h
 * Author: Monty
 *
 * Created on 26 de abril de 2016, 00:14
 */

#ifndef IARCHIVOARBOL_H
#define	IARCHIVOARBOL_H

#include "../../../Utils/Nodo/Headers/iNodo.h"
#include "../../../Serializadores/SerializadorNodo/Headers/iSerializadorNodo.h"
#include "../../../Hidratadores/HidratadorNodo/Headers/iHidratadorNodo.h"

typedef class iArchivoArbol {

public:

	// Si el nro de nodo hace referencia a un nodo libre, devuelve NULL
	virtual iNodoPtr LeerNodo(size_t _nroNodo) = 0;

	// Escribe un nodo en la posicion de nodo indicada
	virtual void EscribirNodo(size_t _nroNodo, iNodoPtr _nodo) = 0;

	// Devuelve el nro de nodo mas pequenio que referencia a un nodo libre
	// Y crea un nodo vacio y lo asigna al puntero referenciado.
	virtual size_t NuevoNodo(iNodoPtr *_nodo) = 0;

	// Devuelve uno de los valores, dependiendo del estado del nodo
	virtual eEstadoCargaNodo DeterminarEstadoNodo(iNodoPtr _nodo) = 0;

	// Libera el nodo que se encuentra en la posición pasada como parámetro.
	virtual void LiberarNodo(size_t _nroNodo) = 0;

	// Cierra el archivo y libera los recursos de memoria.
	virtual void Close() = 0;

}*iArchivoArbolPtr;

#endif	/* IARCHIVOARBOL_H */
