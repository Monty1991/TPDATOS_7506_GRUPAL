/* 
 * File:   MapaDeBits.h
 * Author: Monty
 *
 * Created on 19 de marzo de 2016, 01:08
 */

#ifndef MAPADEBITS_H
#define	MAPADEBITS_H

#include "../../Bloque/Headers/iBloque.h"
#include "iMapaDeBits.h"

class MapaDeBits: public iMapaDeBits
{
	private:
		iBloquePtr bloque;
		
	public:
		MapaDeBits(const iBloquePtr bloque);
		~MapaDeBits();

		const iBloquePtr Leer();

		size_t ObtenerTamanio();

		bool ObtenerBit(size_t posicion);
		void SetearBit(size_t posicion, bool valor);

		void Dispose();

	private:
		char ObtenerOffsetCorrimiento(size_t posicion);
};

#endif	/* MAPADEBITS_H */

