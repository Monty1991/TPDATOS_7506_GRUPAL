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
#include "../../../Sistema/Sistema/Headers/Sistema.h"

Bloque::Bloque(const char *buffer, size_t tamanioBloque): Object(), tamanioBloque(tamanioBloque), buff(NULL)
{
	this->buff = new char[this->tamanioBloque];

	// Lo limpiamos previamente
	for (size_t i = 0; i < this->tamanioBloque; i++)
		this->buff[i] = 0;

	Sistema_Execute(this->EscribirBloque(buffer, 0, this->tamanioBloque););

	this->BorrarBitModificacion();
}

Bloque::~Bloque()
{
	if (this->buff)
	{
		delete[] this->buff;
		this->buff = NULL;
	}
}

iBloquePtr Bloque::Copiar()
{
	Object::IncrementarContador();
	return this;
}

iBloquePtr Bloque::Clone()
{
	return new Bloque(this->buff, this->tamanioBloque);
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

const char *Bloque::ObtenerContenido()
{
	return this->buff;
}

void Bloque::LeerBloque(char *buff, size_t offset, size_t length)
{
	if (this->tamanioBloque < (offset + length) )
	{
		char msg[20];
		StringUtils_Concatenar(msg,"%lu + %lu > %lu", offset, length, this->tamanioBloque);
		Throw(ExceptionType_ArrayIndexOutOfBounds, msg);
	}

	memcpy(buff, this->buff + offset, length);
}

void Bloque::EscribirBloque(const char *buff, size_t offset, size_t length)
{
	if (this->tamanioBloque < (offset + length) )
	{
		char msg[20];
		StringUtils_Concatenar(msg,"%lu + %lu > %lu", offset, length, this->tamanioBloque);
		Throw(ExceptionType_ArrayIndexOutOfBounds, msg);
	}
	
	memcpy(this->buff + offset, buff, length);
	this->modificado = true;
}

void Bloque::Dispose()
{
	Object::Dispose();
}
