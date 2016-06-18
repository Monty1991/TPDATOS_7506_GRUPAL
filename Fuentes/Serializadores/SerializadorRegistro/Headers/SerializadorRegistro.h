/* 
 * File:   SerializadorRegistro.h
 * Author: Monty
 *
 * Created on 10 de mayo de 2016, 03:41
 */

#ifndef SERIALIZADORREGISTRO_H
#define SERIALIZADORREGISTRO_H

#include "iSerializadorRegistro.h"
#include "../../SerializadorFeature/Headers/iSerializadorFeature.h"

class SerializadorRegistro: public iSerializadorRegistro
{
	private:
		iSerializadorFeaturePtr serializadorFeature;

		virtual ~SerializadorRegistro();
	public:
		SerializadorRegistro();

		virtual size_t CalcularEspacio(const iRegistroPtr registro);

		virtual size_t Serializar(char *buffer, const iRegistroPtr registro);

		virtual void Dispose();
};

#endif /* SERIALIZADORREGISTRO_H */
