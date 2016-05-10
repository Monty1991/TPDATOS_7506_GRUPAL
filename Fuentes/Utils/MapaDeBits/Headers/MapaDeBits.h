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
		
		virtual ~MapaDeBits();
	public:
		MapaDeBits(const iBloquePtr bloque);

		virtual const iBloquePtr Leer();

		virtual size_t ObtenerTamanio();

		virtual bool ObtenerBit(size_t posicion);
		virtual void SetearBit(size_t posicion, bool valor);

		virtual void Dispose();

	private:
		virtual char ObtenerOffsetCorrimiento(size_t posicion);
};

#endif	/* MAPADEBITS_H */

