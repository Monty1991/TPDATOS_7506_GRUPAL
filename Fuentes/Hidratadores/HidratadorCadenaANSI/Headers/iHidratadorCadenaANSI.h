/* 
 * File:   iHidratadorCadenaANSI.h
 * Author: Monty
 *
 * Created on 7 de abril de 2016, 21:38
 */

#ifndef IHIDRATADORCADENAANSI_H
#define	IHIDRATADORCADENAANSI_H

#include "../../../Memoria/DataType.h"

typedef class iHidratadorCadenaANSI
{
	public:
		virtual size_t Hidratar(char *buff, sCadenaANSI *cadena) = 0;
		
		virtual void Dispose() = 0;

} *iHidratadorCadenaANSIPtr;

#endif	/* IHIDRATADORCADENAANSI_H */
