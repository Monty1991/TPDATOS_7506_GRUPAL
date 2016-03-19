/* 
 * File:   MapaDeBits.cpp
 * Author: Monty
 * 
 * Created on 19 de marzo de 2016, 01:08
 */

#include "../Headers/MapaDeBits.h"
#include <string.h>

MapaDeBits::MapaDeBits(const iBloquePtr bloque)
{
	this->bloque = bloque->Clone();
}

MapaDeBits::~MapaDeBits()
{
	if (this->bloque)
	{
		this->bloque->Dispose();
		this->bloque = NULL;
	}
}

const iBloquePtr MapaDeBits::Leer()
{
	return this->bloque;
}

size_t MapaDeBits::ObtenerTamanio()
{
	return this->bloque->ObtenerTamanioBloque();
}

bool MapaDeBits::ObtenerBit(size_t posicion)
{
	char x;
	this->bloque->LeerBloque(&x, posicion / 8, 1);
	return (x >> this->ObtenerOffsetCorrimiento(posicion)) & 1;
}

void MapaDeBits::SetearBit(size_t posicion, bool valor)
{
	char x;
	char offset = this->ObtenerOffsetCorrimiento(posicion);
	this->bloque->LeerBloque(&x, posicion / 8, 1);

	if (((x >> offset) & 1) == valor)	// si el bit ya tiene ese valor
		return;
	
	if (valor)
		x |= (1 << offset);
	else
		x &= ~ (1 << offset);

	this->bloque->EscribirBloque(&x, posicion / 8, 1);
}

void MapaDeBits::Dispose()
{
	delete this;
}

char MapaDeBits::ObtenerOffsetCorrimiento(size_t posicion)
{
	return (7 - (posicion % 8));
}
