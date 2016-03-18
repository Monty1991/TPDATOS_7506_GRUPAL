/* 
 * File:   RegistroBase.h
 * Author: Monty
 *
 * Created on 17 de marzo de 2016, 12:37
 */

#ifndef REGISTRO_H
#define	REGISTRO_H

#include "iRegistroBase.h"

typedef class RegistroBase: public iRegistroBase
{
	private:
		uValue *campoValores;
		int cantidadCampos;

	public:
		RegistroBase(size_t cantidadCampos);

		~RegistroBase();

		uValue ObtenerCampo(size_t nroCampo);

		void ModificarCampo(size_t nroCampo, uValue valor);

		void Disponer();

	private:

} *RegistroBasePtr;

#endif	/* REGISTRO_H */

