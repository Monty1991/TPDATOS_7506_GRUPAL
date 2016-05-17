/* 
 * File:   HidratadorFeature.h
 * Author: Monty
 *
 * Created on 10 de mayo de 2016, 02:26
 */

#ifndef HIDRATADORFEATURE_H
#define HIDRATADORFEATURE_H

#include "iHidratadorFeature.h"
#include "../../HidratadorNumerico/Headers/iHidratadorNumerico.h"
#include "../../HidratadorCadenaANSI/Headers/iHidratadorCadenaANSI.h"
#include "../../HidratadorCadenaUNICODE/Headers/iHidratadorCadenaUNICODE.h"

class HidratadorFeature: public iHidratadorFeature
{
	private:
		iHidratadorNumericoPtr hidratadorNumerico;
		iHidratadorCadenaANSIPtr hidratadorCadenaANSI;
		iHidratadorCadenaUNICODEPtr hidratadorCadenaUNICODE;

		virtual ~HidratadorFeature();
	public:
		HidratadorFeature();

		virtual size_t Hidratar(char *buff, iFeaturePtr *feature);

		virtual void Dispose();
};

#endif /* HIDRATADORFEATURE_H */
