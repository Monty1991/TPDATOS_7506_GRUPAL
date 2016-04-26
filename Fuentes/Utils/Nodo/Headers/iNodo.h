/* 
 * File:   iNodo.h
 * Author: Monty
 *
 * Created on 25 de abril de 2016, 22:43
 */

#ifndef INODO_H
#define	INODO_H

#include "../../../Memoria/Registro/Headers/iRegistro.h"

typedef class iNodo
{
	public:
		virtual void Dispose() = 0;

		virtual size_t ObtenerAltura() = 0;
		virtual void CambiarAltura(size_t altura) = 0;

		virtual size_t ObtenerCantidadRegistros() = 0;
		virtual iRegistroPtr ObtenerRegistro(size_t pos) = 0;

		virtual iRegistroPtr AgregarRegistro(iRegistroPtr reg) = 0;
		virtual iRegistroPtr QuitarRegistro(size_t pos) = 0;
} *iNodoPtr;

#endif	/* INODO_H */
