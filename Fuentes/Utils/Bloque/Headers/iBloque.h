/* 
 * File:   iBloque.h
 * Author: Monty
 *
 * Created on 19 de marzo de 2016, 00:25
 */

#ifndef IBLOQUE_H
#define	IBLOQUE_H

#include <stddef.h>
#include "../../../Memoria/Object/Headers/iObject.h"

typedef class iBloque: public iObject
{
	public:
		virtual iBloque *Copiar() = 0;
		virtual iBloque *Clone() = 0;

		virtual size_t ObtenerTamanioBloque() = 0;

		virtual const char *ObtenerContenido() = 0;
		// si offset + length > ObtenerTamanioBloque() -> tira excepcion
		// offset siempre refere a la posicion relativa dentro del bloque
		virtual void LeerBloque(char *buff, size_t offset, size_t length) = 0;
		virtual void EscribirBloque(const char *buff, size_t offset, size_t length) = 0;

		virtual void Dispose() = 0;

} *iBloquePtr;

#endif	/* IBLOQUE_H */
