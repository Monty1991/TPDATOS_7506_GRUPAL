/* 
 * File:   iComando.h
 * Author: Monty
 *
 * Created on 4 de junio de 2016, 13:21
 */

#ifndef ICOMANDO_H
#define ICOMANDO_H

#include <stdio.h>

typedef class iComando
{
	public:
		virtual void Dispose() = 0;
		
		virtual const char *ObtenerNombre() = 0;
		virtual void ImprimirAyuda(FILE *salida) = 0;

		virtual void Ejecutar(FILE *salida, const char **listaParametros, size_t cantidad) = 0;
} *iComandoPtr;

#endif /* ICOMANDO_H */
