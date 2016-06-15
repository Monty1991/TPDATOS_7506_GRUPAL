/* 
 * File:   MapaDeBits.cpp
 * Author: Monty
 * 
 * Created on 19 de marzo de 2016, 01:08
 */

#include "../Headers/MapaDeBits.h"
#include <string.h>
#include "../../../Sistema/Sistema/Headers/Sistema.h"

MapaDeBits::MapaDeBits(const iBloquePtr bloque): bloque(bloque)
{
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
	if (!this->bloque)
		return 0;

	return this->bloque->ObtenerTamanioBloque();
}

bool MapaDeBits::ObtenerBit(size_t posicion)
{
	char x;
	Sistema_Execute(this->bloque->LeerBloque(&x, posicion / 8, 1););
	return (x >> this->ObtenerOffsetCorrimiento(posicion)) & 1;
}

void MapaDeBits::SetearBit(size_t posicion, bool valor)
{
	char x;
	char offset = this->ObtenerOffsetCorrimiento(posicion);
	Sistema_Execute(this->bloque->LeerBloque(&x, posicion / 8, 1););

	if (((x >> offset) & 1) == valor)	// si el bit ya tiene ese valor
		return;
	
	if (valor)
		x |= (1 << offset);
	else
		x &= ~ (1 << offset);

	Sistema_Execute(this->bloque->EscribirBloque(&x, posicion / 8, 1););
}

void MapaDeBits::Dispose()
{
	delete this;
}

char MapaDeBits::ObtenerOffsetCorrimiento(size_t posicion)
{
	return (7 - (posicion % 8));
}
