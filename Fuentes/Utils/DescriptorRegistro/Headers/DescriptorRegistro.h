/* 
 * File:   DescriptorRegistro.h
 * Author: Monty
 *
 * Created on 18 de marzo de 2016, 03:47
 */

#ifndef DESCRIPTORREGISTRO_H
#define	DESCRIPTORREGISTRO_H

#include "iDescriptorRegistro.h"

class DescriptorRegistro: public iDescriptorRegistro
{
	private:
		eValueType *valores;
		int cantidad;

	public:
		DescriptorRegistro(eValueType *valores, int cantidad);
		~DescriptorRegistro();

		eValueType ObtenerValor(int posicion);
		int ObtenerCantidadCampos();

		void Dispose();

	private:

};

#endif	/* DESCRIPTORREGISTRO_H */

