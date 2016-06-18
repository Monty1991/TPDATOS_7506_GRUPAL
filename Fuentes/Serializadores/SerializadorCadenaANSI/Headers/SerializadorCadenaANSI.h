/* 
 * File:   SerializadorCadenaANSI.h
 * Author: Monty
 *
 * Created on 7 de abril de 2016, 21:19
 */

#ifndef SERIALIZADORCADENAANSI_H
#define	SERIALIZADORCADENAANSI_H

#include "iSerializadorCadenaANSI.h"
#include "../../SerializadorCadenaSinPrefijo/Headers/iSerializadorCadenaSinPrefijo.h"

class SerializadorCadenaANSI: public iSerializadorCadenaANSI
{
	private:
		iSerializadorCadenaSinPrefijoPtr serializadorCadenaSinPrefijo;

		virtual ~SerializadorCadenaANSI();
	public:
		SerializadorCadenaANSI();
	
		virtual size_t CalcularEspacio(sCadenaANSI *cadena);

		virtual size_t Serializar(char *buff, sCadenaANSI *cadena);

		virtual void Dispose();
};

#endif	/* SERIALIZADORCADENAANSI_H */
