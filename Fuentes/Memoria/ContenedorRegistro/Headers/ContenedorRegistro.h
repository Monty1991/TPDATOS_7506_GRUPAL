/* 
 * File:   ContenedorRegistro.h
 * Author: Monty
 *
 * Created on 18 de junio de 2016, 18:29
 */

#ifndef CONTENEDORREGISTRO_H
#define CONTENEDORREGISTRO_H

#include "iContenedorRegistro.h"

class ContenedorRegistro: public iContenedorRegistro
{
	private:
		iRegistroPtr *tablaRegistros;
		size_t tamanioTablaRegistros;
		size_t cantidadRegistros;

		virtual ~ContenedorRegistro();
	public:
		ContenedorRegistro(iRegistroPtr *listaRegistros, size_t cantidadRegistros);

		virtual void Dispose();
		
		virtual size_t ObtenerCantidadRegistros();
		virtual iRegistroPtr ObtenerRegistro(size_t pos);

		virtual void AgregarRegistro(iRegistroPtr reg);
		virtual iRegistroPtr QuitarRegistro(size_t pos);
		virtual iRegistroPtr QuitarRegistro();

		virtual size_t BuscarRegistro(iFeaturePtr clave, size_t nroCampoClave);

	private:
		virtual void RedimensionarTabla(size_t nuevoTamanio);
};

#endif /* CONTENEDORREGISTRO_H */
