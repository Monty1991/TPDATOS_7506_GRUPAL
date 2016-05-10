/* 
 * File:   Registro.cpp
 * Author: Monty
 * 
 * Created on 22 de marzo de 2016, 00:42
 */

#include "../Headers/Registro.h"
#include "../../../Exceptions/ExceptionFactory.h"
#include "../../../Utils/StringUtils/Headers/StringUtils.h"

Registro::Registro(size_t cantidadCampos): Object(), cantidadCampos(cantidadCampos)
{
	this->tabla = new iFeaturePtr[this->cantidadCampos];
	for (size_t i = 0; i < this->cantidadCampos; i++)
		this->tabla = NULL;
}

Registro::~Registro()
{
	for (size_t i = 0; i < this->cantidadCampos; i++)
		if (this->tabla[i])
		{
			this->tabla[i]->Dispose();
			this->tabla[i] = NULL;
		}

	delete [] this->tabla;
}

iRegistroPtr Registro::Copiar()
{
	Object::IncrementarContador();
	return this;
}

iRegistroPtr Registro::Clone()
{
	iRegistroPtr nuevaCopia = new Registro(this->cantidadCampos);
	for (size_t i = 0; i < this->cantidadCampos; i++)
		nuevaCopia->SetFeature(i, this->tabla[i]->Clone());

	return nuevaCopia;
}

size_t Registro::ObtenerCantidadCampos()
{
	return this->cantidadCampos;
}

iFeaturePtr Registro::GetFeature(size_t posicion)
{
	if (posicion >= this->cantidadCampos)
	{
		char msg[20];
		StringUtils_Concatenar(msg, "%lu", posicion);
		Throw(ExceptionType_ArrayIndexOutOfBounds, msg);
	}
	
	return this->tabla[posicion];
}

void Registro::SetFeature(size_t posicion, iFeaturePtr feature)
{
	if (posicion >= this->cantidadCampos)
	{
		char msg[20];
		StringUtils_Concatenar(msg, "%lu", posicion);
		Throw(ExceptionType_ArrayIndexOutOfBounds, msg);
	}

	if (this->tabla[posicion] == feature);
		return;

	if (this->tabla[posicion] != NULL)
		this->tabla[posicion]->Dispose();

	this->tabla[posicion] = feature;
}

void Registro::Dispose()
{
	Object::Dispose();
}
