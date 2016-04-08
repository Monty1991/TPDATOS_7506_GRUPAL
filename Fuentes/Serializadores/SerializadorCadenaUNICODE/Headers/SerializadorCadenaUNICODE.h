/* 
 * File:   SerializadorCadenaUNICODE.h
 * Author: Monty
 *
 * Created on 7 de abril de 2016, 22:21
 */

#ifndef SERIALIZADORCADENAUNICODE_H
#define	SERIALIZADORCADENAUNICODE_H

#include "iSerializadorCadenaUNICODE.h"
#include "../../SerializadorNumerico/Headers/iSerializadorNumerico.h"
#include "../../SerializadorCadenaSinPrefijo/Headers/iSerializadorCadenaSinPrefijo.h"

class SerializadorCadenaUNICODE: public iSerializadorCadenaUNICODE
{
	private:
		iSerializadorNumericoPtr serializadorNumerico;
		iSerializadorCadenaSinPrefijoPtr serializadorCadenaSinPrefijo;

	public:
		SerializadorCadenaUNICODE();
		virtual ~SerializadorCadenaUNICODE();

		virtual size_t CalcularEspacio(sCadenaUNICODE *cadena);

		virtual size_t Serializar(char *buff, sCadenaUNICODE *cadena);

		virtual void Dispose();
};

#endif	/* SERIALIZADORCADENAUNICODE_H */
