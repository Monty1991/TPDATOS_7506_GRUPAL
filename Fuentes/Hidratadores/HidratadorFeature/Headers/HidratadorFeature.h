/* 
 * File:   HidratadorFeature.h
 * Author: Monty
 *
 * Created on 10 de mayo de 2016, 02:26
 */

#ifndef HIDRATADORFEATURE_H
#define HIDRATADORFEATURE_H

#include "iHidratadorFeature.h"

class HidratadorFeature: public iHidratadorFeature
{
	private:

		virtual ~HidratadorFeature();
	public:
		HidratadorFeature();

		virtual size_t Hidratar(char *buff, iFeaturePtr *feature);

		virtual void Dispose();
};

#endif /* HIDRATADORFEATURE_H */
