/* 
 * File:   HidratadorRegistro.h
 * Author: Monty
 *
 * Created on 10 de mayo de 2016, 04:35
 */

#ifndef HIDRATADORREGISTRO_H
#define HIDRATADORREGISTRO_H

#include "iHidratadorRegistro.h"
#include "../../HidratadorFeature/Headers/iHidratadorFeature.h"

class HidratadorRegistro: public iHidratadorRegistro
{
	private:
		iHidratadorFeaturePtr hidratadorFeature;

		virtual ~HidratadorRegistro();
	public:
		HidratadorRegistro();

		virtual size_t Hidratar(char *buff, iRegistroPtr *registro);

		virtual void Dispose();
};

#endif /* HIDRATADORREGISTRO_H */
