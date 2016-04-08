/* 
 * File:   iSerializadorCadenaUNICODE.h
 * Author: Monty
 *
 * Created on 7 de abril de 2016, 22:20
 */

#ifndef ISERIALIZADORCADENAUNICODE_H
#define	ISERIALIZADORCADENAUNICODE_H

#include "../../../Memoria/DataType.h"

typedef class iSerializadorCadenaUNICODE
{
	public:
		virtual size_t CalcularEspacio(sCadenaUNICODE *cadena) = 0;

		virtual size_t Serializar(char *buff, sCadenaUNICODE *cadena) = 0;

		virtual void Dispose() = 0;
} *iSerializadorCadenaUNICODEPtr;

#endif	/* ISERIALIZADORCADENAUNICODE_H */
