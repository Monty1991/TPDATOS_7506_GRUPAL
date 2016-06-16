/* 
 * File:   iEspacioMetrico.h
 * Author: Monty
 *
 * Created on 1 de junio de 2016, 00:48
 */

#ifndef IESPACIOMETRICO_H
#define IESPACIOMETRICO_H

#include "../../../Memoria/DataType.h"

typedef class iEspacioMetrico: public iObject
{
	public:
		virtual iEspacioMetrico *Copiar() = 0;
		virtual iEspacioMetrico *Clone() = 0;
		
		virtual void Dispose() = 0;

		virtual double CalcularDistancia(size_t clave2, size_t clave1) = 0;
		virtual double CalcularDistancia(sCadenaANSI *clave1, sCadenaANSI *clave2) = 0;

		virtual size_t CalcularPivote(size_t *listaClaves, size_t cantidadClaves) = 0;
		virtual sCadenaANSI *CalcularPivote(sCadenaANSI **listaClaves, size_t cantidadClaves) = 0;
		
} *iEspacioMetricoPtr;

#endif /* IESPACIOMETRICO_H */
