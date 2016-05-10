/* 
 * File:   iHidratadorFeature.h
 * Author: Monty
 *
 * Created on 10 de mayo de 2016, 02:21
 */

#ifndef IHIDRATADORFEATURE_H
#define IHIDRATADORFEATURE_H

#include "../../../Memoria/Feature/Headers/iFeature.h"

typedef class iHidratadorFeature
{
	public:
		virtual size_t Hidratar(char *buff, iFeaturePtr *feature, eValueType tipo) = 0;

		virtual void Dispose() = 0;

} *iHidratadorFeaturePtr;

#endif /* IHIDRATADORFEATURE_H */
