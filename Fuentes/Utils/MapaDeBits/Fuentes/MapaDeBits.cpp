/* 
 * File:   MapaDeBits.cpp
 * Author: Monty
 * 
 * Created on 19 de marzo de 2016, 01:08
 */

#include "../Headers/MapaDeBits.h"
#include <string.h>

MapaDeBits::MapaDeBits(const char *buff, size_t tamanioMapa)
{
	this->tamanioMapa = tamanioMapa;
	this->buff = new char[this->tamanioMapa];
	this->Escribir(buff);
}

MapaDeBits::~MapaDeBits()
{
	if (this->buff)
	{
		delete this->buff;
		this->buff = NULL;
	}
}

void MapaDeBits::Leer(char *buff)
{
	memcpy(buff, this->buff, this->tamanioMapa);
}

void MapaDeBits::Escribir(const char *buff)
{
	memcpy(this->buff, buff, this->tamanioMapa);	
}

size_t MapaDeBits::ObtenerTamanio()
{
	return this->tamanioMapa;
}

bool MapaDeBits::ObtenerBit(size_t posicion)
{
	return ((this->buff[(posicion - 1 ) / 8]) >> ((posicion - 1) % 8)) & 1;
}

void MapaDeBits::SetearBit(size_t posicion, bool valor)
{
	if (valor)
		this->buff[(posicion - 1) / 8] |= (1 << ((posicion - 1) % 8));
	else
		this->buff[(posicion - 1) / 8] &= ~(1 << ((posicion - 1) % 8));
}

void MapaDeBits::Dispose()
{
	delete this;
}
