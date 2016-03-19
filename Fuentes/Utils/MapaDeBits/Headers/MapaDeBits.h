/* 
 * File:   MapaDeBits.h
 * Author: Monty
 *
 * Created on 19 de marzo de 2016, 01:08
 */

#ifndef MAPADEBITS_H
#define	MAPADEBITS_H

#include "iMapaDeBits.h"

class MapaDeBits: public iMapaDeBits
{
	private:
		char *buff;
		size_t tamanioMapa;
		
	public:
		MapaDeBits(const char *buff, size_t tamanioMapa);
		~MapaDeBits();

		void Leer(char *buff);
		void Escribir(const char *buff);

		size_t ObtenerTamanio();

		bool ObtenerBit(size_t posicion);
		void SetearBit(size_t posicion, bool valor);

		void Dispose();
	private:

};

#endif	/* MAPADEBITS_H */

