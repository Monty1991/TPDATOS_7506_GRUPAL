/* 
 * File:   SerializadorFeature.h
 * Author: Monty
 *
 * Created on 9 de mayo de 2016, 21:50
 */

#ifndef SERIALIZADORFEATURE_H
#define SERIALIZADORFEATURE_H

#include "iSerializadorFeature.h"
#include "../../SerializadorNumerico/Headers/SerializadorNumerico.h"
#include "../../SerializadorCadenaANSI/Headers/iSerializadorCadenaANSI.h"
#include "../../SerializadorCadenaUNICODE/Headers/iSerializadorCadenaUNICODE.h"

class SerializadorFeature: public iSerializadorFeature
{
	private:
		iSerializadorCadenaANSIPtr serializadorCadenaANSI;
		iSerializadorCadenaUNICODEPtr serializadorCadenaUNICODE;
		iSerializadorNumericoPtr serializadorNumerico;

	public:
		SerializadorFeature();
		virtual ~SerializadorFeature();

		virtual size_t CalcularEspacio(const iFeaturePtr feature);

		virtual size_t Serializar(char *buffer, const iFeaturePtr feature);
		
		virtual void Dispose();
};

#endif /* SERIALIZADORFEATURE_H */
