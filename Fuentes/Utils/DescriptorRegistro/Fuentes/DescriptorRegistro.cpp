/* 
 * File:   DescriptorRegistro.cpp
 * Author: Monty
 * 
 * Created on 18 de marzo de 2016, 03:47
 */

#include "DescriptorRegistro.h"
#include "../../../Exceptions/Exception.h"

DescriptorRegistro::DescriptorRegistro(eValueType *valores, int cantidad)
{
	this->valores = valores;
	this->cantidad = cantidad;
}

DescriptorRegistro::~DescriptorRegistro()
{
	if (this->valores)
		delete this;
}

eValueType DescriptorRegistro::ObtenerValor(int posicion)
{
	if (posicion >= this->cantidad)
		Throw(Exception, "Se intento acceder a una posicion invalida");

	return this->valores[posicion];
}

int DescriptorRegistro::ObtenerCantidadCampos()
{
	return this->cantidad;
}

void DescriptorRegistro::Dispose()
{
	delete this;
}
