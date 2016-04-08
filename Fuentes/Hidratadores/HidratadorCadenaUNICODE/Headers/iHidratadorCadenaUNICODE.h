/* 
 * File:   iHidratadorCadenaUNICODE.h
 * Author: Monty
 *
 * Created on 7 de abril de 2016, 22:07
 */

#ifndef IHIDRATADORCADENAUNICODE_H
#define	IHIDRATADORCADENAUNICODE_H

#include "../../../Memoria/DataType.h"

typedef class iHidratadorCadenaUNICODE
{
	public:
		
		size_t Hidratar(char *buff, sCadenaUNICODE **cadena);

		virtual void Dispose() = 0;
} *iHidratadorCadenaUNICODEPtr;

#endif	/* IHIDRATADORCADENAUNICODE_H */
