/* 
 * File:   iSerializadorFeature.h
 * Author: Monty
 *
 * Created on 9 de mayo de 2016, 21:51
 */

#ifndef ISERIALIZADORFEATURE_H
#define ISERIALIZADORFEATURE_H

#include "../../../Memoria/Feature/Headers/iFeature.h"

typedef class iSerializadorFeature
{
	public:
		virtual size_t CalcularEspacio(const iFeaturePtr feature) = 0;

		virtual size_t Serializar(char *buffer, const iFeaturePtr feature) = 0;

		virtual void Dispose() = 0;

} *iSerializadorFeaturePtr;

#endif /* ISERIALIZADORFEATURE_H */
