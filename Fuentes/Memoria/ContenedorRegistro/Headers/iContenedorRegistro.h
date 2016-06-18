/* 
 * File:   iContenedorRegistro.h
 * Author: Monty
 *
 * Created on 18 de junio de 2016, 18:26
 */

#ifndef ICONTENEDORREGISTRO_H
#define ICONTENEDORREGISTRO_H

#include "../../Registro/Headers/iRegistro.h"

typedef class iContenedorRegistro
{
	public:
		virtual void Dispose() = 0;

		virtual size_t ObtenerCantidadRegistros() = 0;
		virtual iRegistroPtr ObtenerRegistro(size_t pos) = 0;

		virtual void AgregarRegistro(iRegistroPtr reg) = 0;
		virtual iRegistroPtr QuitarRegistro(size_t pos) = 0;
		virtual iRegistroPtr QuitarRegistro() = 0;

		virtual size_t BuscarRegistro(iFeaturePtr clave, size_t nroCampoClave) = 0;

} *iContenedorRegistroPtr;

#endif /* ICONTENEDORREGISTRO_H */
