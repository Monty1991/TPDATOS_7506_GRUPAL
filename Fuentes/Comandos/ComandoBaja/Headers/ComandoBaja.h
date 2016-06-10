/* 
 * File:   ComandoBaja.h
 * Author: Monty
 *
 * Created on 10 de junio de 2016, 14:56
 */

#ifndef COMANDOBAJA_H
#define COMANDOBAJA_H

#include "iComandoBaja.h"

class ComandoBaja: public iComandoBaja
{
	private:

		virtual ~ComandoBaja();
	public:
		ComandoBaja();

		virtual void Dispose();
		
		virtual const char *ObtenerNombre();
		virtual void ImprimirAyuda(FILE *salida);

		virtual void Ejecutar(FILE *salida, const char **listaParametros, size_t cantidad);	
};

#endif /* COMANDOBAJA_H */
