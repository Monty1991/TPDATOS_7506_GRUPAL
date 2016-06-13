/* 
 * File:   ComandoModificacion.h
 * Author: Monty
 *
 * Created on 13 de junio de 2016, 14:56
 */

#ifndef COMANDOMODIFICACION_H
#define COMANDOMODIFICACION_H

#include "iComandoModificacion.h"

class ComandoModificacion: public iComandoModificacion
{
	private:

		virtual ~ComandoModificacion();
	public:
		ComandoModificacion();

		virtual void Dispose();
		
		virtual const char *ObtenerNombre();
		virtual void ImprimirAyuda(FILE *salida);

		virtual void Ejecutar(FILE *salida, const char **listaParametros, size_t cantidad);	
};

#endif /* COMANDOMODIFICACION_H */
