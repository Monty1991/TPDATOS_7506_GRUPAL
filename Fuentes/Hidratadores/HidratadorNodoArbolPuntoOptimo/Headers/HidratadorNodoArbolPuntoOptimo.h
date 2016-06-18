/* 
 * File:   HidratadorNodoArbolPuntoOptimo.h
 * Author: Monty
 *
 * Created on 24 de mayo de 2016, 01:43
 */

#ifndef HIDRATADORNODOARBOLPUNTOOPTIMO_H
#define HIDRATADORNODOARBOLPUNTOOPTIMO_H

#include "../../HidratadorNodo/Headers/iHidratadorNodo.h"

class HidratadorNodoArbolPuntoOptimo: public iHidratadorNodo
{
	private:

		virtual ~HidratadorNodoArbolPuntoOptimo();
	public:
		HidratadorNodoArbolPuntoOptimo();

		virtual size_t Hidratar(char *buff, iNodoPtr *nodo);

		virtual void Dispose();
};

#endif /* HIDRATADORNODOARBOLPUNTOOPTIMO_H */
