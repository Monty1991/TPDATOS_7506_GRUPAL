/* 
 * File:   iArchivoBloque.h
 * Author: Monty
 *
 * Created on 17 de marzo de 2016, 02:12
 */

#ifndef IARCHIVOBLOQUE_H
#define	IARCHIVOBLOQUE_H

#include "../../../Utils/Bloque/Headers/iBloque.h"

typedef class iArchivoBloque
{
	public:
		virtual size_t ObtenerTamanioBloque() = 0;

		virtual iBloquePtr LeerBloque(size_t nroBloque) = 0;
		virtual void EscribirBloque(size_t nroBloque, iBloquePtr bloque) = 0;
		
		virtual void Close() = 0;
} *iArchivoBloquePtr;

#endif	/* IARCHIVOBLOQUE_H */
