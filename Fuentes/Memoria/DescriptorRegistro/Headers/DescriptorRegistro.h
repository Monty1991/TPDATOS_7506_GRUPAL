/* 
 * File:   DescriptorRegistro.h
 * Author: Monty
 *
 * Created on 11 de junio de 2016, 14:28
 */

#ifndef DESCRIPTORREGISTRO_H
#define DESCRIPTORREGISTRO_H

#include "iDescriptorRegistro.h"

class DescriptorRegistro: public iDescriptorRegistro
{
	private:
		sDescriptorCampoPtr *tablaDescriptorCampo;
		size_t cantidadDescriptoresCampo;

		virtual ~DescriptorRegistro();
	public:
		DescriptorRegistro(sDescriptorCampoPtr *tablaDescriptorCampo, size_t cantidadDescriptoresCampo);

		virtual void Dispose();

		virtual size_t ObtenerCantidadCampos();
		virtual sDescriptorCampoPtr ObtenerDescriptorCampo(size_t pos);
};

#endif /* DESCRIPTORREGISTRO_H */
