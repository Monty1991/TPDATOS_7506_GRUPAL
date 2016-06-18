/* 
 * File:   iArbol.h
 * Author: Monty
 *
 * Created on 21 de marzo de 2016, 06:04
 */

#ifndef IARBOL_H
#define	IARBOL_H

#include "../../../Memoria/Feature/Headers/iFeature.h"

typedef class iArbol
{
	public:
		// Guarda un valor con la clave. Si ya existe la clave, se
		// devuelve a traves del parametro valor.
		// Devuelve la nueva raiz del arbol
		virtual iArbol *Add(iFeaturePtr clave, iObjectPtr *valor) = 0;
		virtual iFeaturePtr GetKey() = 0;
		virtual iObjectPtr GetValue(iFeaturePtr clave) = 0;

		// Remueve el valor almacenado bajo la clave key.
		// En valor se devuelve el dato guardado, o NULL si no existe
		// Devuelve la nueva raiz del arbol
		virtual iArbol *Remove(iFeaturePtr clave, iObjectPtr *valor) = 0;

		// destruye la totalidad del arbol, incluyendo los datos.
		virtual void Dispose() = 0;

} *iArbolPtr;

#endif	/* IARBOL_H */
