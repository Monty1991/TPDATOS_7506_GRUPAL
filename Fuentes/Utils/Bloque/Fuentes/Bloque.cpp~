/* 
 * File:   Bloque.cpp
 * Author: Monty
 * 
 * Created on 19 de marzo de 2016, 00:16
 */

#include "../Headers/Bloque.h"
#include <string.h>
#include "../../StringUtils/Headers/StringUtils.h"
#include "../../../Exceptions/ExceptionFactory.h"

Bloque::Bloque(const char *buffer, size_t tamanioBloque)
{
	this->tamanioBloque = tamanioBloque;
	this->buff = new char[this->tamanioBloque];

	this->EscribirBloque(buffer, 0, this->tamanioBloque);

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

size_t Bloque::ObtenerTamanioBloque()
{
	return this->tamanioBloque;
}

bool Bloque::FueModificado()
{
	return this->modificado;
}

void Bloque::BorrarBitModificacion()
{
	this->modificado = false;
}

void Bloque::LeerBloque(char *buff, size_t offset, size_t length)
{
	if (this->tamanioBloque < (offset + length) )
	{
		char msg[20];
		StringUtils_Concatenar(msg,"%d + %d > %d", offset, length, this->tamanioBloque);
		Throw("ArrayIndexOutOfBoundsException", msg);
	}

	memcpy(buff, this->buff + offset, length);
}

void Bloque::EscribirBloque(const char *buff, size_t offset, size_t length)
{
	if (this->tamanioBloque < (offset + length) )
	{
		char msg[20];
		StringUtils_Concatenar(msg,"%d + %d > %d", offset, length, this->tamanioBloque);
		Throw("ArrayIndexOutOfBoundsException", msg);
	}
	
	memcpy(this->buff + offset, buff, length);
	this->modificado = true;
}

iBloquePtr Bloque::Clone()
{
	return new Bloque(this->buff, this->tamanioBloque);
}

void Bloque::Dispose()
{
	delete this;
}
