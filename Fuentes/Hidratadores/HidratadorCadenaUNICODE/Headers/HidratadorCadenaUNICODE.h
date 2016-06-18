/* 
 * File:   HidratadorCadenaUNICODE.h
 * Author: Monty
 *
 * Created on 7 de abril de 2016, 22:09
 */

#ifndef HIDRATADORCADENAUNICODE_H
#define	HIDRATADORCADENAUNICODE_H

#include "iHidratadorCadenaUNICODE.h"
#include "../../HidratadorCadenaSinPrefijo/Headers/iHidratadorCadenaSinPrefijo.h"

class HidratadorCadenaUNICODE: public iHidratadorCadenaUNICODE
{
	private:
		iHidratadorCadenaSinPrefijoPtr hidratadorCadenaSinPrefijo;

	public:
		HidratadorCadenaUNICODE();
		virtual ~HidratadorCadenaUNICODE();

		virtual size_t Hidratar(char *buff, sCadenaUNICODE *cadena);
		
		virtual void Dispose();
};

#endif	/* HIDRATADORCADENAUNICODE_H */
