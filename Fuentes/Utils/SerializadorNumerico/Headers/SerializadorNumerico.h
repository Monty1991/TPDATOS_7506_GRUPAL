/* 
 * File:   SerializadorNumerico.h
 * Author: Monty
 *
 * Created on 4 de abril de 2016, 12:40
 */

#ifndef SERIALIZADORNUMERICO_H
#define	SERIALIZADORNUMERICO_H

#include "iSerializadorNumerico.h"

class SerializadorNumerico: public iSerializadorNumerico
{
	private:

	public:
		SerializadorNumerico();
		virtual ~SerializadorNumerico();

		size_t CalcularEspacio(uNumber numero, eValueType tipo);
		size_t Serializar(char *buff, uNumber numero, eValueType tipo);

		void Dispose();
};

#endif	/* SERIALIZADORNUMERICO_H */

