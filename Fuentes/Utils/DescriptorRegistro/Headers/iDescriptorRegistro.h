/* 
 * File:   iDescriptorRegistro.h
 * Author: Monty
 *
 * Created on 18 de marzo de 2016, 03:48
 */

#ifndef IDESCRIPTORREGISTRO_H
#define	IDESCRIPTORREGISTRO_H

#include "../../../Memoria/Datos.h"

typedef class iDescriptorRegistro
{
	public:
		virtual eValueType ObtenerValor(int posicion) = 0;
		virtual int ObtenerCantidadCampos() = 0;

		virtual void Dispose() = 0;
} *iDescriptorRegistroPtr;

#endif	/* IDESCRIPTORREGISTRO_H */
