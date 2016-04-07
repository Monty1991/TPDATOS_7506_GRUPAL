/* 
 * File:   HidratadorCadenaSinPrefijo.h
 * Author: Monty
 *
 * Created on 7 de abril de 2016, 19:14
 */

#ifndef HIDRATADORCADENASINPREFIJO_H
#define	HIDRATADORCADENASINPREFIJO_H

#include "iHidratadorCadenaSinPrefijo.h"

class HidratadorCadenaSinPrefijo: public iHidratadorCadenaSinPrefijo
{
	private:

	public:
		HidratadorCadenaSinPrefijo();
		virtual ~HidratadorCadenaSinPrefijo();

		size_t Hidratar(char *buff, char *cadena, size_t largo);

		virtual void Dispose();
};

#endif	/* HIDRATADORCADENASINPREFIJO_H */

