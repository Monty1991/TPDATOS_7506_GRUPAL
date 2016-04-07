/* 
 * File:   iHidratadorNumerico.h
 * Author: Monty
 *
 * Created on 4 de abril de 2016, 23:56
 */

#ifndef IHIDRATADORNUMERICO_H
#define	IHIDRATADORNUMERICO_H

#include "../../../Memoria/DataType.h"

typedef class iHidratadorNumerico
{
	public:

		// devuelve la cantidad de bytes leidos
		// Si tipo no es un tipo numerico, lanza excepcion
		virtual size_t Hidratar(const char *buff, uNumber *numero, eValueType tipo) = 0;
		
		virtual void Dispose() = 0;

} *iHidratadorNumericoPtr;

#endif	/* IHIDRATADORNUMERICO_H */

