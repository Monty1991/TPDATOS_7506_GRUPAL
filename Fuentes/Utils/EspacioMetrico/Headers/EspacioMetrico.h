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

		virtual float CalcularDistancia(size_t clave1, size_t clave2);

		virtual size_t CalcularPivote(size_t *listaClaves, size_t cantidadClaves);

	private:
		virtual void SepararCoordenadas(size_t clave, size_t *coord1, size_t *coord2);
		virtual size_t JuntarCoordenadas(size_t coord1, size_t coord2);
};

#endif /* ESPACIOMETRICO_H */
