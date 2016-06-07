/* 
 * File:   HidratadorNodoArbolPuntoOptimo.h
 * Author: Monty
 *
 * Created on 24 de mayo de 2016, 01:43
 */

#ifndef HIDRATADORNODOARBOLPUNTOOPTIMO_H
#define HIDRATADORNODOARBOLPUNTOOPTIMO_H

#include "../../HidratadorNodo/Headers/iHidratadorNodo.h"

#include "../../HidratadorNumerico/Headers/iHidratadorNumerico.h"
#include "../../HidratadorFeature/Headers/iHidratadorFeature.h"
#include "../../HidratadorRegistro/Headers/iHidratadorRegistro.h"

class HidratadorNodoArbolPuntoOptimo: public iHidratadorNodo
{
	private:
		iHidratadorNumericoPtr hidratadorNumerico;
		iHidratadorFeaturePtr hidratadorFeature;
		iHidratadorRegistroPtr hidratadorRegistro;

		virtual ~HidratadorNodoArbolPuntoOptimo();
	public:
		HidratadorNodoArbolPuntoOptimo();

		virtual size_t Hidratar(char *buff, iNodoPtr *nodo);

		virtual void Dispose();
};

#endif /* HIDRATADORNODOARBOLPUNTOOPTIMO_H */
