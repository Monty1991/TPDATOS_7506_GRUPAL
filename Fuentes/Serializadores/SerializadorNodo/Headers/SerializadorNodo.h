/* 
 * File:   SerializadorNodo.h
 * Author: Monty
 *
 * Created on 10 de mayo de 2016, 12:56
 */

#ifndef SERIALIZADORNODO_H
#define SERIALIZADORNODO_H

#include "iSerializadorNodo.h"
#include "../../SerializadorNumerico/Headers/iSerializadorNumerico.h"
#include "../../SerializadorRegistro/Headers/iSerializadorRegistro.h"

class SerializadorNodo: public iSerializadorNodo
{
	private:
		iSerializadorNumericoPtr serializadorNumerico;
		iSerializadorRegistroPtr serializadorRegistro;

		virtual ~SerializadorNodo();
	public:
		SerializadorNodo();

		virtual size_t CalcularEspacioSerializacion(iNodoPtr nodo);

		virtual size_t Serializar(char *buff, iNodoPtr nodo);
		
		virtual void Dispose();
};

#endif /* SERIALIZADORNODO_H */

