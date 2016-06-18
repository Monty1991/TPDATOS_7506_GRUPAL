/* 
 * File:   SerializadorCadenaUNICODE.h
 * Author: Monty
 *
 * Created on 7 de abril de 2016, 22:21
 */

#ifndef SERIALIZADORCADENAUNICODE_H
#define	SERIALIZADORCADENAUNICODE_H

#include "iSerializadorCadenaUNICODE.h"
#include "../../SerializadorCadenaSinPrefijo/Headers/iSerializadorCadenaSinPrefijo.h"

class SerializadorCadenaUNICODE: public iSerializadorCadenaUNICODE
{
	private:
		iSerializadorCadenaSinPrefijoPtr serializadorCadenaSinPrefijo;

		virtual ~SerializadorCadenaUNICODE();
	public:
		SerializadorCadenaUNICODE();

		virtual size_t CalcularEspacio(sCadenaUNICODE *cadena);

		virtual size_t Serializar(char *buff, sCadenaUNICODE *cadena);

		virtual void Dispose();
};

#endif	/* SERIALIZADORCADENAUNICODE_H */
