/* 
 * File:   SerializadorCadenaSinPrefijo.h
 * Author: Monty
 *
 * Created on 7 de abril de 2016, 02:15
 */

#ifndef SERIALIZADORCADENASINPREFIJO_H
#define	SERIALIZADORCADENASINPREFIJO_H

#include "iSerializadorCadenaSinPrefijo.h"

class SerializadorCadenaSinPrefijo: public iSerializadorCadenaSinPrefijo
{
	private:


	public:
		SerializadorCadenaSinPrefijo();
		virtual ~SerializadorCadenaSinPrefijo();

		size_t CalcularEspacio(char *cadena, size_t tamanio);
		size_t Serializar(char *buff, char *cadena, size_t tamanio);

		virtual void Dispose();

	private:
};

#endif	/* SERIALIZADORCADENASINPREFIJO_H */

