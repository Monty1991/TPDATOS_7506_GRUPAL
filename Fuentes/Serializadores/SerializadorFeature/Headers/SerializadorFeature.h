/* 
 * File:   SerializadorFeature.h
 * Author: Monty
 *
 * Created on 9 de mayo de 2016, 21:50
 */

#ifndef SERIALIZADORFEATURE_H
#define SERIALIZADORFEATURE_H

#include "iSerializadorFeature.h"

class SerializadorFeature: public iSerializadorFeature
{
	private:

		virtual ~SerializadorFeature();
	public:
		SerializadorFeature();

		virtual size_t CalcularEspacio(const iFeaturePtr feature);

		virtual size_t Serializar(char *buffer, const iFeaturePtr feature);
		
		virtual void Dispose();
};

#endif /* SERIALIZADORFEATURE_H */
