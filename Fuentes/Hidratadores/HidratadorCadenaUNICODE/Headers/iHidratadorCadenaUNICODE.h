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
		virtual size_t Hidratar(char *buff, sCadenaUNICODE *cadena) = 0;

		virtual void Dispose() = 0;
} *iHidratadorCadenaUNICODEPtr;

#endif	/* IHIDRATADORCADENAUNICODE_H */
