/* 
 * File:   iSerializadorCadenaANSI.h
 * Author: Monty
 *
 * Created on 7 de abril de 2016, 21:19
 */

#ifndef ISERIALIZADORCADENAANSI_H
#define	ISERIALIZADORCADENAANSI_H

#include "../../../Memoria/DataType.h"

typedef class iSerializadorCadenaANSI
{
	public:
		
		virtual size_t CalcularEspacio(sCadenaANSI *cadena) = 0;

		virtual size_t Serializar(char *buff, sCadenaANSI *cadena) = 0;

		virtual void Dispose() = 0;
} *iSerializadorCadenaANSIPtr;

#endif	/* ISERIALIZADORCADENAANSI_H */

