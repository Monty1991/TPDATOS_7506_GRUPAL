/* 
 * File:   iSerializadorNumerico.h
 * Author: Monty
 *
 * Created on 4 de abril de 2016, 12:35
 */

#ifndef ISERIALIZADORNUMERICO_H
#define	ISERIALIZADORNUMERICO_H

#include "../../../Memoria/DataType.h"

typedef class iSerializadorNumerico
{
	public:

		// devuelve el espacio en bytes requerido para serializar
		// Si tipo no es un tipo numerico, lanza excepcion
		virtual size_t CalcularEspacio(uNumber numero, eValueType tipo) = 0;

		// devuelve la cantidad de bytes escritos en buff
		// Si tipo no es un tipo numerico, lanza excepcion
		virtual size_t Serializar(char *buff, uNumber numero, eValueType tipo) = 0;
		
		virtual void Dispose() = 0;

} *iSerializadorNumericoPtr;

#endif	/* ISERIALIZADORNUMERICO_H */
