/* 
 * File:   DescriptorRegistro.cpp
 * Author: Monty
 * 
 * Created on 18 de marzo de 2016, 03:47
 */

#include "../Headers/DescriptorRegistro.h"
#include "../../../Exceptions/ExceptionFactory.h"
#include "../../StringUtils/Headers/StringUtils.h"

DescriptorRegistro::DescriptorRegistro(eValueType *valores, size_t cantidadCampos)
{
	this->cantidadCampos = cantidadCampos;
	this->tablaValores = new eValueType[cantidadCampos];

	for (size_t i = 0; i < cantidadCampos; i++)
		this->tablaValores[i] = valores[i];
}

DescriptorRegistro::~DescriptorRegistro()
{
	if (this->tablaValores)
		delete [] this->tablaValores;
}

eValueType DescriptorRegistro::ObtenerTipoCampo(size_t posicion)
{
	if (posicion >= this->cantidadCampos)
	{
		char msg[20];
		StringUtils_Concatenar(msg,"%lu", posicion);
		Throw(ExceptionType_ArrayIndexOutOfBounds, msg);
	}

	return this->tablaValores[posicion];
}

size_t DescriptorRegistro::ObtenerCantidadCampos()
{
	return this->cantidadCampos;
}

void DescriptorRegistro::Dispose()
{
	delete this;
}
