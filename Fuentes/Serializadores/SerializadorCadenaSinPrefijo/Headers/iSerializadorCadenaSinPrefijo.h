/* 
 * File:   iSerializadorCadenaSinPrefijo.h
 * Author: Monty
 *
 * Created on 7 de abril de 2016, 02:08
 */

#ifndef ISERIALIZADORCADENASINPREFIJO_H
#define	ISERIALIZADORCADENASINPREFIJO_H

#include <stddef.h>

typedef class iSerializadorCadenaSinPrefijo
{
	public:
		
		// devuelve el espacio en bytes requerido para serializar
		virtual size_t CalcularEspacio(char *cadena, size_t tamanio) = 0;

		// devuelve la cantidad de bytes escritos en buff
		virtual size_t Serializar(char *buff, char *cadena, size_t tamanio) = 0;

		virtual void Dispose() = 0;
} *iSerializadorCadenaSinPrefijoPtr;

#endif	/* ISERIALIZADORCADENASINPREFIJO_H */
