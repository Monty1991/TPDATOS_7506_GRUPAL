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
		eTipoCampo *valores;
		size_t cantidad;

	public:
		DescriptorRegistro(eTipoCampo *valores, size_t cantidad);
		~DescriptorRegistro();

		eTipoCampo ObtenerTipoCampo(size_t nroCampo);
		size_t ObtenerCantidadCampos();

		void Dispose();

	private:

};

#endif	/* DESCRIPTORREGISTRO_H */

