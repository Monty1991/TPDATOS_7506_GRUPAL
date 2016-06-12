/* 
 * File:   iDescriptorRegistro.h
 * Author: Monty
 *
 * Created on 8 de junio de 2016, 17:32
 */

#ifndef IDESCRIPTORREGISTRO_H
#define IDESCRIPTORREGISTRO_H

#include <stddef.h>

enum eDescriptorCampo
{
	eDescriptorCampo_U,		// Entero Sin Signo
	eDescriptorCampo_I,		// Entero Con Signo
	eDescriptorCampo_F,		// Flotante, IEEE 754

	eDescriptorCampo_C,		// cadena ANSI, tamanio fijo
	eDescriptorCampo_CV,	// cadena ANSI, tamanio variable
};

typedef struct sDescriptorCampo
{
	eDescriptorCampo desc;
	size_t modificador;		// modificador del descriptor de campo
} *sDescriptorCampoPtr;

typedef class iDescriptorRegistro
{
	public:
		virtual void Dispose() = 0;

		virtual size_t ObtenerCantidadCampos() = 0;
		virtual const sDescriptorCampoPtr ObtenerDescriptorCampo(size_t pos) = 0;

} *iDescriptorRegistroPtr;

#endif /* IDESCRIPTORREGISTRO_H */
