/* 
 * File:   Registro.cpp
 * Author: Monty
 * 
 * Created on 22 de marzo de 2016, 00:42
 */

#include "../Headers/Registro.h"
#include "../../../Exceptions/ExceptionFactory.h"
#include "../../../Utils/StringUtils/Headers/StringUtils.h"
#include "../../../Sistema/Sistema/Headers/Sistema.h"

Registro::Registro(size_t cantidadCampos): Object(), cantidadCampos(cantidadCampos)
{
	this->tabla = new iFeaturePtr[this->cantidadCampos];
	for (size_t i = 0; i < this->cantidadCampos; i++)
		this->tabla[i] = NULL;
}

Registro::~Registro()
{
	for (size_t i = 0; i < this->cantidadCampos; i++)
	{
		iFeaturePtr feature = this->tabla[i];

		if (feature)
			feature->Dispose();
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
	{
		iFeaturePtr feature = this->tabla[i];
		if (feature)
			feature = feature->Clone();
		Sistema_Execute(nuevaCopia->SetFeature(i, feature););
	}

	return nuevaCopia;
}

size_t Registro::ObtenerCantidadCampos()
{
	return this->cantidadCampos;
}

const iFeaturePtr Registro::GetFeature(size_t posicion)
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

	if (!feature)
		Throw(ExceptionType_InvalidArg, "feature == NULL");

	if (this->tabla[posicion] == feature)
		return;

	if (this->tabla[posicion] != NULL)
		this->tabla[posicion]->Dispose();

	this->tabla[posicion] = feature;
}

void Registro::Dispose()
{
	Object::Dispose();
}
