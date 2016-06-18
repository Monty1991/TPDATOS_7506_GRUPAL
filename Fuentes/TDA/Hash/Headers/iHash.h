/* 
 * File:   iHash.h
 * Author: Monty
 *
 * Created on 18 de junio de 2016, 17:01
 */

#ifndef IHASH_H
#define IHASH_H

#include "../../../Memoria/Feature/Headers/iFeature.h"

typedef class iHash
{
	public:
		virtual void Dispose() = 0;

		virtual bool Guardar(iObjectPtr obj, iFeaturePtr clave) = 0;
		virtual iObjectPtr Obtener(iFeaturePtr clave) = 0;
		virtual iObjectPtr Borrar(iFeaturePtr clave) = 0;
		virtual size_t ObtenerCantidad() = 0;

} *iHashPtr;

#endif /* IHASH_H */
