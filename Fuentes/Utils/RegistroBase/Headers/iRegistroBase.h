/* 
 * File:   iRegistroBase.h
 * Author: Monty
 *
 * Created on 17 de marzo de 2016, 12:32
 */

#ifndef IREGISTRO_H
#define	IREGISTRO_H

#include "../../../Memoria/Datos.h"

typedef class iRegistroBase
{
	public:

		// lanza excepcion si se excede el numero de campos
		virtual uValue ObtenerCampo(size_t nroCampo) = 0;

		virtual void ModificarCampo(size_t nroCampo, uValue valor) = 0;

		virtual void Disponer() = 0;
} *iRegistroBasePtr;

#endif	/* IREGISTRO_H */
