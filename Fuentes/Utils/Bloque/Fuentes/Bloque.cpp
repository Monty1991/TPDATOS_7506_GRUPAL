/* 
 * File:   Bloque.cpp
 * Author: Monty
 * 
 * Created on 19 de marzo de 2016, 00:16
 */

#include "../Headers/Bloque.h"
#include <string.h>

Bloque::Bloque(const char *buffer, size_t tamanioBloque)
{
	this->tamanioBloque = tamanioBloque;
	this->buff = new char[this->tamanioBloque];
	this->LeerBloque(buffer);

	this->BorrarBitModificacion();
}

Bloque::~Bloque()
{
	if (this->buff)
	{
		delete this->buff;
		this->buff = NULL;
	}
}

bool Bloque::FueModificado()
{
	return this->modificado;
}

void Bloque::BorrarBitModificacion()
{
	this->modificado = false;
}

void Bloque::LeerBloque(const char *buff)
{
	memcpy(this->buff, buff, this->tamanioBloque);	
}

void Bloque::EscribirBloque(char *buff)
{
	memcpy(this->buff, buff, this->tamanioBloque);
	this->modificado = true;
}

void Bloque::Dispose()
{
	delete this;
}
