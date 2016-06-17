/* 
 * File:   ComandoCarga.h
 * Author: Monty
 *
 * Created on 17 de junio de 2016, 15:17
 */

#ifndef COMANDOCARGA_H
#define COMANDOCARGA_H

#include "iComandoCarga.h"

class ComandoCarga: public iComandoCarga
{
	private:

		virtual ~ComandoCarga();
	public:
		ComandoCarga();

		virtual void Dispose();
		
		virtual const char *ObtenerNombre();
		virtual void ImprimirAyuda(FILE *salida);

		virtual void Ejecutar(FILE *salida, const char **listaParametros, size_t cantidad);	
};

#endif /* COMANDOCARGA_H */
