/* 
 * File:   BloqueRegistro.cpp
 * Author: Monty
 * 
 * Created on 1 de abril de 2016, 00:23
 */

#include "../Headers/BloqueRegistro.h"
#include "../../../TDA/Arbol/ArbolFactory.h"

BloqueRegistro::BloqueRegistro()
{
	this->contenedor = NULL;
}

BloqueRegistro::~BloqueRegistro()
{
	this->contenedor->Dispose();
}

void BloqueRegistro::AgregarRegistro(int idRegistro, iRegistroPtr *registro)
{
	if (this->contenedor)
		this->contenedor = this->contenedor->Add(idRegistro, (iObjectPtr *)registro);
	else
		this->contenedor = ArbolFactory_Nuevo(idRegistro, (iObjectPtr)&registro);
}

iRegistroPtr BloqueRegistro::ObtenerRegistro(int idRegistro)
{
	if (!this->contenedor)
		return NULL;

	return (iRegistroPtr)this->contenedor->GetValue(idRegistro);
}

iRegistroPtr BloqueRegistro::RemoverRegistro(int idRegistro)
{
	if (!this->contenedor)
		return NULL;

	iRegistroPtr registro = NULL;
	this->contenedor = this->contenedor->Remove(idRegistro, (iObjectPtr *)&registro);
}

void BloqueRegistro::Dispose()
{
	delete this;
}
