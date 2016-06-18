/* 
 * File:   HidratadorCadenaANSI.h
 * Author: Monty
 *
 * Created on 7 de abril de 2016, 21:40
 */

#ifndef HIDRATADORCADENAANSI_H
#define	HIDRATADORCADENAANSI_H

#include "iHidratadorCadenaANSI.h"
#include "../../HidratadorCadenaSinPrefijo/Headers/iHidratadorCadenaSinPrefijo.h"

class HidratadorCadenaANSI: public iHidratadorCadenaANSI
{
	private:
		iHidratadorCadenaSinPrefijoPtr hidratadorCadenaSinPrefijo;

	public:
		HidratadorCadenaANSI();
		virtual ~HidratadorCadenaANSI();
		
		virtual size_t Hidratar(char *buff, sCadenaANSI *cadena);

		virtual void Dispose();		
};

#endif	/* HIDRATADORCADENAANSI_H */
