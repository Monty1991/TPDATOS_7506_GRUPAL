/* 
 * File:   iDescriptorRegistro.h
 * Author: Monty
 *
 * Created on 18 de marzo de 2016, 03:48
 */

#ifndef IDESCRIPTORREGISTRO_H
#define	IDESCRIPTORREGISTRO_H

#include "../../../Memoria/DataType.h"

typedef class iDescriptorRegistro
{
	public:
		virtual eValueType ObtenerTipoCampo(size_t nroCampo) = 0;
		virtual size_t ObtenerCantidadCampos() = 0;

		virtual void Dispose() = 0;
} *iDescriptorRegistroPtr;

#endif	/* IDESCRIPTORREGISTRO_H */
