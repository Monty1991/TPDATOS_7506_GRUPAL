/* 
 * File:   ComandoBuscar.h
 * Author: Monty
 *
 * Created on 10 de junio de 2016, 14:43
 */

#ifndef COMANDOBUSCAR_H
#define COMANDOBUSCAR_H


#include "iComandoBuscar.h"

class ComandoBuscar: public iComandoBuscar
{
	private:

		virtual ~ComandoBuscar();
	public:
		ComandoBuscar();

		virtual void Dispose();
		
		virtual const char *ObtenerNombre();
		virtual void ImprimirAyuda(FILE *salida);

		virtual void Ejecutar(FILE *salida, const char **listaParametros, size_t cantidad);	
};

#endif /* COMANDOBUSCAR_H */
