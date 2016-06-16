/* 
 * File:   EspacioMetrico.h
 * Author: Monty
 *
 * Created on 1 de junio de 2016, 00:52
 */

#ifndef ESPACIOMETRICO_H
#define ESPACIOMETRICO_H

#include "iEspacioMetrico.h"
#include "../../../Memoria/Object/Headers/Object.h"

class EspacioMetrico: public iEspacioMetrico, public Object
{
	private:
		
		virtual ~EspacioMetrico();
	public:	
		EspacioMetrico();

		virtual iEspacioMetrico *Copiar();
		virtual iEspacioMetrico *Clone();
		
		virtual void Dispose();

		virtual double CalcularDistancia(size_t clave2, size_t clave1);
		virtual double CalcularDistancia(sCadenaANSI *clave1, sCadenaANSI *clave2);

		virtual size_t CalcularPivote(size_t *listaClaves, size_t cantidadClaves);
		virtual sCadenaANSI *CalcularPivote(sCadenaANSI **listaClaves, size_t cantidadClaves);

	private:
		virtual void SepararCoordenadas(size_t clave, size_t *coord1, size_t *coord2);
		virtual void SepararCoordenadas(sCadenaANSI *clave, sCadenaANSI **coord1, sCadenaANSI **coord2);
		virtual size_t JuntarCoordenadas(size_t coord1, size_t coord2);
		virtual sCadenaANSI *JuntarCoordenadas(sCadenaANSI *coord1, sCadenaANSI *coord2);
		virtual size_t DistanciaLevenshtein(sCadenaANSI *coord1, sCadenaANSI *coord2);
};

#endif /* ESPACIOMETRICO_H */
