/* 
 * File:   iArchivoArbol.h
 * Author: Monty
 *
 * Created on 26 de abril de 2016, 00:14
 */

#ifndef IARCHIVOARBOL_H
#define	IARCHIVOARBOL_H

#include "../../../Utils/Nodo/Headers/iNodo.h"

enum eArbolError
{
	eArbolError_NoErr,		//	Operacion exitosa
	eArbolError_Overflow,	//	El nodo no se pudo serializar: excede la capacidad del nodo
	eArbolError_Underflow	//	El nodo quedo con menos de la carga minima
};

typedef class iArchivoArbol
{
	public:
		virtual void Close() = 0;

		// Devuelve el nro de nodo mas pequenio que referencia a un nodo libre
		// ayuda a reducir la fragmentacion del archivo
		virtual size_t ObtenerNroNodoLibre() = 0;

		virtual eArbolError EscribirNodo(size_t nroNodo, iNodoPtr nodo) = 0;

		// Si el nro de nodo hace referencia a un nodo libre, devuelve NULL
		virtual iNodoPtr LeerNodo(size_t nroNodo) = 0;

} *iArchivoArbolPtr;

#endif	/* IARCHIVOARBOL_H */
