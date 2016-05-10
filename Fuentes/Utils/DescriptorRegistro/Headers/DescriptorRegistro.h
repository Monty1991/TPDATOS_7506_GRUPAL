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
		eValueType *tablaValores;
		size_t cantidadCampos;

		virtual ~DescriptorRegistro();
	public:
		DescriptorRegistro(eValueType *valores, size_t cantidadCampos);

		virtual eValueType ObtenerTipoCampo(size_t nroCampo);
		virtual size_t ObtenerCantidadCampos();

		virtual void Dispose();

	private:

};

#endif	/* DESCRIPTORREGISTRO_H */
