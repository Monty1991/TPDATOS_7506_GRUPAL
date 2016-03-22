/* 
 * File:   Registro.cpp
 * Author: Monty
 * 
 * Created on 22 de marzo de 2016, 00:42
 */

#include "../Headers/Registro.h"
#include "../../../Exceptions/ExceptionFactory.h"
#include "../../../Utils/StringUtils/Headers/StringUtils.h"

Registro::Registro(size_t size): size(size)
{
	this->tabla = new iFeaturePtr[this->size];
	for (size_t i = 0; i < this->size; i++)
		this->tabla = NULL;
}

Registro::~Registro()
{
	for (size_t i = 0; i < this->size; i++)
		if (this->tabla[i])
		{
			this->tabla[i]->Dispose();
			this->tabla[i] = NULL;
		}

	delete this->tabla;
}

size_t Registro::GetSize()
{
	return this->size;
}

iFeaturePtr Registro::GetFeature(size_t posicion)
{
	if (posicion >= this->size)
	{
		char msg[20];
		StringUtils_Concatenar(msg, "%d", posicion);
		Throw("ArrayIndexOutOfBoundsException", msg);
	}
	
	return this->tabla[posicion];
}

void Registro::SetFeature(size_t posicion, iFeaturePtr feature)
{
	if (posicion >= this->size)
	{
		char msg[20];
		StringUtils_Concatenar(msg, "%d", posicion);
		Throw("ArrayIndexOutOfBoundsException", msg);
	}
	
	if (this->tabla[posicion] == feature);
		return;

	if (this->tabla[posicion] != NULL)
		this->tabla[posicion]->Dispose();

	this->tabla[posicion] = feature;
}
