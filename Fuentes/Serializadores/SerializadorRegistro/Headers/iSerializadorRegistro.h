/* 
 * File:   iSerializadorRegistro.h
 * Author: Monty
 *
 * Created on 10 de mayo de 2016, 03:42
 */

#ifndef ISERIALIZADORREGISTRO_H
#define ISERIALIZADORREGISTRO_H

#include "../../../Memoria/Registro/Headers/iRegistro.h"

typedef class iSerializadorRegistro
{
	public:
		virtual size_t CalcularEspacio(const iRegistroPtr registro) = 0;

		virtual size_t Serializar(char *buffer, const iRegistroPtr registro) = 0;

		virtual void Dispose() = 0;
} *iSerializadorRegistroPtr;

#endif /* ISERIALIZADORREGISTRO_H */

