/* 
 * File:   iBloqueRegistro.h
 * Author: Monty
 *
 * Created on 1 de abril de 2016, 00:24
 */

#ifndef IBLOQUEREGISTRO_H
#define	IBLOQUEREGISTRO_H

#include "../../../Memoria/Registro/Headers/iRegistro.h"

typedef class iBloqueRegistro
{
	public:

		virtual void AgregarRegistro(int idRegistro, iRegistroPtr *registro) = 0;
		virtual iRegistroPtr ObtenerRegistro(int idRegistro) = 0;
		virtual iRegistroPtr RemoverRegistro(int idRegistro) = 0;

		// Libera todos los registros guardados.
		virtual void Dispose() = 0;
} *iBloqueRegistroPtr;

#endif	/* IBLOQUEREGISTRO_H */

