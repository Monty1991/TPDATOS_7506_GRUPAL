/* 
 * File:   iHidratadorCadenaSinPrefijo.h
 * Author: Monty
 *
 * Created on 7 de abril de 2016, 19:12
 */

#ifndef IHIDRATADORCADENASINPREFIJO_H
#define	IHIDRATADORCADENASINPREFIJO_H

#include <stddef.h>

typedef class iHidratadorCadenaSinPrefijo
{
	public:

		virtual size_t Hidratar(char *buff, char *cadena, size_t largo) = 0;

		virtual void Dispose() = 0;
} *iHidratadorCadenaSinPrefijoPtr;

#endif	/* IHIDRATADORCADENASINPREFIJO_H */
