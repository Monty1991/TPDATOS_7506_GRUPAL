/* 
 * File:   ComandoAlta.h
 * Author: Monty
 *
 * Created on 4 de junio de 2016, 13:53
 */

#ifndef COMANDOALTA_H
#define COMANDOALTA_H

#include "iComandoAlta.h"

class ComandoAlta: public iComandoAlta
{
	private:

		virtual ~ComandoAlta();
	public:
		ComandoAlta();

		virtual void Dispose();
		
		virtual const char *ObtenerNombre();
		virtual void ImprimirAyuda(FILE *salida);

		virtual void Ejecutar(FILE *salida, const char **listaParametros, size_t cantidad);	
};

#endif /* COMANDOALTA_H */
