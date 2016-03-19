/* 
 * File:   iMapaDeBits.h
 * Author: Monty
 *
 * Created on 19 de marzo de 2016, 01:10
 */

#ifndef IMAPADEBITS_H
#define	IMAPADEBITS_H

#include <stddef.h>

typedef class iMapaDeBits
{
	public:
		virtual void Leer(char *buff) = 0;
		virtual void Escribir(const char *buff) = 0;

		virtual size_t ObtenerTamanio() = 0;

		virtual bool ObtenerBit(size_t posicion) = 0;
		virtual void SetearBit(size_t posicion, bool valor) = 0;

		virtual void Dispose() = 0;
} *iMapaDeBitsPtr;

#endif	/* IMAPADEBITS_H */
